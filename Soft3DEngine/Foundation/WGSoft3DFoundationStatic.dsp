# Microsoft Developer Studio Project File - Name="WGSoft3DFoundationStatic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=WGSoft3DFoundationStatic - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WGSoft3DFoundationStatic.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WGSoft3DFoundationStatic.mak" CFG="WGSoft3DFoundationStatic - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WGSoft3DFoundationStatic - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "WGSoft3DFoundationStatic - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WGSoft3DFoundationStatic - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "./Source" /I "./Source/System" /I "./Source/SharedArrays" /I "./Source/SceneGraph" /I "./Source/Rendering" /I "./Source/ObjectSystem" /I "./Source/Mathematics" /I "./Source/Effect" /I "./Source/Controllers" /I "./Source/Containment" /I "./Source/Collision" /I "./Source/Shaders" /I "./Source/Effects" /I "./Source/Intersection" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "WG3D_USE_PRECOMPILED_HEADERS" /YX /FD /c
# ADD BASE RSC /l 0x412 /d "NDEBUG"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../bin/WGSoft3DFoundationStatic.lib"

!ELSEIF  "$(CFG)" == "WGSoft3DFoundationStatic - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "./Source" /I "./Source/System" /I "./Source/SharedArrays" /I "./Source/SceneGraph" /I "./Source/Rendering" /I "./Source/ObjectSystem" /I "./Source/Mathematics" /I "./Source/Effect" /I "./Source/Controllers" /I "./Source/Containment" /I "./Source/Collision" /I "./Source/Shaders" /I "./Source/Effects" /I "./Source/Intersection" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "WG3D_USE_PRECOMPILED_HEADERS" /YX"WgFoundationPCH.h" /FD /GZ /c
# ADD BASE RSC /l 0x412 /d "_DEBUG"
# ADD RSC /l 0x412 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../bin/WGSoft3DFoundationStatic_D.lib"

!ENDIF 

# Begin Target

# Name "WGSoft3DFoundationStatic - Win32 Release"
# Name "WGSoft3DFoundationStatic - Win32 Debug"
# Begin Group "Mathematics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Mathematics\WgColorRGB.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgColorRGB.h
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgColorRGB.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgColorRGBA.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgColorRGBA.h
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgColorRGBA.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgFrustum3.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgFrustum3.h
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgFrustum3.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgLinComp.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgLinComp.h
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgLinComp.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgMath.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgMath.h
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgMath.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgMatrix2.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgMatrix2.h
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgMatrix2.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgMatrix3.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgMatrix3.h
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgMatrix3.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgMatrix4.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgMatrix4.h
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgMatrix4.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgPlane3.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgPlane3.h
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgPlane3.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgRay2.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgRay2.h
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgRay2.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgRay3.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgRay3.h
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgRay3.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgSphere3.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgSphere3.h
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgSphere3.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgTriangle3.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgTriangle3.h
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgTriangle3.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgVector2.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgVector2.h
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgVector2.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgVector3.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgVector3.h
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgVector3.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgVector4.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgVector4.h
# End Source File
# Begin Source File

SOURCE=.\Source\Mathematics\WgVector4.inl
# End Source File
# End Group
# Begin Group "Containment"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Containment\WgContSphere3.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Containment\WgContSphere3.h
# End Source File
# Begin Source File

SOURCE=.\Source\Containment\WgContSphere3.inl
# End Source File
# End Group
# Begin Group "Intersection"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Intersection\WgIntersector.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Intersection\WgIntersector.h
# End Source File
# Begin Source File

SOURCE=.\Source\Intersection\WgIntersector.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Intersection\WgIntrRay3Sphere3.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Intersection\WgIntrRay3Sphere3.h
# End Source File
# Begin Source File

SOURCE=.\Source\Intersection\WgIntrRay3Sphere3.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Intersection\WgIntrRay3Triangle3.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Intersection\WgIntrRay3Triangle3.h
# End Source File
# Begin Source File

SOURCE=.\Source\Intersection\WgIntrRay3Triangle3.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Intersection\WgIntrSphere3Sphere3.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Intersection\WgIntrSphere3Sphere3.h
# End Source File
# Begin Source File

SOURCE=.\Source\Intersection\WgIntrSphere3Sphere3.inl
# End Source File
# End Group
# Begin Group "ObjectSystem"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\ObjectSystem\WgNameID.mcr
# End Source File
# Begin Source File

SOURCE=.\Source\ObjectSystem\WgObject.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\ObjectSystem\WgObject.h
# End Source File
# Begin Source File

SOURCE=.\Source\ObjectSystem\WgObject.inl
# End Source File
# Begin Source File

SOURCE=.\Source\ObjectSystem\WgRtti.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\ObjectSystem\WgRtti.h
# End Source File
# Begin Source File

SOURCE=.\Source\ObjectSystem\WgRtti.inl
# End Source File
# Begin Source File

SOURCE=.\Source\ObjectSystem\WgRtti.mcr
# End Source File
# Begin Source File

SOURCE=.\Source\ObjectSystem\WgSmartPointer.h
# End Source File
# Begin Source File

SOURCE=.\Source\ObjectSystem\WgSmartPointer.inl
# End Source File
# Begin Source File

SOURCE=.\Source\ObjectSystem\WgStringTree.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\ObjectSystem\WgStringTree.h
# End Source File
# Begin Source File

SOURCE=.\Source\ObjectSystem\WgStringTree.inl
# End Source File
# End Group
# Begin Group "Rendering"

# PROP Default_Filter ""
# Begin Group "States"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Rendering\WgAlphaState.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgAlphaState.h
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgCullState.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgCullState.h
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgDitherState.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgDitherState.h
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgFogState.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgFogState.h
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgGlobalState.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgGlobalState.h
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgMaterialState.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgMaterialState.h
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgPolygonOffsetState.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgPolygonOffsetState.h
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgShadeState.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgShadeState.h
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgStencilState.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgStencilState.h
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgZBufferState.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgZBufferState.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Source\Rendering\WgBindInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgBindInfo.h
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgBufferParams.h
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgImage.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgImage.h
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgImage.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgPBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgPBuffer.h
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgRenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgRenderer.h
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgRenderer.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgTexture.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgTexture.h
# End Source File
# Begin Source File

SOURCE=.\Source\Rendering\WgTexture.inl
# End Source File
# End Group
# Begin Group "SceneGraph"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\SceneGraph\WgBoundingVolume.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgBoundingVolume.h
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgCamera.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgCamera.h
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgCamera.inl
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgGeometry.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgGeometry.h
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgGeometry.inl
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgLight.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgLight.h
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgLight.inl
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgNode.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgNode.h
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgNode.inl
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgScreenPolygon.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgScreenPolygon.h
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgScreenPolygon.inl
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgSpatial.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgSpatial.h
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgSpatial.inl
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgSphereBV.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgSphereBV.h
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgSphereBV.inl
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgTransformation.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgTransformation.h
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgTransformation.inl
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgTriangles.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgTriangles.h
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgTriMesh.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgTriMesh.h
# End Source File
# Begin Source File

SOURCE=.\Source\SceneGraph\WgTriMesh.inl
# End Source File
# End Group
# Begin Group "SharedArrays"

# PROP Default_Filter ""
# Begin Group "CachedArrays"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\SharedArrays\WgCachedColorRGBAArray.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgCachedColorRGBAArray.h
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgCachedColorRGBArray.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgCachedColorRGBArray.h
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgCachedShortArray.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgCachedShortArray.h
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgCachedVector2Array.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgCachedVector2Array.h
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgCachedVector3Array.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgCachedVector3Array.h
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgTCachedArray.h
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgTCachedArray.inl
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgTCachedArrayDestructor.inl
# End Source File
# End Group
# Begin Source File

SOURCE=.\Source\SharedArrays\WgColorRGBAArray.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgColorRGBAArray.h
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgColorRGBArray.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgColorRGBArray.h
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgShortArray.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgShortArray.h
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgTSharedArray.h
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgTSharedArray.inl
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgVector2Array.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgVector2Array.h
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgVector3Array.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\SharedArrays\WgVector3Array.h
# End Source File
# End Group
# Begin Group "System"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\System\WgFixed.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\System\WgFixed.h
# End Source File
# Begin Source File

SOURCE=.\Source\System\WgFixed.inl
# End Source File
# Begin Source File

SOURCE=.\Source\System\WgMemory.h
# End Source File
# Begin Source File

SOURCE=.\Source\System\WgPlatforms.h
# End Source File
# Begin Source File

SOURCE=.\Source\System\WgSinTable.h
# End Source File
# Begin Source File

SOURCE=.\Source\System\WgString.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\System\WgString.h
# End Source File
# Begin Source File

SOURCE=.\Source\System\WgString.inl
# End Source File
# Begin Source File

SOURCE=.\Source\System\WgSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\System\WgSystem.h
# End Source File
# Begin Source File

SOURCE=.\Source\System\WgTArray.h
# End Source File
# Begin Source File

SOURCE=.\Source\System\WgTArray.inl
# End Source File
# Begin Source File

SOURCE=.\Source\System\WgTHashTable.h
# End Source File
# Begin Source File

SOURCE=.\Source\System\WgTHashTable.inl
# End Source File
# Begin Source File

SOURCE=.\Source\System\WgTList.h
# End Source File
# Begin Source File

SOURCE=.\Source\System\WgTList.inl
# End Source File
# Begin Source File

SOURCE=.\Source\System\WgTStack.h
# End Source File
# Begin Source File

SOURCE=.\Source\System\WgTStack.inl
# End Source File
# End Group
# Begin Group "Controllers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Controllers\WgController.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Controllers\WgController.h
# End Source File
# Begin Source File

SOURCE=.\Source\Controllers\WgController.inl
# End Source File
# End Group
# Begin Group "Shaders"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Shaders\WgShaderConstant.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Shaders\WgShaderConstant.h
# End Source File
# Begin Source File

SOURCE=.\Source\Shaders\WgShaderConstant.inl
# End Source File
# End Group
# Begin Group "Effects"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Source\Effects\WgBumpMapEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgBumpMapEffect.h
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgBumpMapEffect.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgDarkMapEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgDarkMapEffect.h
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgEffect.h
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgEnvironmentMapEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgEnvironmentMapEffect.h
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgGlossMapEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgGlossMapEffect.h
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgLightMapEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgLightMapEffect.h
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgPlanarShadowEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgPlanarShadowEffect.h
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgPlanarShadowEffect.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgProjectedTextureEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgProjectedTextureEffect.h
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgProjectedTextureEffect.inl
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgTextureEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgTextureEffect.h
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgVertexColorEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Effects\WgVertexColorEffect.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Source\WgFoundation.h
# End Source File
# Begin Source File

SOURCE=.\Source\WgFoundationLIB.h
# End Source File
# Begin Source File

SOURCE=.\Source\WgFoundationPCH.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\WgFoundationPCH.h
# End Source File
# End Target
# End Project
