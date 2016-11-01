# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101
# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=AuthKey - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to AuthKey - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "StockMon - Win32 Release" && "$(CFG)" !=\
 "StockMon - Win32 Debug" && "$(CFG)" != "SM - Win32 Release" && "$(CFG)" !=\
 "SM - Win32 Debug" && "$(CFG)" != "AuthKey - Win32 Release" && "$(CFG)" !=\
 "AuthKey - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "STOCKMON.MAK" CFG="AuthKey - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StockMon - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "StockMon - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "SM - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SM - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AuthKey - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AuthKey - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "StockMon - Win32 Debug"

!IF  "$(CFG)" == "StockMon - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\STOCKMON.exe"

CLEAN : 
	-@erase "$(INTDIR)\AuthKey.obj"
	-@erase "$(INTDIR)\IAccess.obj"
	-@erase "$(INTDIR)\listvwex.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\MktSumVw.obj"
	-@erase "$(INTDIR)\PERSIST.OBJ"
	-@erase "$(INTDIR)\ReadMsg.obj"
	-@erase "$(INTDIR)\Request.obj"
	-@erase "$(INTDIR)\SMDoc.obj"
	-@erase "$(INTDIR)\SMView.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\StkTickr.obj"
	-@erase "$(INTDIR)\StockMon.obj"
	-@erase "$(INTDIR)\Thread.obj"
	-@erase "$(INTDIR)\ui.obj"
	-@erase "$(OUTDIR)\STOCKMON.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/STOCKMON.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/STOCKMON.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib winmm.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=version.lib winmm.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/STOCKMON.pdb" /machine:I386 /out:"$(OUTDIR)/STOCKMON.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AuthKey.obj" \
	"$(INTDIR)\IAccess.obj" \
	"$(INTDIR)\listvwex.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\MktSumVw.obj" \
	"$(INTDIR)\PERSIST.OBJ" \
	"$(INTDIR)\ReadMsg.obj" \
	"$(INTDIR)\Request.obj" \
	"$(INTDIR)\SMDoc.obj" \
	"$(INTDIR)\SMView.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\StkTickr.obj" \
	"$(INTDIR)\StockMon.obj" \
	"$(INTDIR)\Thread.obj" \
	"$(INTDIR)\ui.obj"

"$(OUTDIR)\STOCKMON.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "StockMon - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\STOCKMON.exe"

CLEAN : 
	-@erase "$(INTDIR)\AuthKey.obj"
	-@erase "$(INTDIR)\IAccess.obj"
	-@erase "$(INTDIR)\listvwex.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\MktSumVw.obj"
	-@erase "$(INTDIR)\PERSIST.OBJ"
	-@erase "$(INTDIR)\ReadMsg.obj"
	-@erase "$(INTDIR)\Request.obj"
	-@erase "$(INTDIR)\SMDoc.obj"
	-@erase "$(INTDIR)\SMView.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\StkTickr.obj"
	-@erase "$(INTDIR)\StockMon.obj"
	-@erase "$(INTDIR)\Thread.obj"
	-@erase "$(INTDIR)\ui.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\STOCKMON.exe"
	-@erase "$(OUTDIR)\STOCKMON.ilk"
	-@erase "$(OUTDIR)\STOCKMON.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/STOCKMON.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/STOCKMON.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 version.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=version.lib winmm.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/STOCKMON.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/STOCKMON.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AuthKey.obj" \
	"$(INTDIR)\IAccess.obj" \
	"$(INTDIR)\listvwex.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\MktSumVw.obj" \
	"$(INTDIR)\PERSIST.OBJ" \
	"$(INTDIR)\ReadMsg.obj" \
	"$(INTDIR)\Request.obj" \
	"$(INTDIR)\SMDoc.obj" \
	"$(INTDIR)\SMView.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\StkTickr.obj" \
	"$(INTDIR)\StockMon.obj" \
	"$(INTDIR)\Thread.obj" \
	"$(INTDIR)\ui.obj"

"$(OUTDIR)\STOCKMON.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SM - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SM\Release"
# PROP BASE Intermediate_Dir "SM\Release"
# PROP BASE Target_Dir "SM"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "."
# PROP Intermediate_Dir "TEMP"
# PROP Target_Dir "SM"
OUTDIR=.\.
INTDIR=.\TEMP

ALL : "$(OUTDIR)\SM.dll"

CLEAN : 
	-@erase "$(INTDIR)\StockMon.res"
	-@erase "$(OUTDIR)\SM.dll"
	-@erase "$(OUTDIR)\SM.exp"
	-@erase "$(OUTDIR)\SM.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/SM.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\TEMP/
CPP_SBRS=.\.

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/StockMon.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SM.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386 /NOENTRY
# SUBTRACT LINK32 /debug
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386\
 /out:"$(OUTDIR)/SM.dll" /implib:"$(OUTDIR)/SM.lib" /NOENTRY 
LINK32_OBJS= \
	"$(INTDIR)\StockMon.res"

"$(OUTDIR)\SM.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SM - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SM\Debug"
# PROP BASE Intermediate_Dir "SM\Debug"
# PROP BASE Target_Dir "SM"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "TEMP"
# PROP Target_Dir "SM"
OUTDIR=.\.
INTDIR=.\TEMP

ALL : "$(OUTDIR)\SM.dll"

CLEAN : 
	-@erase "$(INTDIR)\StockMon.res"
	-@erase "$(OUTDIR)\SM.dll"
	-@erase "$(OUTDIR)\SM.exp"
	-@erase "$(OUTDIR)\SM.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/SM.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\TEMP/
CPP_SBRS=.\.

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/StockMon.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/SM.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386 /NOENTRY
# SUBTRACT LINK32 /debug
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /pdb:none /machine:I386\
 /out:"$(OUTDIR)/SM.dll" /implib:"$(OUTDIR)/SM.lib" /NOENTRY 
LINK32_OBJS= \
	"$(INTDIR)\StockMon.res"

"$(OUTDIR)\SM.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AuthKey - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "AuthKey\Release"
# PROP BASE Intermediate_Dir "AuthKey\Release"
# PROP BASE Target_Dir "AuthKey"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "AuthKey\Release"
# PROP Intermediate_Dir "AuthKey\Release"
# PROP Target_Dir "AuthKey"
OUTDIR=.\AuthKey\Release
INTDIR=.\AuthKey\Release

ALL : "$(OUTDIR)\AuthKey.exe"

CLEAN : 
	-@erase "$(INTDIR)\AuthKey.obj"
	-@erase "$(INTDIR)\AuthKey.pch"
	-@erase "$(INTDIR)\AuthKey.res"
	-@erase "$(INTDIR)\AuthKeyDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\AuthKey.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/AuthKey.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\AuthKey\Release/
CPP_SBRS=.\.

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/AuthKey.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/AuthKey.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/AuthKey.pdb" /machine:I386 /out:"$(OUTDIR)/AuthKey.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AuthKey.obj" \
	"$(INTDIR)\AuthKey.res" \
	"$(INTDIR)\AuthKeyDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\AuthKey.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AuthKey - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AuthKey\Debug"
# PROP BASE Intermediate_Dir "AuthKey\Debug"
# PROP BASE Target_Dir "AuthKey"
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "AuthKey\Debug"
# PROP Intermediate_Dir "AuthKey\Debug"
# PROP Target_Dir "AuthKey"
OUTDIR=.\AuthKey\Debug
INTDIR=.\AuthKey\Debug

ALL : "$(OUTDIR)\AuthKey.exe"

CLEAN : 
	-@erase "$(INTDIR)\AuthKey.obj"
	-@erase "$(INTDIR)\AuthKey.pch"
	-@erase "$(INTDIR)\AuthKey.res"
	-@erase "$(INTDIR)\AuthKeyDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\AuthKey.exe"
	-@erase "$(OUTDIR)\AuthKey.ilk"
	-@erase "$(OUTDIR)\AuthKey.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/AuthKey.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\AuthKey\Debug/
CPP_SBRS=.\.

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL=mktyplib.exe
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
RSC=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/AuthKey.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/AuthKey.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/AuthKey.pdb" /debug /machine:I386 /out:"$(OUTDIR)/AuthKey.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AuthKey.obj" \
	"$(INTDIR)\AuthKey.res" \
	"$(INTDIR)\AuthKeyDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\AuthKey.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

################################################################################
# Begin Target

# Name "StockMon - Win32 Release"
# Name "StockMon - Win32 Debug"

!IF  "$(CFG)" == "StockMon - Win32 Release"

!ELSEIF  "$(CFG)" == "StockMon - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\mainfrm.cpp
DEP_CPP_MAINF=\
	".\AuthKey.h"\
	".\LISTVWEX.H"\
	".\mainfrm.h"\
	".\PERSIST.H"\
	".\SMDOC.H"\
	".\SMView.h"\
	".\STDAFX.H"\
	".\STOCKMON.H"\
	

"$(INTDIR)\mainfrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SMDoc.cpp
DEP_CPP_SMDOC=\
	".\AuthKey.h"\
	".\SMDOC.H"\
	".\STDAFX.H"\
	".\STKTICKR.H"\
	".\STOCKMON.H"\
	

"$(INTDIR)\SMDoc.obj" : $(SOURCE) $(DEP_CPP_SMDOC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SMView.cpp
DEP_CPP_SMVIE=\
	".\AuthKey.h"\
	".\IACCESS.H"\
	".\LISTVWEX.H"\
	".\MKTSUMVW.H"\
	".\READMSG.H"\
	".\Request.h"\
	".\SMDOC.H"\
	".\SMView.h"\
	".\STDAFX.H"\
	".\STKTICKR.H"\
	".\STOCKMON.H"\
	".\THREAD.H"\
	".\ui.h"\
	".\UMAPI.H"\
	

"$(INTDIR)\SMView.obj" : $(SOURCE) $(DEP_CPP_SMVIE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\stdafx.cpp
DEP_CPP_STDAF=\
	".\STDAFX.H"\
	

"$(INTDIR)\stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StockMon.cpp
DEP_CPP_STOCK=\
	".\AuthKey.h"\
	".\LISTVWEX.H"\
	".\mainfrm.h"\
	".\PERSIST.H"\
	".\SMDOC.H"\
	".\SMView.h"\
	".\STDAFX.H"\
	".\STOCKMON.H"\
	

"$(INTDIR)\StockMon.obj" : $(SOURCE) $(DEP_CPP_STOCK) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StkTickr.cpp
DEP_CPP_STKTI=\
	".\AuthKey.h"\
	".\STDAFX.H"\
	".\STKTICKR.H"\
	".\STOCKMON.H"\
	

"$(INTDIR)\StkTickr.obj" : $(SOURCE) $(DEP_CPP_STKTI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Thread.cpp
DEP_CPP_THREA=\
	".\AuthKey.h"\
	".\IACCESS.H"\
	".\LISTVWEX.H"\
	".\READMSG.H"\
	".\Request.h"\
	".\SMDOC.H"\
	".\SMView.h"\
	".\STDAFX.H"\
	".\STOCKMON.H"\
	".\THREAD.H"\
	

"$(INTDIR)\Thread.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IAccess.cpp
DEP_CPP_IACCE=\
	".\AuthKey.h"\
	".\IACCESS.H"\
	".\mainfrm.h"\
	".\PERSIST.H"\
	".\STDAFX.H"\
	".\STOCKMON.H"\
	

"$(INTDIR)\IAccess.obj" : $(SOURCE) $(DEP_CPP_IACCE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ui.cpp
DEP_CPP_UI_CP=\
	".\AuthKey.h"\
	".\mainfrm.h"\
	".\PERSIST.H"\
	".\SMDOC.H"\
	".\STDAFX.H"\
	".\STKTICKR.H"\
	".\STOCKMON.H"\
	".\ui.h"\
	

"$(INTDIR)\ui.obj" : $(SOURCE) $(DEP_CPP_UI_CP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PERSIST.CPP
DEP_CPP_PERSI=\
	".\AuthKey.h"\
	".\PERSIST.H"\
	".\STDAFX.H"\
	".\STOCKMON.H"\
	

"$(INTDIR)\PERSIST.OBJ" : $(SOURCE) $(DEP_CPP_PERSI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ReadMsg.cpp
DEP_CPP_READM=\
	".\AuthKey.h"\
	".\READMSG.H"\
	".\STDAFX.H"\
	".\STOCKMON.H"\
	

"$(INTDIR)\ReadMsg.obj" : $(SOURCE) $(DEP_CPP_READM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\listvwex.cpp
DEP_CPP_LISTV=\
	".\LISTVWEX.H"\
	".\STDAFX.H"\
	

"$(INTDIR)\listvwex.obj" : $(SOURCE) $(DEP_CPP_LISTV) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MktSumVw.cpp
DEP_CPP_MKTSU=\
	".\AuthKey.h"\
	".\IACCESS.H"\
	".\LISTVWEX.H"\
	".\MKTSUMVW.H"\
	".\READMSG.H"\
	".\SMDOC.H"\
	".\SMView.h"\
	".\STDAFX.H"\
	".\STKTICKR.H"\
	".\STOCKMON.H"\
	".\THREAD.H"\
	".\ui.h"\
	".\UMAPI.H"\
	

"$(INTDIR)\MktSumVw.obj" : $(SOURCE) $(DEP_CPP_MKTSU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Request.cpp
DEP_CPP_REQUE=\
	".\AuthKey.h"\
	".\Request.h"\
	".\STDAFX.H"\
	".\STOCKMON.H"\
	

"$(INTDIR)\Request.obj" : $(SOURCE) $(DEP_CPP_REQUE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\AuthKey.cpp
DEP_CPP_AUTHK=\
	".\AuthKey.h"\
	".\STDAFX.H"\
	".\STOCKMON.H"\
	

"$(INTDIR)\AuthKey.obj" : $(SOURCE) $(DEP_CPP_AUTHK) "$(INTDIR)"


# End Source File
# End Target
################################################################################
# Begin Target

# Name "SM - Win32 Release"
# Name "SM - Win32 Debug"

!IF  "$(CFG)" == "SM - Win32 Release"

!ELSEIF  "$(CFG)" == "SM - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StockMon.rc

!IF  "$(CFG)" == "SM - Win32 Release"

DEP_RSC_STOCKM=\
	".\res\ARROWS1.BMP"\
	".\res\BBB16BMP.BMP"\
	".\res\BMP00002.BMP"\
	".\res\ICON1.ICO"\
	".\res\STATEICO.BMP"\
	".\res\STOCKMON.RC2"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\StockMon.res" : $(SOURCE) $(DEP_RSC_STOCKM) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SM - Win32 Debug"

DEP_RSC_STOCKM=\
	".\res\ARROWS1.BMP"\
	".\res\BBB16BMP.BMP"\
	".\res\BMP00002.BMP"\
	".\res\ICON1.ICO"\
	".\res\STATEICO.BMP"\
	".\res\STOCKMON.RC2"\
	".\res\Toolbar.bmp"\
	

"$(INTDIR)\StockMon.res" : $(SOURCE) $(DEP_RSC_STOCKM) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
################################################################################
# Begin Target

# Name "AuthKey - Win32 Release"
# Name "AuthKey - Win32 Debug"

!IF  "$(CFG)" == "AuthKey - Win32 Release"

!ELSEIF  "$(CFG)" == "AuthKey - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\AuthKey\ReadMe.txt

!IF  "$(CFG)" == "AuthKey - Win32 Release"

!ELSEIF  "$(CFG)" == "AuthKey - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AuthKey\AuthKey.cpp

!IF  "$(CFG)" == "AuthKey - Win32 Release"

DEP_CPP_AUTHK=\
	".\AuthKey\AuthKey.h"\
	".\AuthKey\AuthKeyDlg.h"\
	".\AuthKey\StdAfx.h"\
	

"$(INTDIR)\AuthKey.obj" : $(SOURCE) $(DEP_CPP_AUTHK) "$(INTDIR)"\
 "$(INTDIR)\AuthKey.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "AuthKey - Win32 Debug"

DEP_CPP_AUTHK=\
	".\AuthKey\AuthKey.h"\
	".\AuthKey\AuthKeyDlg.h"\
	".\AuthKey\StdAfx.h"\
	

"$(INTDIR)\AuthKey.obj" : $(SOURCE) $(DEP_CPP_AUTHK) "$(INTDIR)"\
 "$(INTDIR)\AuthKey.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AuthKey\AuthKeyDlg.cpp
DEP_CPP_AUTHKE=\
	".\AuthKey\AuthKey.h"\
	".\AuthKey\AuthKeyDlg.h"\
	".\AuthKey\StdAfx.h"\
	

"$(INTDIR)\AuthKeyDlg.obj" : $(SOURCE) $(DEP_CPP_AUTHKE) "$(INTDIR)"\
 "$(INTDIR)\AuthKey.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\AuthKey\StdAfx.cpp
DEP_CPP_STDAFX=\
	".\AuthKey\StdAfx.h"\
	

!IF  "$(CFG)" == "AuthKey - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/AuthKey.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAFX) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\AuthKey.pch" : $(SOURCE) $(DEP_CPP_STDAFX) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "AuthKey - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/AuthKey.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAFX) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\AuthKey.pch" : $(SOURCE) $(DEP_CPP_STDAFX) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AuthKey\AuthKey.rc
DEP_RSC_AUTHKEY=\
	".\AuthKey\res\AuthKey.ico"\
	".\AuthKey\res\AuthKey.rc2"\
	

!IF  "$(CFG)" == "AuthKey - Win32 Release"


"$(INTDIR)\AuthKey.res" : $(SOURCE) $(DEP_RSC_AUTHKEY) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/AuthKey.res" /i "AuthKey" /d "NDEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ELSEIF  "$(CFG)" == "AuthKey - Win32 Debug"


"$(INTDIR)\AuthKey.res" : $(SOURCE) $(DEP_RSC_AUTHKEY) "$(INTDIR)"
   $(RSC) /l 0x409 /fo"$(INTDIR)/AuthKey.res" /i "AuthKey" /d "_DEBUG" /d\
 "_AFXDLL" $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
