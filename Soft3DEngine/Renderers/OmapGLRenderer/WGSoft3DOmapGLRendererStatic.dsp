# Microsoft Developer Studio Project File - Name="WGSoft3DOmapGLRendererStatic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=WGSoft3DOmapGLRendererStatic - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WGSoft3DOmapGLRendererStatic.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WGSoft3DOmapGLRendererStatic.mak" CFG="WGSoft3DOmapGLRendererStatic - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WGSoft3DOmapGLRendererStatic - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "WGSoft3DOmapGLRendererStatic - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WGSoft3DOmapGLRendererStatic - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "./Source" /I "./Source/Renderer" /I "../../include" /I "../../external/OmapGL/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "WG3D_USE_PRECOMPILED_HEADERS" /YX"WgOmapGLRendererPCH.h" /FD /c
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../bin/WGSoft3DOmapGLRendererStatic.lib"

!ELSEIF  "$(CFG)" == "WGSoft3DOmapGLRendererStatic - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "./Source" /I "./Source/Renderer" /I "../../include" /I "../../external/OmapGL/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "WG3D_USE_PRECOMPILED_HEADERS" /YX"WgOmapGLRendererPCH.h" /FD /GZ /c
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../bin/WGSoft3DOmapGLRendererStatic_D.lib"

!ENDIF 

# Begin Target

# Name "WGSoft3DOmapGLRendererStatic - Win32 Release"
# Name "WGSoft3DOmapGLRendererStatic - Win32 Debug"
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
