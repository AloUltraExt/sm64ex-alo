/* Public domain.  */
//#include <stddef.h>
#include <ultra64.h>

void *
memmove (void *dest, const void *src, size_t len)
{
  char *d = dest;
  const char *s = src;
  if (d < s)
    while (len--)
      *d++ = *s++;
  else
    {
      char *lasts = (char *)s + (len-1);
      char *lastd = (char *)d + (len-1);
      while (len--)
        *lastd-- = *lasts--;
    }
  return dest;
}
