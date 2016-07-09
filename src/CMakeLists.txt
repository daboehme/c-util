set(C_UTIL_HEADERS
  strutil.h
  vlenc.h
  unitfmt.h)
set(C_UTIL_SOURCES
  strutil.c
  vlenc.c
  unitfmt.c)

add_library(c-util ${C_UTIL_SOURCES})

#
# Installation (if needed)
#

install(FILES ${C_UTIL_HEADERS} DESTINATION include/c-util)

install(TARGETS c-util
  EXPORT c-util
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib)
