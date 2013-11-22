@echo off

cd %~dp0

if /i "%1"=="help" goto help
if /i "%1"=="--help" goto help
if /i "%1"=="-help" goto help
if /i "%1"=="/help" goto help
if /i "%1"=="?" goto help
if /i "%1"=="-?" goto help
if /i "%1"=="--?" goto help
if /i "%1"=="/?" goto help

@rem Process arguments.
set config=
set target=Build
set noprojgen=
set nobuild=
set run=
set target_arch=ia32
set vs_toolset=x86
set platform=WIN32
set library=static_library

:next-arg
if "%1"=="" goto args-done
if /i "%1"=="debug"        set config=Debug&goto arg-ok
if /i "%1"=="release"      set config=Release&goto arg-ok
if /i "%1"=="test"         set run=run-tests.exe&goto arg-ok
if /i "%1"=="bench"        set run=run-benchmarks.exe&goto arg-ok
if /i "%1"=="clean"        set target=Clean&goto arg-ok
if /i "%1"=="noprojgen"    set noprojgen=1&goto arg-ok
if /i "%1"=="nobuild"      set nobuild=1&goto arg-ok
if /i "%1"=="x86"          set target_arch=ia32&set platform=WIN32&set vs_toolset=x86&goto arg-ok
if /i "%1"=="ia32"         set target_arch=ia32&set platform=WIN32&set vs_toolset=x86&goto arg-ok
if /i "%1"=="x64"          set target_arch=x64&set platform=amd64&set vs_toolset=x64&goto arg-ok
if /i "%1"=="shared"       set library=shared_library&goto arg-ok
if /i "%1"=="static"       set library=static_library&goto arg-ok
:arg-ok
shift
goto next-arg
:args-done

:select-target
if not "%config%"=="" goto project-gen
if "%run%"=="run-tests.exe" set config=Debug& goto project-gen
if "%run%"=="run-benchmarks.exe" set config=Release& goto project-gen
set config=Debug

:project-gen
@rem Skip project generation if requested.
if defined noprojgen goto msbuild

@rem Generate the VS project.
if exist build\gyp goto have_gyp
echo git clone https://git.chromium.org/external/gyp.git build/gyp
git clone https://git.chromium.org/external/gyp.git build/gyp
if errorlevel 1 goto gyp_install_failed
goto have_gyp

:gyp_install_failed
echo Failed to download gyp. Make sure you have git installed, or
echo manually install gyp into %~dp0build\gyp.
exit /b 1

:have_gyp
if not defined PYTHON set PYTHON="python"
if errorlevel 1 goto create-msvs-files-failed

if "%nobuild%"=="1" goto nobuild
goto build

:build
%PYTHON% gyp_uv -Dtarget_arch=%target_arch% -Dlibrary=%library% --build %config%
goto run

:nobuild
%PYTHON% gyp_uv -Dtarget_arch=%target_arch% -Dlibrary=%library% --build %config%
goto run

:run
@rem Run tests if requested.
if "%run%"=="" goto exit
if not exist %config%\%run% goto exit
echo running '%config%\%run%'
%config%\%run%
goto exit

:create-msvs-files-failed
echo Failed to create vc project files.
exit /b 1

:help
echo vcbuild.bat [debug/release] [test/bench] [clean] [noprojgen] [nobuild] [x86/x64] [static/shared]
echo Examples:
echo   vcbuild.bat              : builds debug build
echo   vcbuild.bat test         : builds debug build and runs tests
echo   vcbuild.bat release bench: builds release build and runs benchmarks
goto exit

:exit
