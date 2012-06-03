# Microsoft Developer Studio Project File - Name="WGSoft3DOmapGLRenderer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=WGSoft3DOmapGLRenderer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WGSoft3DOmapGLRenderer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WGSoft3DOmapGLRenderer.mak" CFG="WGSoft3DOmapGLRenderer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WGSoft3DOmapGLRenderer - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WGSoft3DOmapGLRenderer - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WGSoft3DOmapGLRenderer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "WGSOFT3DOMAPGLRENDERER_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "./Source" /I "./Source/Renderer" /I "../../include" /I "../../external/OmapGL/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "WG3D_RENDERER_DLL_EXPORT" /D "WG3D_FOUNDATION_DLL_IMPORT" /D "WG3D_USE_PRECOMPILED_HEADERS" /YX"WgOmapGLRendererPCH.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib WGSoft3DFoundation.lib libEGL.lib libgles_cm.lib libgles_cl.lib /nologo /dll /machine:I386 /out:"../../bin/WGSoft3DOmapGLRenderer.dll" /implib:"../../bin/WGSoft3DOmapGLRenderer.lib" /libpath:"./../../bin" /libpath:"../../external/OmapGL/lib"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy /y Source\Renderer\*.h ..\..\Include	copy /y Source\Renderer\*.inl ..\..\Include	copy /y Source\*.h ..\..\Include
# End Special Build Tool

!ELSEIF  "$(CFG)" == "WGSoft3DOmapGLRenderer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "WGSOFT3DOMAPGLRENDERER_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I "./Source" /I "./Source/Renderer" /I "../../include" /I "../../external/OmapGL/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "WG3D_RENDERER_DLL_EXPORT" /D "WG3D_FOUNDATION_DLL_IMPORT" /D "WG3D_USE_PRECOMPILED_HEADERS" /YX"WgOmapGLRendererPCH.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib WGSoft3DFoundation_D.lib libEGL.lib libgles_cm.lib libgles_cl.lib /nologo /dll /debug /machine:I386 /out:"../../bin/WGSoft3DOmapGLRenderer_D.dll" /implib:"../../bin/WGSoft3DOmapGLRenderer_D.lib" /pdbtype:sept /libpath:"./../../bin" /libpath:"../../external/OmapGL/lib"
# SUBTRACT LINK32 /pdb:none /nodefaultlib
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy /y Source\Renderer\*.h ..\..\Include	copy /y Source\Renderer\*.inl ..\..\Include	copy /y Source\*.h ..\..\Include
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "WGSoft3DOmapGLRenderer - Win32 Release"
# Name "WGSoft3DOmapGLRenderer - Win32 Debug"
# Begin Group "Renderer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Renderer\WgOmapGLRenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Renderer\WgOmapGLRenderer.h
# End Source File
# Begin Source File

SOURCE=.\Source\Renderer\WgOmapGLRenderer.inl
# End Source File
# End Group
# Begin Group "States"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Renderer\WgOmapGLAlphaState.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Renderer\WgOmapGLCullState.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Renderer\WgOmapGLDitherState.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Renderer\WgOmapGLFogState.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Renderer\WgOmapGLMaterialState.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Renderer\WgOmapGLPolygonOffsetState.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Renderer\WgOmapGLShadeState.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Renderer\WgOmapGLZBufferState.cpp
# End Source File
# End Group
# Begin Group "Effects"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Renderer\WgOmapGLBumpMap.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Renderer\WgOmapGLEnvironmentMap.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Renderer\WgOmapGLGlossMap.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Renderer\WgOmapGLPlanarShadow.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Renderer\WgOmapGLProjectedTexture.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Source\WgOmapGLRendererLIB.h
# End Source File
# Begin Source File

SOURCE=.\Source\WgOmapGLRendererPCH.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\WgOmapGLRendererPCH.h
# End Source File
# End Target
# End Project
