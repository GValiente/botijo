#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SDL2::SDL2-static" for configuration "Release"
set_property(TARGET SDL2::SDL2-static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SDL2::SDL2-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "m;iconv;/System/Library/Frameworks/CoreVideo.framework;/System/Library/Frameworks/Cocoa.framework;/System/Library/Frameworks/IOKit.framework;/System/Library/Frameworks/ForceFeedback.framework;/System/Library/Frameworks/Carbon.framework;/System/Library/Frameworks/CoreAudio.framework;/System/Library/Frameworks/AudioToolbox.framework;-Wl,-undefined,error"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libSDL2.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS SDL2::SDL2-static )
list(APPEND _IMPORT_CHECK_FILES_FOR_SDL2::SDL2-static "${_IMPORT_PREFIX}/lib/libSDL2.a" )

# Import target "SDL2::SDL2" for configuration "Release"
set_property(TARGET SDL2::SDL2 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SDL2::SDL2 PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "m;iconv;/System/Library/Frameworks/CoreVideo.framework;/System/Library/Frameworks/Cocoa.framework;/System/Library/Frameworks/IOKit.framework;/System/Library/Frameworks/ForceFeedback.framework;/System/Library/Frameworks/Carbon.framework;/System/Library/Frameworks/CoreAudio.framework;/System/Library/Frameworks/AudioToolbox.framework;-Wl,-undefined,error"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libSDL2.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libSDL2.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS SDL2::SDL2 )
list(APPEND _IMPORT_CHECK_FILES_FOR_SDL2::SDL2 "${_IMPORT_PREFIX}/lib/libSDL2.dylib" )

# Import target "SDL2::SDL2main" for configuration "Release"
set_property(TARGET SDL2::SDL2main APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SDL2::SDL2main PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libSDL2main.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS SDL2::SDL2main )
list(APPEND _IMPORT_CHECK_FILES_FOR_SDL2::SDL2main "${_IMPORT_PREFIX}/lib/libSDL2main.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
