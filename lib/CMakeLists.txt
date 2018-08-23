cmake_minimum_required(VERSION 3.4)
project(botijo)

# Define sources:
set(SOURCES
    src/btj_global_pointers.cpp
    src/btj_aligned_allocator.cpp
    src/btj_image.cpp
    src/btj_texture.cpp
    src/btj_texture_region.cpp
    src/btj_textures.cpp
    src/btj_window_config.cpp
    src/btj_window_impl.cpp
    src/btj_layer.cpp
    src/btj_layers.cpp
    src/btj_sprite.cpp
    src/btj_sprites.cpp
    src/btj_graphics.cpp
    src/btj_graphics_impl.cpp
    src/btj_keyboard.cpp
    src/btj_keyboard_impl.cpp
    src/btj_core.cpp
)

# Define backends sources:
set(SOURCES
    ${SOURCES}
    src/sdl_core_backend/btj_core_backend.cpp
    src/sdl_window_backend/btj_window_backend.cpp
    src/opengl_graphics_backend/btj_graphics_backend.cpp
    src/sdl_keyboard_backend/btj_keyboard_backend.cpp
)

# Add a library with the above sources:
add_library(${PROJECT_NAME} ${SOURCES})

# Define include directories:
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Include optional library:
add_subdirectory(../3rd_party/optional optional)
target_link_libraries(${PROJECT_NAME} PUBLIC optional)

# Include string-view-lite library:
add_subdirectory(../3rd_party/string-view-lite string-view-lite)
target_link_libraries(${PROJECT_NAME} PUBLIC string-view-lite)

# Include glm library:
add_subdirectory(../3rd_party/glm glm)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)

# Include SDL2 library:
set("SDL2_DIR" "${CMAKE_CURRENT_SOURCE_DIR}/../3rd_party/sdl2")
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_DIR}/include)

if(CMAKE_COMPILER_IS_MINGW)
    error("MinGW build not supported")
elseif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
    error("ARM build not supported")
else()
    if(WIN32)
        target_link_libraries(${PROJECT_NAME} PRIVATE "${SDL2_DIR}/build_win_x86/SDL2-static.lib")

        target_link_libraries(${PROJECT_NAME} PRIVATE imm32.lib)

        target_link_libraries(${PROJECT_NAME} PRIVATE winmm.lib)

        target_link_libraries(${PROJECT_NAME} PRIVATE version.lib)
    elseif(APPLE)
        target_link_libraries(${PROJECT_NAME} PRIVATE "${SDL2_DIR}/build_mac_x86/libSDL2.a")

	find_library(CORE_VIDEO_LIBRARY CoreVideo)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${CORE_VIDEO_LIBRARY})

	find_library(CORE_AUDIO_LIBRARY CoreAudio)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${CORE_AUDIO_LIBRARY})

	find_library(CORE_GRAPHICS_LIBRARY CoreGraphics)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${CORE_GRAPHICS_LIBRARY})

	find_library(APP_KIT_LIBRARY AppKit)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${APP_KIT_LIBRARY})

	find_library(IO_KIT_LIBRARY IOKit)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${IO_KIT_LIBRARY})

	find_library(AUDIO_TOOLBOX_LIBRARY AudioToolbox)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${AUDIO_TOOLBOX_LIBRARY})

	find_library(FORCE_FEEDBACK_LIBRARY ForceFeedback)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${FORCE_FEEDBACK_LIBRARY})

	find_library(CARBON_LIBRARY Carbon)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${CARBON_LIBRARY})

	find_library(ICONV_LIBRARY iconv)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${ICONV_LIBRARY})
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE "${SDL2_DIR}/build_linux_x86/libSDL2.a")
    endif()
endif()

# Include GLEW library:
set("GLEW_DIR" "${CMAKE_CURRENT_SOURCE_DIR}/../3rd_party/glew")
target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_DIR}/include)

if(CMAKE_COMPILER_IS_MINGW)
    error("MinGW build not supported")
elseif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
    error("ARM build not supported")
else()
    if(WIN32)
        target_link_libraries(${PROJECT_NAME} PRIVATE "${GLEW_DIR}/build_win_x86/glew32s.lib")
    elseif(APPLE)
        target_link_libraries(${PROJECT_NAME} PRIVATE "${GLEW_DIR}/build_mac_x86/libGLEW.a")
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE "${GLEW_DIR}/build_linux_x86/libGLEW.a")
    endif()
endif()

# Include OpenGL library:
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})

# Include stb-image library:
add_subdirectory(../3rd_party/stb-image stb-image)
target_link_libraries(${PROJECT_NAME} PRIVATE stb-image)

# Include dl:
if(CMAKE_COMPILER_IS_GNUCC)
    target_link_libraries(${PROJECT_NAME} PRIVATE dl)
endif()

# Include pthread:
if(CMAKE_COMPILER_IS_GNUCC)
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()
