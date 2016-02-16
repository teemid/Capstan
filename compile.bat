@ECHO off

SET PROJECT_PATH=%~dp0
SET BUILD_PATH=%PROJECT_PATH%build
SET INCLUDE_PATH=%PROJECT_PATH%include
SET SOURCE_PATH=%PROJECT_PATH%src
SET EXE_NAME=capstan

REM Create a build directory if it does not exist
IF NOT EXIST %BUILD_PATH% MD %BUILD_PATH%

REM COMPILER OPTIONS
REM /Od     - Disable optimizations
REM /I      - Include directories
REM /c      - Compiles without linking
REM /Fe     - Renames executable file
REM /MT(d)  - Creates a multithreaded executable file using LIBCMT.lib
REM /WX     - Treat warnings like errors
REM /wdn    - Disable warning [n]
REM /Wn     - Specify warning level n=[0..4], /Wall=/W4
REM /Zi     - Produces a program database (PDB) with debugging information
REM /MP[n]  - Use multiple process to compile the code with maximum n process
set COMMON_FLAGS=/nologo /MP
SET COMPILER_FLAGS=/Od /I %INCLUDE_PATH% /c /MTd /WX /W3 /wd4996 /Zi

REM LINKER OPTIONS
REM /PDB    - Creates program database (PDB) debugging information
REM /WX     - Treat linker warnings as errors
SET LINKER_FLAGS=/WX

SET MACRO_DEFINITIONS=/DCAPSTAN_DEBUG /DCAPSTAN_ASSERT /DCAPSTAN_CONSOLE
SET LIB_FILES=user32.lib opengl32.lib gdi32.lib XInput.lib


PUSHD %BUILD_PATH%

FOR /R %SOURCE_PATH% %%G IN (*.cpp) DO cl %COMMON_FLAGS% %COMPILER_FLAGS% "%%G" %MACRO_DEFINITIONS%

link /DEBUG /NOLOGO /OUT:%EXE_NAME%.exe *.obj %LIB_FILES%
REM %COMMON_FLAGS% /Fe%EXE_NAME% /Zi *.obj /link /DEBUG %LINKER_FLAGS% %LIB_FILES%

POPD
