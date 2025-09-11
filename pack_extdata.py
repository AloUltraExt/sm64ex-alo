#!/usr/bin/env python3

import os
import sys
import glob
import zipfile
import hashlib
import json
import multiprocessing
from concurrent.futures import ThreadPoolExecutor, as_completed
import time
import argparse

def parse_defines(defines_list):
    """Parse -D arguments into a dictionary of defines (C-style)"""
    defines = {}
    for define in defines_list:
        if define.startswith('-D'):
            define = define[2:]  # Remove the -D prefix

        # Handle both KEY and KEY=VALUE formats
        if '=' in define:
            key, value = define.split('=', 1)
            defines[key] = value
        else:
            defines[define] = True  # Flag-style define (no value)

    return defines

def is_defined(defines, key):
    """Check if a define exists (C-style: any value means defined)"""
    return key in defines

def calculate_file_hash(filepath):
    """Calculate MD5 hash of a file for caching"""
    hash_md5 = hashlib.md5()
    try:
        with open(filepath, "rb") as f:
            for chunk in iter(lambda: f.read(4096), b""):
                hash_md5.update(chunk)
        return hash_md5.hexdigest()
    except (IOError, OSError):
        return None

def generate_file_list(build_dir, defines, skytile_dir):
    """Generate the list of files to include in the basepack"""
    file_list = []

    # Sound files
    sound_files = [
        ('bank_sets', 'sound/bank_sets'),
        ('sequences.bin', 'sound/sequences.bin'),
        ('sound_data.ctl', 'sound/sound_data.ctl'),
        ('sound_data.tbl', 'sound/sound_data.tbl')
    ]

    # SH/CN version specific files
    if is_defined(defines, 'VERSION_SH') or is_defined(defines, 'VERSION_CN'):
        sound_files.extend([
            ('sequences_header', 'sound/sequences_header'),
            ('ctl_header', 'sound/ctl_header'),
            ('tbl_header', 'sound/tbl_header')
        ])

    for filename, archive_path in sound_files:
        real_path = os.path.join(build_dir, 'sound', filename)
        if os.path.exists(real_path):
            file_list.append((real_path, archive_path))

    # Skybox tiles
    if skytile_dir and os.path.exists(skytile_dir):
        for tile_file in glob.glob(os.path.join(skytile_dir, '*')):
            if os.path.isfile(tile_file):
                archive_path = f"gfx/{os.path.relpath(tile_file, build_dir)}"
                file_list.append((tile_file, archive_path))

    # PNG files in various directories
    folders_to_search = ['actors', 'levels', 'textures']

    if is_defined(defines, 'PORT_MOP_OBJS'):
        folders_to_search.append('src/extras/mop/actors')

    # Exact directory paths to exclude
    exclude_paths = ['textures/crash_screen', 'textures/crash_screen_pc']

    if not is_defined(defines, 'VERSION_CN'):
        exclude_paths.append('textures/segment2/cn')

    # Normalize all paths at once
    exclude_list = [os.path.normpath(path) for path in exclude_paths]

    for folder in folders_to_search:
        if os.path.exists(folder):
            for root, dirs, files in os.walk(folder):
                # Check if current directory should be excluded (exact match)
                normalized_root = os.path.normpath(root)
                should_exclude = normalized_root in exclude_list

                if should_exclude:
                    # Skip this directory and all its subdirectories
                    continue

                for file in files:
                    if file.endswith('.png'):
                        real_path = os.path.join(root, file)
                        archive_path = f"gfx/{real_path}"
                        file_list.append((real_path, archive_path))

    return file_list

def load_ndjson_cache(cache_file):
    """Load NDJSON cache file"""
    cache = {}
    if os.path.exists(cache_file):
        try:
            with open(cache_file, 'r') as f:
                for line in f:
                    line = line.strip()
                    if line:
                        try:
                            entry = json.loads(line)
                            cache_key = entry.get('key')
                            if cache_key:
                                cache[cache_key] = entry
                        except json.JSONDecodeError:
                            continue
        except IOError:
            pass
    return cache

def save_ndjson_cache(cache_file, cache_data):
    """Save cache as NDJSON (faster for large caches)"""
    try:
        with open(cache_file, 'w') as f:
            for cache_key, data in cache_data.items():
                entry = {'key': cache_key, **data}
                f.write(json.dumps(entry) + '\n')
    except IOError:
        pass

def clean_cache(build_dir):
    """Clean the cache file"""
    cache_file = os.path.join(build_dir, 'basepack_cache.ndjson')

    if os.path.exists(cache_file):
        try:
            os.remove(cache_file)
            print(f"Removed cache file: {cache_file}")
            return True
        except OSError as e:
            print(f"Error removing cache file: {e}")
            return False
    else:
        print("Cache file does not exist")
        return True

def get_files_to_pack(file_list, cache_file):
    """Get list of files that need to be packed (based on cache)"""
    old_cache = load_ndjson_cache(cache_file)
    files_to_pack = []

    # Get all files that should be in the current build
    current_files = {real_path: archive_path for real_path, archive_path in file_list}

    # Clean up cache by removing entries for files that:
    # 1. No longer exist on filesystem, OR
    # 2. Should not be included in current build (due to define conditions)
    cleaned_cache = {}
    for cache_key, cache_data in old_cache.items():
        if ':' in cache_key:
            real_path = cache_key.split(':', 1)[0]

            # Keep in cache only if:
            # 1. File exists on filesystem, AND
            # 2. File should be included in current build
            if os.path.exists(real_path) and real_path in current_files:
                cleaned_cache[cache_key] = cache_data

    # Now check which files need to be packed
    for real_path, archive_path in file_list:
        if not os.path.exists(real_path):
            continue

        file_hash = calculate_file_hash(real_path)
        if file_hash is None:
            continue

        mtime = os.path.getmtime(real_path)
        cache_key = f"{real_path}:{archive_path}"

        # Check if file has changed or is new
        if (cache_key in cleaned_cache and
            cleaned_cache[cache_key].get('hash') == file_hash and
            cleaned_cache[cache_key].get('mtime') == mtime):
            # File hasn't changed, use cached version
            pass
        else:
            # File has changed or is new
            files_to_pack.append((real_path, archive_path))
            # Update cache entry for this file
            cleaned_cache[cache_key] = {
                'hash': file_hash,
                'mtime': mtime,
                'size': os.path.getsize(real_path)
            }

    return files_to_pack, cleaned_cache

def prepare_file_for_zip(real_path, archive_path):
    """Read file content and prepare it for ZIP writing (thread-safe)"""
    try:
        with open(real_path, 'rb') as f:
            content = f.read()
        return True, real_path, archive_path, content, None
    except (IOError, OSError) as e:
        return False, real_path, archive_path, None, str(e)

def print_progress(current, total, start_time, message=""):
    """Simple progress indicator with ASCII-only characters"""
    if total == 0:
        return

    elapsed = time.time() - start_time
    percent = (current / total) * 100
    bar_length = 20
    filled_length = int(bar_length * current // total)

    bar = '=' * filled_length + '-' * (bar_length - filled_length)

    if current > 0:
        time_per_file = elapsed / current
        remaining = time_per_file * (total - current)
        time_info = f"{elapsed:.1f}s elapsed, {remaining:.1f}s remaining"
    else:
        time_info = f"{elapsed:.1f}s elapsed"

    progress_text = f"\r{message} |{bar}| {current}/{total} ({percent:.1f}%) {time_info}"

    try:
        sys.stdout.write(progress_text)
        sys.stdout.flush()
    except UnicodeEncodeError:
        # Fallback: simpler progress without Unicode
        simple_text = f"\r{message} {current}/{total} ({percent:.1f}%) {time_info}"
        sys.stdout.write(simple_text)
        sys.stdout.flush()

def verify_zip_contents(zip_path, expected_files, changed_files=None):
    """Verify that the ZIP contains the expected files and check changed files"""
    if not os.path.exists(zip_path):
        print(f"ERROR: ZIP file {zip_path} does not exist")
        return False

    try:
        with zipfile.ZipFile(zip_path, 'r') as zipf:
            zip_files = set(zipf.namelist())

            # Check if all expected files are present
            missing_files = expected_files - zip_files
            if missing_files:
                print(f"ERROR: {len(missing_files)} files missing from ZIP:")
                for missing in sorted(missing_files)[:10]:  # Show first 10 missing
                    print(f"  - {missing}")
                if len(missing_files) > 10:
                    print(f"  ... and {len(missing_files) - 10} more")
                return False

            # Check if any unexpected files are present
            extra_files = zip_files - expected_files
            if extra_files:
                print(f"WARNING: {len(extra_files)} unexpected files in ZIP:")
                for extra in sorted(extra_files)[:5]:  # Show first 5 extra
                    print(f"  - {extra}")
                if len(extra_files) > 5:
                    print(f"  ... and {len(extra_files) - 5} more")

            # Verify changed files if provided
            if changed_files:
                verified_changes = 0
                failed_changes = 0

                for real_path, archive_path in changed_files:
                    if archive_path in zip_files:
                        # Calculate hash of the file in ZIP
                        with zipf.open(archive_path) as zipped_file:
                            zip_content = zipped_file.read()
                            zip_hash = hashlib.md5(zip_content).hexdigest()

                        # Calculate hash of the original file
                        file_hash = calculate_file_hash(real_path)

                        if file_hash and zip_hash == file_hash:
                            verified_changes += 1
                        else:
                            failed_changes += 1
                            print(f"VERIFY FAIL: {archive_path} - hash mismatch")
                    else:
                        failed_changes += 1
                        print(f"VERIFY FAIL: {archive_path} - missing from ZIP")

                if failed_changes > 0:
                    print(f"File verification: {verified_changes} OK, {failed_changes} FAILED")
                    return False
                else:
                    print(f"File verification: All {verified_changes} changed files verified OK")

            return True

    except (IOError, zipfile.BadZipFile) as e:
        print(f"ERROR: Failed to verify ZIP file: {e}")
        return False

def create_basepack(build_dir, defines, skytile_dir, output_zip, num_workers):
    """Generate file list and create basepack ZIP with optimizations"""
    cache_file = os.path.join(build_dir, 'basepack_cache.ndjson')

    # Generate complete file list
    print("Scanning for files...")
    file_list = generate_file_list(build_dir, defines, skytile_dir)
    print(f"Found {len(file_list)} total files")

    # Check which files need to be packed
    print("Checking cache for changes...")
    files_to_pack, cleaned_cache = get_files_to_pack(file_list, cache_file)

    # Track changed files for verification
    changed_files = files_to_pack.copy()

    # Get the set of archive paths that should be in the final ZIP
    current_archive_paths = {archive_path for _, archive_path in file_list}

    # Check if ZIP needs to be rebuilt to remove unwanted files
    need_cleanup = False
    if os.path.exists(output_zip):
        try:
            with zipfile.ZipFile(output_zip, 'r') as old_zip:
                current_zip_files = set(old_zip.namelist())
                # Check if there are files in ZIP that shouldn't be there
                unwanted_files = current_zip_files - current_archive_paths
                if unwanted_files:
                    print(f"Found {len(unwanted_files)} unwanted files in ZIP that need removal")
                    need_cleanup = True
        except (IOError, zipfile.BadZipFile):
            # ZIP is corrupt or can't be read, need to rebuild
            need_cleanup = True

    # We need to rebuild if:
    # 1. There are files to pack (changed/new files), OR
    # 2. There are unwanted files in the ZIP that need removal
    # 3. Cache file doesn't exist but ZIP does (force rebuild to avoid duplicates)
    cache_exists = os.path.exists(cache_file)
    need_rebuild = bool(files_to_pack) or need_cleanup or (os.path.exists(output_zip) and not cache_exists)

    if not need_rebuild:
        print("No files need to be updated in basepack")
        # Still save the cleaned cache (in case files were removed from filesystem)
        save_ndjson_cache(cache_file, cleaned_cache)
        return True

    if need_cleanup and not files_to_pack:
        print("Cleaning up unwanted files from ZIP...")
    elif not cache_exists and os.path.exists(output_zip):
        print("Cache missing, rebuilding ZIP to avoid duplicates...")

    if files_to_pack:
        print(f"Processing {len(files_to_pack)} changed files:")
        for real_path, archive_path in files_to_pack:
            print(f"  - {archive_path}")

    # Use ThreadPoolExecutor for parallel file reading
    start_time = time.time()
    successful_reads = 0
    failed_reads = 0
    failed_files = []
    file_contents = []

    if files_to_pack:
        with ThreadPoolExecutor(max_workers=num_workers) as executor:
            # Submit all file reading tasks
            future_to_file = {
                executor.submit(prepare_file_for_zip, real_path, archive_path): (real_path, archive_path)
                for real_path, archive_path in files_to_pack
            }

            # Process results with progress indicator
            completed = 0
            total = len(files_to_pack)

            for future in as_completed(future_to_file):
                real_path, archive_path = future_to_file[future]
                try:
                    success, file_path, arch_path, content, error = future.result()
                    if success:
                        successful_reads += 1
                        file_contents.append((arch_path, content))
                    else:
                        failed_reads += 1
                        failed_files.append((file_path, error))
                except Exception as e:
                    failed_reads += 1
                    failed_files.append((real_path, str(e)))

                completed += 1
                print_progress(completed, total, start_time, "Reading files")

    # Print newline to clear the progress bar
    print()
    if files_to_pack:
        print(f"File reading complete: {successful_reads} successful, {failed_reads} failed")

    if failed_reads > 0:
        print("\nFailed to read files:")
        for file_path, error in failed_files:
            print(f"  - {file_path}: {error}")

    # Now create the ZIP file
    if need_rebuild:
        print(f"Creating ZIP archive...")
        try:
            # Create a temporary file first
            temp_zip = output_zip + '.tmp'

            # Create a mapping of archive paths to content for changed files
            changed_files_map = {archive_path: content for archive_path, content in file_contents}

            with zipfile.ZipFile(temp_zip, 'w', zipfile.ZIP_DEFLATED, allowZip64=False) as zipf:
                added_files = set()

                # First, add all files from the old ZIP that should remain (excluding changed ones)
                if os.path.exists(output_zip):
                    try:
                        with zipfile.ZipFile(output_zip, 'r') as old_zip:
                            for old_info in old_zip.infolist():
                                if (old_info.filename in current_archive_paths and
                                    old_info.filename not in changed_files_map and
                                    old_info.filename not in added_files):

                                    # This file should remain and hasn't been changed
                                    with old_zip.open(old_info) as old_file:
                                        content = old_file.read()
                                    zipf.writestr(old_info.filename, content)
                                    added_files.add(old_info.filename)
                                    if len(added_files) % 100 == 0:
                                        print_progress(len(added_files), len(current_archive_paths), start_time, "Copying unchanged files")
                    except (IOError, zipfile.BadZipFile):
                        # Old ZIP is corrupt, start fresh
                        pass

                # Now add all changed files (this will overwrite any existing ones)
                for i, (archive_path, content) in enumerate(file_contents):
                    zipf.writestr(archive_path, content)
                    added_files.add(archive_path)

                    if len(added_files) % 100 == 0 or i + 1 == len(file_contents):
                        print_progress(len(added_files), len(current_archive_paths), start_time, "Adding changed files")

            # Replace the old ZIP with the new one
            if os.path.exists(output_zip):
                os.remove(output_zip)
            os.rename(temp_zip, output_zip)

            # Print newline to clear the progress bar
            print()

            # Verify the ZIP contents
            print("Verifying ZIP contents...")
            verification_success = verify_zip_contents(output_zip, current_archive_paths, changed_files if files_to_pack else None)

            if not verification_success:
                print("ERROR: ZIP verification failed!")
                return False

            # Update cache AFTER successful ZIP creation and verification
            print("Updating cache...")
            # The cache is already updated with new/changed files in get_files_to_pack
            # We just need to save it
            save_ndjson_cache(cache_file, cleaned_cache)

            final_count = len(added_files)
            print(f"Successfully created and verified ZIP with {final_count} files")
            return True

        except (IOError, OSError, zipfile.BadZipFile) as e:
            print(f"\nError creating ZIP file: {e}")
            # Clean up temporary file if it exists
            if os.path.exists(temp_zip):
                os.remove(temp_zip)
            return False
    else:
        print("No files to write to ZIP")
        # Still save the cleaned cache (in case files were removed from filesystem)
        save_ndjson_cache(cache_file, cleaned_cache)
        return failed_reads == 0

def main():
    parser = argparse.ArgumentParser(description='EXTERNAL_DATA zip packer for sm64ex')
    parser.add_argument('--build-dir', required=True, help='Build directory')
    parser.add_argument('--skytile-dir', help='Skybox tiles directory')
    parser.add_argument('--output', help='Output ZIP file')
    parser.add_argument('--workers', type=int, help='Number of worker threads (default: CPU count - 1)')
    parser.add_argument('--clean', action='store_true', help='Clean cache file and exit')
    parser.add_argument('-D', action='append', default=[], help='Define C flags')

    args = parser.parse_args()

    # Handle clean operation
    if args.clean:
        success = clean_cache(args.build_dir)
        sys.exit(0 if success else 1)

    # Validate required arguments for non-clean operations
    if not args.output:
        parser.error("the following arguments are required for packing: --output")

    # Parse defines (C-style: both KEY and KEY=VALUE)
    defines = parse_defines(args.D)

    # Determine number of workers
    if args.workers is not None:
        num_workers = max(1, args.workers)
    else:
        num_workers = max(1, multiprocessing.cpu_count() - 1)

    # Create output directory
    os.makedirs(os.path.dirname(args.output), exist_ok=True)

    success = create_basepack(
        args.build_dir,
        defines,
        args.skytile_dir,
        args.output,
        num_workers
    )

    if success:
        print(f"Successfully created: {args.output}")
        sys.exit(0)
    else:
        print(f"Failed to create: {args.output}")
        sys.exit(1)

if __name__ == "__main__":
    main()
