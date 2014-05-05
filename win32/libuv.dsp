# Microsoft Developer Studio Project File - Name="libuv" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libuv - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libuv.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libuv.mak" CFG="libuv - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libuv - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libuv - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libuv - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "../include/uv-private" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\libuv.lib"

!ELSEIF  "$(CFG)" == "libuv - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "../include/uv-private" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\libuvd.lib"

!ENDIF 

# Begin Target

# Name "libuv - Win32 Release"
# Name "libuv - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\win\async.c
# End Source File
# Begin Source File

SOURCE=..\src\win\core.c
# End Source File
# Begin Source File

SOURCE=..\src\win\dl.c
# End Source File
# Begin Source File

SOURCE=..\src\win\error.c
# End Source File
# Begin Source File

SOURCE="..\src\win\fs-event.c"
# End Source File
# Begin Source File

SOURCE="..\src\fs-poll.c"
# End Source File
# Begin Source File

SOURCE=..\src\win\fs.c
# End Source File
# Begin Source File

SOURCE=..\src\win\getaddrinfo.c
# End Source File
# Begin Source File

SOURCE=..\src\win\handle.c
# End Source File
# Begin Source File

SOURCE=..\src\inet.c
# End Source File
# Begin Source File

SOURCE="..\src\win\loop-watcher.c"
# End Source File
# Begin Source File

SOURCE=..\src\win\pipe.c
# End Source File
# Begin Source File

SOURCE=..\src\win\poll.c
# End Source File
# Begin Source File

SOURCE="..\src\win\process-stdio.c"
# End Source File
# Begin Source File

SOURCE=..\src\win\process.c
# End Source File
# Begin Source File

SOURCE=..\src\win\req.c
# End Source File
# Begin Source File

SOURCE=..\src\win\signal.c
# End Source File
# Begin Source File

SOURCE=..\src\win\stream.c
# End Source File
# Begin Source File

SOURCE=..\src\win\tcp.c
# End Source File
# Begin Source File

SOURCE=..\src\win\thread.c
# End Source File
# Begin Source File

SOURCE=..\src\win\threadpool.c
# End Source File
# Begin Source File

SOURCE=..\src\win\timer.c
# End Source File
# Begin Source File

SOURCE=..\src\win\tty.c
# End Source File
# Begin Source File

SOURCE=..\src\win\udp.c
# End Source File
# Begin Source File

SOURCE=..\src\win\util.c
# End Source File
# Begin Source File

SOURCE="..\src\uv-common.c"
# End Source File
# Begin Source File

SOURCE=..\src\version.c
# End Source File
# Begin Source File

SOURCE=..\src\win\winapi.c
# End Source File
# Begin Source File

SOURCE=..\src\win\winsock.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE="..\src\win\atomicops-inl.h"
# End Source File
# Begin Source File

SOURCE="..\src\win\handle-inl.h"
# End Source File
# Begin Source File

SOURCE=..\src\win\internal.h
# End Source File
# Begin Source File

SOURCE=..\src\queue.h
# End Source File
# Begin Source File

SOURCE="..\src\win\req-inl.h"
# End Source File
# Begin Source File

SOURCE="..\src\win\stream-inl.h"
# End Source File
# Begin Source File

SOURCE="..\src\uv-common.h"
# End Source File
# Begin Source File

SOURCE="..\include\uv-private\uv-win.h"
# End Source File
# Begin Source File

SOURCE=..\include\uv.h
# End Source File
# Begin Source File

SOURCE=..\src\win\winapi.h
# End Source File
# Begin Source File

SOURCE=..\src\win\winsock.h
# End Source File
# End Group
# End Target
# End Project
