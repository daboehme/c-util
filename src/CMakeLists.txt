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

install(FILES ${C_UTIL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/c-util)

install(TARGETS c-util
  EXPORT c-util
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
