@echo off

set PLATFORM=WIN32
set BUILD_OS=WIN32
set BLD_PLAT_DIR=WIN32
set TTG_ROOT=\development
set WRL_ROOT=\wrlinux
set WRL_PLAT_ROOT=\wrlsp
set FSS_PSS_ROOT=\pss\fss
set FSS_PTS_ROOT=\pts\fss
set PSOS_VOB=\psos
set LUMOS_VOB=\lumos
set ZLIB_BASE=%TTG_ROOT%\tools\zlib\src
set PSS_ROOT=%PSOS_VOB%\prism_ppc_2.5\pssppc.250
set OSPF_ROOT=\ospf\rev_125-E\src
set DCL_BASE=\dclCommon
set ATMSIM_BASE=\cpCommon\atmsim
set CNTL_PLANE_BASE=\cpCommon\controlPlane
rem When searching for source files, we'll look in
rem CP_PREFERRED first, and CP_ALTERNATE second
set CP_PREFERRED=\
set CP_ALTERNATE=\cpCommon\
set CP_MAKE_ROOT=\cpCommon\atmsim\make
set ECPE_ESW_BASE=\ecpe_eswitch
set ECPE_PROTOCOL_BASE=\ecpe_eswitch\iss\code\future

rem
rem Doxygen automated doc generator
set DOX_VERSION=1.2.18
set DOX_PATH=%TTG_ROOT%\tools\doxygen\%DOX_VERSION%

set CYGWIN=nodosfilewarning igncr

rem
rem Visual Developer Studio
rem while the environment variables below can be overridden in a user
rem login and allow Studio to be installed at a location other than
rem C:\Program Files\..., it is highly recommended Visual Studio
rem still be installed at C:\ for derived object wink in and do-pool storage
rem
if "%VC8Drive%" == "" set VC8Drive=C

set VC8rroot=%VC8Drive%:\Program Files\Microsoft Visual Studio 8
if "%PROCESSOR_ARCHITECTURE%" == "AMD64" set BUILD_ARCHITECTURE=64BIT
if "%BUILD_ARCHITECTURE%" == "64BIT" set VC8rroot=%VC8Drive%:\Program Files (x86)\Microsoft Visual Studio 8

rem echo Setting VSCommonDir
if "%VSCommonDir%" == "" set VSCommonDir=%VC8rroot%\Common7
rem echo Setting MSDevDir
if "%MSDevDir%" == "" set MSDevDir=%VC8rroot%\Common7\IDE
rem echo Setting MSVCDir
if "%MSVCDir%" == "" set MSVCDir=%VC8rroot%\VC
rem echo Setting Platform SDK directory
if "%MSPlatformSDKDir%" == "" set MSPlatformSDKDir=%VC8Drive%:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2
rem Let's verify that the user has installed the compiler and SDK properly.
if not exist "%VSCommonDir%" echo. %VSCommonDir% is missing! Please properly install Visual Studio 8.
if not exist "%MSDevDir%" echo. %MSDevDir% is missing! Please properly install Visual Studio 8.
if not exist "%MSVCDir%" echo. %MSVCDir% is missing! Please properly install Visual Studio 8.
if not exist "%MSPlatformSDKDir%" echo. %MSPlatformSDKDir% is missing! Please properly install Platform SDK.

rem
rem VcOsDir is used to help create either a Windows 95 or Windows NT specific path.
rem
set VcOsDir=WIN95
if "%OS%" == "Windows_NT" set VcOsDir=WINNT

rem
echo Setting environment for using Microsoft Visual C++ tools.
rem

if "%win32BatchFileUsed%" == "" if "%OS%" == "Windows_NT" set PATH=%TTG_ROOT%\tools;%DOX_PATH%;%MSDevDir%;%MSVCDir%\BIN;%VSCommonDir%\TOOLS\%VcOsDir%;%VSCommonDir%\TOOLS;%PATH%
if "%win32BatchFileUsed%" == "" if "%OS%" == "" set PATH="%TTG_ROOT%\tools";"%DOX_PATH%";"%MSDevDir%";"%MSVCDir%\BIN";"%VSCommonDir%\TOOLS\%VcOsDir%";"%VSCommonDir%\TOOLS";"%windir%\SYSTEM";"%PATH%"
if "%win32BatchFileUsed%" == "" set include=%MSVCDir%\ATL\INCLUDE;%MSVCDir%\INCLUDE;%MSVCDir%\MFC\INCLUDE;%MSVCDir%\PlatformSDK\INCLUDE;%INCLUDE%;%MSPlatformSDKDir%\Include
if "%win32BatchFileUsed%" == "" set lib=%MSPlatformSDKDir%\Lib;%MSVCDir%\LIB;%MSVCDir%\MFC\LIB;%MSVCDir%\PlatformSDK\LIB

rem clearmake declarations
set CMAKE_PNAME_SEP=\
set CCASE_CONC_V6_OBSOLETE=yes

set VcOsDir=
set VSCommonDir=

set win32BatchFileUsed=true
cleartool pwv | awk 'BEGIN {print "@echo off"} length($4)!=0 {print "title "$4" for WIN32"}' > %TEMP%\PromptViewName.bat
call %TEMP%\PromptViewName.bat
del %TEMP%\PromptViewName.bat
color 71

rem ---- Set the view's cache to 4meg now done automatically by the server when the view is created...

set CCASE_OPTS_SPECS=%TTG_ROOT%\proj\makeopt.WIN32

set CCASE_BLD_UMASK=002

