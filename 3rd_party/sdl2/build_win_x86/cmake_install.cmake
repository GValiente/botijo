# Install script for directory: C:/dev/botijo/3rd_party/sdl2

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/SDL2")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/dev/botijo/3rd_party/sdl2/build_win_x86/SDL2-static.lib")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/dev/botijo/3rd_party/sdl2/build_win_x86/SDL2.lib")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/dev/botijo/3rd_party/sdl2/build_win_x86/SDL2.dll")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/dev/botijo/3rd_party/sdl2/build_win_x86/SDL2main.lib")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets.cmake"
         "C:/dev/botijo/3rd_party/sdl2/build_win_x86/CMakeFiles/Export/cmake/SDL2Targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/SDL2Targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "C:/dev/botijo/3rd_party/sdl2/build_win_x86/CMakeFiles/Export/cmake/SDL2Targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "C:/dev/botijo/3rd_party/sdl2/build_win_x86/CMakeFiles/Export/cmake/SDL2Targets-release.cmake")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES
    "C:/dev/botijo/3rd_party/sdl2/SDL2Config.cmake"
    "C:/dev/botijo/3rd_party/sdl2/build_win_x86/SDL2ConfigVersion.cmake"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL2" TYPE FILE FILES
    "C:/dev/botijo/3rd_party/sdl2/include/SDL.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_assert.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_atomic.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_audio.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_bits.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_blendmode.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_clipboard.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_config_android.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_config_iphoneos.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_config_macosx.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_config_minimal.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_config_pandora.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_config_psp.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_config_windows.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_config_winrt.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_config_wiz.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_copying.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_cpuinfo.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_egl.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_endian.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_error.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_events.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_filesystem.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_gamecontroller.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_gesture.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_haptic.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_hints.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_joystick.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_keyboard.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_keycode.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_loadso.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_log.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_main.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_messagebox.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_mouse.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_mutex.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_name.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_opengl.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_opengl_glext.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_opengles.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_opengles2.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_opengles2_gl2.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_opengles2_gl2ext.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_opengles2_gl2platform.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_opengles2_khrplatform.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_pixels.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_platform.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_power.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_quit.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_rect.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_render.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_revision.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_rwops.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_scancode.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_shape.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_stdinc.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_surface.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_system.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_syswm.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_test.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_test_assert.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_test_common.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_test_compare.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_test_crc32.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_test_font.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_test_fuzzer.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_test_harness.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_test_images.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_test_log.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_test_md5.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_test_memory.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_test_random.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_thread.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_timer.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_touch.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_types.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_version.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_video.h"
    "C:/dev/botijo/3rd_party/sdl2/include/SDL_vulkan.h"
    "C:/dev/botijo/3rd_party/sdl2/include/begin_code.h"
    "C:/dev/botijo/3rd_party/sdl2/include/close_code.h"
    "C:/dev/botijo/3rd_party/sdl2/build_win_x86/include/SDL_config.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/dev/botijo/3rd_party/sdl2/build_win_x86/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
