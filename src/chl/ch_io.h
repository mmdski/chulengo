#include <stdio.h>

#ifdef _WIN32

#define SIZE_T_FMT "%llu"

#define ch_snprintf(buffer, size, format, ...)                                 \
  sprintf_s (buffer, size, format, __VA_ARGS__)

#else

#define SIZE_T_FMT "%lu"

#define ch_snprintf(buffer, size, format, ...)                                 \
  snprintf (buffer, size, format, __VA_ARGS__)

#endif
