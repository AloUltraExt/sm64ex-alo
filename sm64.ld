OUTPUT_ARCH (mips)

#define LINKER /* Removes externs from preprocessed script */
#include "segments.h"
#undef LINKER

#define BEGIN_SEG(name, addr) \
     _##name##SegmentStart = ADDR(.name); \
     _##name##SegmentRomStart = __romPos; \
     .name (addr) : AT(__romPos)

#define END_SEG(name) \
     _##name##SegmentEnd = ADDR(.name) + SIZEOF(.name); \
     _##name##SegmentRomEnd = __romPos + SIZEOF(.name); \
     __romPos += SIZEOF(.name);

#define BEGIN_NOLOAD(name) \
     _##name##SegmentBssStart = ADDR(.name.noload); \
     .name.noload (NOLOAD) :

#define END_NOLOAD(name) \
     _##name##SegmentBssEnd = ADDR(.name.noload) + SIZEOF(.name.noload); \
     _##name##SegmentBssSize = SIZEOF(.name.noload);

#define MIO0_SEG(name, segAddr) \
    BEGIN_SEG(name##_mio0, segAddr) \
    { \
        BUILD_DIR/bin/name.mio0.o(.data); \
        . = ALIGN(0x10); \
    } \
    END_SEG(name##_mio0)

#define MIO0_EU_SEG(name, segAddr) \
    BEGIN_SEG(name##_mio0, segAddr) \
    { \
        BUILD_DIR/bin/eu/name.mio0.o(.data); \
        . = ALIGN(0x10); \
    } \
    END_SEG(name##_mio0)

#define STANDARD_LEVEL(name) \
    BEGIN_SEG(name##_segment_7, 0x07000000) \
    { \
        BUILD_DIR/levels/name/leveldata.mio0.o(.data); \
        . = ALIGN(0x10); \
    } \
    END_SEG(name##_segment_7) \
    BEGIN_SEG(name, 0x1A000000) \
    { \
        BUILD_DIR/levels/name/script.o(.data); \
        BUILD_DIR/levels/name/geo.o(.data); \
    } \
    END_SEG(name)

#ifdef RM2C
#define CUSTOM_LEVEL(name) \
   BEGIN_SEG(name##_segment_E, 0x0E000000) \
   { \
      BUILD_DIR/levels/name/custom.leveldata.o(.data); \
   } \
   END_SEG(name##_segment_E) \
   BEGIN_SEG(name##_segment_1B, 0x1B000000) \
   { \
	  BUILD_DIR/levels/name/custom.geo.o(.data); \
	  BUILD_DIR/levels/name/custom.script.o(.data); \
      . = ALIGN(0x10); \
   } \
   END_SEG(name##_segment_1B)

#endif

#define STANDARD_OBJECTS(name, segAddr, geoAddr) \
    BEGIN_SEG(name##_mio0, segAddr) \
    { \
        BUILD_DIR/actors/name.mio0.o(.data); \
        . = ALIGN(0x10); \
    } \
    END_SEG(name##_mio0) \
    BEGIN_SEG(name##_geo, geoAddr) \
    { \
        BUILD_DIR/actors/name##_geo.o(.data); \
    } \
    END_SEG(name##_geo)

SECTIONS
{
    __romPos = 0;

    BEGIN_SEG(boot, 0x04000000)
    {
        BUILD_DIR/asm/rom_header.o(.text);
        BUILD_DIR/asm/boot.o(.text);
        BUILD_DIR/asm/ipl3_font.o(.text);
    }
    END_SEG(boot)

    . = 0x80000400;
    BEGIN_NOLOAD(zbuffer) 
    {
        BUILD_DIR/src/buffers/zbuffer.o(.bss*);
    }
    END_NOLOAD(zbuffer)

    . = _zbufferSegmentBssEnd;
    BEGIN_NOLOAD(buffers)
    {
        BUILD_DIR/src/buffers/buffers.o(.bss*);
        . = ALIGN(0x10);
        BUILD_DIR/src/buffers/gfx_output_buffer.o(.bss*);
    }
    END_NOLOAD(buffers)

    . = _buffersSegmentBssEnd;

    // The way audio bss is cleared in vanilla is weird.
    // Originally they used "start and end markers" defined on specific audio files and
    // they get cleaned using a weird for loop that could break if you move audio bss order.
    // Now we move audio bss into it's own segment to clean those properly using bzero.
    BEGIN_NOLOAD(audio)
    {
        BUILD_DIR/src/audio*.o(.bss*);
        . = ALIGN(0x10);
    }
    END_NOLOAD(audio)

    . = _audioSegmentBssEnd;

    BEGIN_SEG(main, .)
    {
        BUILD_DIR/asm/entry.o(.text);
        BUILD_DIR/src/boot*.o(.text);
        BUILD_DIR/src/audio*.o(.text);
        BUILD_DIR/libultra.a:*.o(.text);
        BUILD_DIR/libgcc.a:*.o(.text);
        BUILD_DIR/lib/rsp.o(.text);

        /* data */
        BUILD_DIR/src/boot*.o(.data*);
        BUILD_DIR/src/audio*.o(.data*);
        BUILD_DIR/libultra.a:*.o(.data*);
        BUILD_DIR/libgcc.a:*.o(.data*);
        BUILD_DIR/lib/rsp.o(.data*);

        /* rodata */
        BUILD_DIR/src/boot*.o(.rodata*);
        BUILD_DIR/src/audio*.o(.rodata*);
        BUILD_DIR/libultra.a:*.o(.rodata*);
        BUILD_DIR/libgcc.a:*.o(.rodata*);
        BUILD_DIR/lib/rsp.o(.rodata*);
    }
    END_SEG(main)
    #ifndef PRELIMINARY
        ASSERT((_mainSegmentRomEnd <= 0x101000), "Error: Please shrink your main segment to under 1MB.")
    #endif
    BEGIN_NOLOAD(main)
    {
        BUILD_DIR/src/boot*.o(.*bss*);
        BUILD_DIR/src/game*.o(.*bss*);
        BUILD_DIR/libultra.a:*.o(.*bss*);
        BUILD_DIR/lib/rsp.o(.*bss*);
        . = ALIGN(0x10);
    }
    END_NOLOAD(main)

    . = _mainSegmentBssEnd;

    BEGIN_SEG(engine, .)
    {
      BUILD_DIR/src/game*.o(.text*);
      BUILD_DIR/src/game/behavior_actions.o(.text*);
      BUILD_DIR/src/game/obj_behaviors_2.o(.text*);
      BUILD_DIR/src/game/obj_behaviors.o(.text*);
      BUILD_DIR/src/game/object_helpers.o(.text*);
      BUILD_DIR/src/game/rendering_graph_node.o(.text*);
      BUILD_DIR/src/engine/math_util.o(.text*);
      BUILD_DIR/src/engine/surface_collision.o(.text*);
      BUILD_DIR/src/engine/surface_load.o(.text*);
      BUILD_DIR/src/engine/graph_node.o(.text*);
      BUILD_DIR/src/engine*.o(.text*);
#ifndef GODDARD_MFACE
      BUILD_DIR/src/menu*.o(.text);
#endif
      BUILD_DIR/src/extras*.o(.text);

      /* data */
      BUILD_DIR/src/game*.o(.data*);
      BUILD_DIR/src/engine*.o(.data*);
#ifndef GODDARD_MFACE
      BUILD_DIR/src/menu*.o(.data*);
#endif
      BUILD_DIR/src/extras*.o(.data*);

      /* rodata */
      BUILD_DIR/src/game*.o(.rodata*);
      BUILD_DIR/src/engine*.o(.rodata*);
#ifndef GODDARD_MFACE
      BUILD_DIR/src/menu*.o(.rodata*);
#endif
      BUILD_DIR/src/extras*.o(.rodata*);
      . = ALIGN(0x10);
    }
    END_SEG(engine)
    
    // load_engine_code_segment had to be modified to clear bss section.
    // Without it, any code you add in would get garbage data, causing a crash on boot.
    BEGIN_NOLOAD(engine)
    {
      BUILD_DIR/src/game*.o(.*bss*);
      BUILD_DIR/src/engine*.o(.bss*);
#ifndef GODDARD_MFACE
      BUILD_DIR/src/menu*.o(.bss*);
#endif
      BUILD_DIR/src/extras*.o(.bss*);
      . = ALIGN(0x40);
    }
    END_NOLOAD(engine)

    . = _engineSegmentBssEnd;
    BEGIN_NOLOAD(framebuffers)
    {
        BUILD_DIR/src/buffers/framebuffers.o(.bss*);
    }
    END_NOLOAD(framebuffers)

    __expansionRamStart = 0x80400000;
    #ifndef N64_USE_EXTENDED_RAM
        #ifndef PRELIMINARY
            ASSERT((. <= __expansionRamStart), "Error: RDRAM expanded into Expansion RAM, despite Expansion RAM not being defined.")
        #endif
    #endif
    BEGIN_SEG(entry, 0x10000000)
    {
        BUILD_DIR/levels/entry.o(.data);
    }
    END_SEG(entry)

    /* load MIO0 and level data */
    MIO0_SEG(segment2, 0x02000000)
#ifdef VERSION_EU
    MIO0_EU_SEG(translation_en, 0x19000000)
    MIO0_EU_SEG(translation_fr, 0x19000000)
    MIO0_EU_SEG(translation_de, 0x19000000)
#endif

    /* mario actor group */
    STANDARD_OBJECTS(group0,  0x04000000, 0x17000000)

    /* load the other actor groups */
    STANDARD_OBJECTS(group1,  0x05000000, 0x0C000000)
    STANDARD_OBJECTS(group2,  0x05000000, 0x0C000000)
    STANDARD_OBJECTS(group3,  0x05000000, 0x0C000000)
    STANDARD_OBJECTS(group4,  0x05000000, 0x0C000000)
    STANDARD_OBJECTS(group5,  0x05000000, 0x0C000000)
    STANDARD_OBJECTS(group6,  0x05000000, 0x0C000000)
    STANDARD_OBJECTS(group7,  0x05000000, 0x0C000000)
    STANDARD_OBJECTS(group8,  0x05000000, 0x0C000000)
    STANDARD_OBJECTS(group9,  0x05000000, 0x0C000000)
    STANDARD_OBJECTS(group10, 0x05000000, 0x0C000000)
    STANDARD_OBJECTS(group11, 0x05000000, 0x0C000000)
    STANDARD_OBJECTS(group12, 0x06000000, 0x0D000000)
    STANDARD_OBJECTS(group13, 0x06000000, 0x0D000000)
    STANDARD_OBJECTS(group14, 0x06000000, 0x0D000000)
    STANDARD_OBJECTS(group15, 0x06000000, 0x0D000000)
    STANDARD_OBJECTS(group16, 0x06000000, 0x0D000000)
    STANDARD_OBJECTS(group17, 0x06000000, 0x0D000000)

    /* load the common actor groups */
    STANDARD_OBJECTS(common0, 0x08000000, 0x0F000000)
    STANDARD_OBJECTS(common1, 0x03000000, 0x16000000)

    /* use segmented addressing for behaviors */
    BEGIN_SEG(behavior, 0x13000000)
    {
        BUILD_DIR/data/behavior_data.o(.data);
    }
    END_SEG(behavior)

#ifdef GODDARD_MFACE
    /* 0x8016F000 21D7D0-255EC0 [386F0] */
    BEGIN_SEG(goddard, (SEG_RAM_END - GODDARD_SIZE))
    {
        BUILD_DIR/src/menu*.o(.text);
        BUILD_DIR/src/menu*.o(.data*);
        BUILD_DIR/src/menu*.o(.rodata*);

        BUILD_DIR/libgoddard.a:*.o(.text);

        /* goddard subsystem data */
        BUILD_DIR/libgoddard.a:gd_main.o(.data*);
        BUILD_DIR/libgoddard.a:draw_objects.o(.data*);
        BUILD_DIR/libgoddard.a:objects.o(.data*);
        BUILD_DIR/libgoddard.a:particles.o(.data*);
        BUILD_DIR/libgoddard.a:dynlist_proc.o(.data*);
        BUILD_DIR/libgoddard.a:debug_utils.o(.data*);
        BUILD_DIR/libgoddard.a:joints.o(.data*);
        BUILD_DIR/libgoddard.a:shape_helper.o(.data*);
        BUILD_DIR/libgoddard.a:renderer.o(.data*);
        /* goddard subsystem rodata */
        BUILD_DIR/libgoddard.a:gd_main.o(.rodata*);
        BUILD_DIR/libgoddard.a:gd_memory.o(.rodata*);
        BUILD_DIR/libgoddard.a:draw_objects.o(.rodata*);
        BUILD_DIR/libgoddard.a:objects.o(.rodata*);
        BUILD_DIR/libgoddard.a:skin_movement.o(.rodata*);
        BUILD_DIR/libgoddard.a:particles.o(.rodata*);
        BUILD_DIR/libgoddard.a:dynlist_proc.o(.rodata*);
        BUILD_DIR/libgoddard.a:old_menu.o(.rodata*);
        BUILD_DIR/libgoddard.a:debug_utils.o(.rodata*);
        BUILD_DIR/libgoddard.a:joints.o(.rodata*);
        BUILD_DIR/libgoddard.a:skin.o(.rodata*);
        BUILD_DIR/libgoddard.a:gd_math.o(.rodata*);
        BUILD_DIR/libgoddard.a:shape_helper.o(.rodata*);
        BUILD_DIR/libgoddard.a:renderer.o(.rodata*);
    }
    END_SEG(goddard)
    BEGIN_NOLOAD(goddard)
    {
        BUILD_DIR/src/menu*.o(.bss*);

        BUILD_DIR/libgoddard.a:*.o(.bss*);
    }
    END_NOLOAD(goddard)
#endif

    #ifndef PRELIMINARY
        ASSERT((. <= (SEG_POOL_START + POOL_SIZE)), "Error: extended past pool end.")
    #endif
    #ifdef PRELIMINARY
        GODDARD_SIZE = SIZEOF(.goddard) + SIZEOF(.goddard.noload);
    #endif

    __mainPoolStart = .;
    __mainPoolSize = SEG_RAM_END - .;

    /* 0x268020 0x268020-0 [0] */
    BEGIN_SEG(intro, 0x14000000)
    {
        BUILD_DIR/levels/intro/script.o(.data);
        BUILD_DIR/levels/intro/geo.o(.data);
    }
    END_SEG(intro)
    BEGIN_SEG(intro_segment_7, 0x07000000)
    {
        BUILD_DIR/levels/intro/leveldata.mio0.o(.data);
        . = ALIGN(0x10);
    }
    END_SEG(intro_segment_7)

    MIO0_SEG(debug_level_select, 0x07000000)
    MIO0_SEG(title_screen_bg, 0x0A000000)

#ifdef GODDARD_MFACE
    /* 271B20-2A42A0 [32780] */
    BEGIN_SEG(gd_dynlists, 0x04000000)
    {
        BUILD_DIR/libgoddard.a:dynlist_test_cube.o(.data);
        BUILD_DIR/libgoddard.a:dynlist_unused.o(.data);
        BUILD_DIR/libgoddard.a:dynlist_mario_face.o(.data);
        BUILD_DIR/libgoddard.a:dynlists_mario_eyes.o(.data);
        BUILD_DIR/libgoddard.a:dynlists_mario_eyebrows_mustache.o(.data);
        BUILD_DIR/libgoddard.a:dynlist_mario_master.o(.data);
        BUILD_DIR/libgoddard.a:anim_mario_mustache_right.o(.data);
        BUILD_DIR/libgoddard.a:anim_mario_mustache_left.o(.data);
        BUILD_DIR/libgoddard.a:anim_mario_lips_1.o(.data);
        BUILD_DIR/libgoddard.a:anim_mario_lips_2.o(.data);
        BUILD_DIR/libgoddard.a:anim_mario_eyebrows_1.o(.data);
        BUILD_DIR/libgoddard.a:anim_group_1.o(.data);
        BUILD_DIR/libgoddard.a:anim_group_2.o(.data);
        BUILD_DIR/libgoddard.a:dynlist_test_cube.o(.rodata*);
        BUILD_DIR/libgoddard.a:dynlist_unused.o(.rodata*);
        BUILD_DIR/libgoddard.a:*.o(.data);
        BUILD_DIR/libgoddard.a:*.o(.rodata);
    }
    END_SEG(gd_dynlists)
#endif

    gMainLevels = __romPos;

    BEGIN_SEG(menu, 0x14000000)
    {
        BUILD_DIR/levels/menu/script.o(.data);
        BUILD_DIR/levels/menu/geo.o(.data);
    }
    END_SEG(menu)
    BEGIN_SEG(menu_segment_7, 0x07000000)
    {
        BUILD_DIR/levels/menu/leveldata.mio0.o(.data);
        . = ALIGN(0x10);
    }
    END_SEG(menu_segment_7)

    BEGIN_SEG(scripts, 0x15000000)
    {
        BUILD_DIR/levels/scripts.o(.data);
    }
    END_SEG(scripts)

    MIO0_SEG(water_skybox, 0x0A000000)
    MIO0_SEG(ccm_skybox, 0x0A000000)
    MIO0_SEG(clouds_skybox, 0x0A000000)
    MIO0_SEG(bitfs_skybox, 0x0A000000)
    MIO0_SEG(wdw_skybox, 0x0A000000)
    MIO0_SEG(cloud_floor_skybox, 0x0A000000)
    MIO0_SEG(ssl_skybox, 0x0A000000)
    MIO0_SEG(bbh_skybox, 0x0A000000)
    MIO0_SEG(bidw_skybox, 0x0A000000)
    MIO0_SEG(bits_skybox, 0x0A000000)

   // Custom Skyboxes from RM2C. In base repo dummy file exists
#ifdef RM2C
   #include "textures/skyboxes/Skybox_Rules.ld"
#endif

    // Texture bins
    MIO0_SEG(fire, 0x09000000)
    MIO0_SEG(spooky, 0x09000000)
    MIO0_SEG(generic, 0x09000000)
    MIO0_SEG(water, 0x09000000)
    MIO0_SEG(sky, 0x09000000)
    MIO0_SEG(snow, 0x09000000)
    MIO0_SEG(cave, 0x09000000)
    MIO0_SEG(machine, 0x09000000)
    MIO0_SEG(mountain, 0x09000000)
    MIO0_SEG(grass, 0x09000000)
    MIO0_SEG(outside, 0x09000000)
    MIO0_SEG(inside, 0x09000000)
    MIO0_SEG(effect, 0x0B000000)

#define STUB_LEVEL(_0, _1, _2, _3, _4, _5, _6, _7, _8)
#define DEFINE_LEVEL(_0, _1, _2, folder, _4, _5, _6, _7, _8, _9, _10) STANDARD_LEVEL(folder)

    #include "levels/level_defines.h"

#undef STUB_LEVEL
#undef DEFINE_LEVEL

#ifdef RM2C
//So RM2C can partially output custom levels instead of forcing all levels to have custom content
#define DEFINE_LEVEL(folder,_0) CUSTOM_LEVEL(folder)
   #include "levels/custom_level_defines.h"
#undef DEFINE_LEVEL
#endif

    /* 4E9FA0-? [?] */
    BEGIN_SEG(assets, __romPos)
    {
        BUILD_DIR/assets/mario_anim_data.o(.data);
        BUILD_DIR/assets/mario_anim_data.o(.rodata);
        BUILD_DIR/assets/demo_data.o(.data);
        BUILD_DIR/sound/sound_data.o(.data);
    }
    END_SEG(assets)

    /* Discard everything not specifically mentioned above. */
    /DISCARD/ :
    {
        *(*);
    }
}
