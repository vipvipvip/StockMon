# Microsoft Developer Studio Project File - Name="StockMon" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=StockMon - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "StockMon.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "StockMon.mak" CFG="StockMon - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StockMon - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "StockMon - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/", aaaaaaaa"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "StockMon - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "c:\temp\DevStudio\StockMon\Release"
# PROP Intermediate_Dir "c:\temp\DevStudio\StockMon\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_CRYPT32_" /D "_WIN32_WINNT" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D _WIN32_WINNT=0x0400 /D "_AFXDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib winmm.lib crypt32.lib. /nologo /subsystem:windows /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy .\Release\stockmon.exe .\Distrib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "StockMon - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "c:\temp\DevStudio\StockMon\Debug"
# PROP Intermediate_Dir "c:\temp\DevStudio\StockMon\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D _WIN32_WINNT=0x0400 /D "WIN32" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 version.lib winmm.lib advapi32.lib crypt32.lib. /nologo /subsystem:windows /debug /machine:I386

!ENDIF 

# Begin Target

# Name "StockMon - Win32 Release"
# Name "StockMon - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\AuthKey.cpp
# End Source File
# Begin Source File

SOURCE=.\BrowserVw.cpp
# End Source File
# Begin Source File

SOURCE=.\DataFile.cpp
# End Source File
# Begin Source File

SOURCE=.\FundaVw.cpp
# End Source File
# Begin Source File

SOURCE=.\IAccess.cpp
# End Source File
# Begin Source File

SOURCE=.\LISTVWEX.CPP
# End Source File
# Begin Source File

SOURCE=.\mainfrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MktSumVw.cpp
# End Source File
# Begin Source File

SOURCE=.\PERSIST.CPP
# End Source File
# Begin Source File

SOURCE=.\ReadMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\Request.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenVw.cpp
# End Source File
# Begin Source File

SOURCE=.\SMDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SMView.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# End Source File
# Begin Source File

SOURCE=.\StkTickr.cpp
# End Source File
# Begin Source File

SOURCE=.\StockMon.cpp
# End Source File
# Begin Source File

SOURCE=.\StockMon.rc
# End Source File
# Begin Source File

SOURCE=.\TechChrt.cpp
# End Source File
# Begin Source File

SOURCE=.\Thread.cpp
# End Source File
# Begin Source File

SOURCE=.\TradeInf.cpp
# End Source File
# Begin Source File

SOURCE=.\ui.cpp
# End Source File
# Begin Source File

SOURCE=.\Valuation.cpp
# End Source File
# Begin Source File

SOURCE=.\WWW.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\AuthKey.h
# End Source File
# Begin Source File

SOURCE=.\BrowserVw.h
# End Source File
# Begin Source File

SOURCE=.\DataFile.h
# End Source File
# Begin Source File

SOURCE=.\FundaVw.h
# End Source File
# Begin Source File

SOURCE=.\IACCESS.H
# End Source File
# Begin Source File

SOURCE=.\LISTVWEX.H
# End Source File
# Begin Source File

SOURCE=.\mainfrm.h
# End Source File
# Begin Source File

SOURCE=.\MKTSUMVW.H
# End Source File
# Begin Source File

SOURCE=.\PERSIST.H
# End Source File
# Begin Source File

SOURCE=.\READMSG.H
# End Source File
# Begin Source File

SOURCE=.\Request.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\ScreenVw.h
# End Source File
# Begin Source File

SOURCE=.\SMDOC.H
# End Source File
# Begin Source File

SOURCE=.\SMView.h
# End Source File
# Begin Source File

SOURCE=.\STDAFX.H
# End Source File
# Begin Source File

SOURCE=.\STKTICKR.H
# End Source File
# Begin Source File

SOURCE=.\STOCKMON.H
# End Source File
# Begin Source File

SOURCE=.\TechChrt.h
# End Source File
# Begin Source File

SOURCE=.\THREAD.H
# End Source File
# Begin Source File

SOURCE=.\TradeInf.h
# End Source File
# Begin Source File

SOURCE=.\ui.h
# End Source File
# Begin Source File

SOURCE=.\UMAPI.H
# End Source File
# Begin Source File

SOURCE=.\Valuation.h
# End Source File
# Begin Source File

SOURCE=.\WWW.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ARROWS1.BMP
# End Source File
# Begin Source File

SOURCE=.\res\BBB16BMP.BMP
# End Source File
# Begin Source File

SOURCE=.\res\BMP00002.BMP
# End Source File
# Begin Source File

SOURCE=.\res\ICON1.ICO
# End Source File
# Begin Source File

SOURCE=.\res\STATEICO.BMP
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# End Target
# End Project
