file(GLOB CAPSTAN_WIN32_SOURCES "${CAPSTAN_SOURCE_DIR}/Platform/Win32/*.cpp")

add_definitions(-DCAPSTAN_DEBUG -DCAPSTAN_WINDOWS)

if (MSVC)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
endif()


add_executable(capstan ${CAPSTAN_SOURCES} ${CAPSTAN_WIN32_SOURCES} Win32Main.cpp)

#  user32.lib gdi32.lib opengl32.lib XInput.lib
# )

# set_property(TARGET capstan PROPERTY LINK_LIBRARIES gdi32.lib opengl32.lib XInput.lib)

target_link_libraries(capstan opengl32.lib XInput.lib)

set_property(TARGET capstan PROPERTY FOLDER "executables")

install(TARGETS capstan RUNTIME DESTINATION ${CAPSTAN_PROJECT_DIR}/build)
