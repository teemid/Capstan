@echo off

rem IF NOT "%VS140COMNTOOLS%" == "" call \vcvarsall.bat

rem echo %WindowSdkDir%%WindowSDKLibVersion%

SET CMAKE_DIR=_cmake

IF EXIST %CMAKE_DIR% GOTO build

MD _cmake

:build
    PUSHD _cmake

    cmake .. -G "Visual Studio 14 2015"

    POPD

    cmake --build _cmake --config Debug
