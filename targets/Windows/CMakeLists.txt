file(GLOB CAPSTAN_WIN32_SOURCES "${CAPSTAN_SOURCE_DIR}/Platform/Win32/*.cpp")

add_executable(capstan ${CAPSTAN_SOURCES} ${CAPSTAN_WIN32_SOURCES} Win32Main.cpp)

add_definitions(-DCAPSTAN_DEBUG -DCAPSTAN_WINDOWS -DCAPSTAN_ASSERT)

find_library(WIN_USER_LIB user32)
find_library(WIN_GDI_LIB gdi32)
find_library(XINPUT_LIB XInput)
find_library(OPENGL_LIB opengl32)

set(CAPSTAN_LIBRARIES ${WIN_USER_LIB} ${WIN_GDI_LIB} ${OPENGL_LIB} ${XINPUT_LIB})

if (MSVC)
    set(CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS} /EHsc /Zi /W3 /WX /MP /fp:fast /wd4996")
    set(CMAKE_CXX_FLAGS_DEBUG          "${CMAKE_CXX_FLAGS_DEBUG} /D _DEBUG /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE        "/Oi /Ot /Gy /bigobj")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Oi /Ot /Gy /bigobj /Ob2")

    set(CMAKE_EXE_LINKER_FLAGS "/NOLOGO /DEBUG /SUBSYSTEM:WINDOWS")

    # set(MSVC_COMPILE_FLAGS "/nologo /MP /fp:fast /Oi /EHsc /Od /c /MTd /WX /W3 /wd4996 /Zi")
    # set(MSVC_LINKER_FLAGS "/NOLOGO /DEBUG /SUBSYSTEM:WINDOWS")
endif()

target_link_libraries(capstan ${CAPSTAN_LIBRARIES})

set_property(TARGET capstan PROPERTY FOLDER "executables")

install(TARGETS capstan RUNTIME DESTINATION ${CAPSTAN_PROJECT_DIR}/build)
