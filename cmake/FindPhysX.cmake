message("Running FindPhysx")

SET (PHYSX_SEARCH_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../deps/physx)
SET (PHYSX_DEFAULT_LIBDIR ${PHYSX_SEARCH_PATH}/lib)
SET	(PHYSX_DEFAULT_INCLUDE ${PHYSX_SEARCH_PATH}/include)
SET (PHYSX_LIBDIR_DEBUG ${PHYSX_DEFAULT_LIBDIR}/debug)
SET (PHYSX_LIBDIR_RELEASE ${PHYSX_DEFAULT_LIBDIR}/release)

# Find include path

FIND_PATH(
	PHYSX_INCLUDE_DIR
	PxPhysicsAPI.h
	PATHS ${PHYSX_DEFAULT_INCLUDE}
)

# Finds Release Libraries

FIND_LIBRARY (
	PHYSX_LIBRARY
	NAMES PhysX3_x86 PhysX3_x64 PhysX3
	PATHS ${PHYSX_LIBDIR_RELEASE}
)
FIND_LIBRARY (
	PHYSX_COMMON_LIBRARY
	NAMES PhysX3Common_x86 PhysX3Common_x64 PhysX3Common
	PATHS ${PHYSX_LIBDIR_RELEASE}
	)
	
FIND_LIBRARY (
	PHYSX_COOKING_LIBRARY
	NAMES PhysX3Cooking_x86 PhysX3Cooking_x64 PhysX3Cooking
	PATHS ${PHYSX_LIBDIR_RELEASE}
	)
	
FIND_LIBRARY (
	PHYSX_PROFILE_SDK_LIBRARY
	NAMES PhysXProfileSDK_x86 PhysXProfileSDK_x64 PhysXProfileSDK
	PATHS ${PHYSX_LIBDIR_RELEASE}
	)
	
FIND_LIBRARY (
	PHYSX_EX_LIBRARY
	PHYSX_EX_LIBRARY
	NAMES PhysX3Extensions_x86 PhysX3Extensions_x64 PhysX3Extensions
	PATHS ${PHYSX_LIBDIR_RELEASE}
	)

# Finds debug libraries

FIND_LIBRARY (
	PHYSX_LIBRARY_DEBUG
	NAMES PhysX3DEBUG_x86 PhysX3DEBUG_x64 PhysX3DEBUG
	PATHS ${PHYSX_LIBDIR_DEBUG}
	)
	
FIND_LIBRARY (
	PHYSX_COMMON_LIBRARY_DEBUG
	NAMES PhysX3CommonDEBUG_x86 PhysX3CommonDEBUG_x64 PhysX3CommonDEBUG
	PATHS ${PHYSX_LIBDIR_DEBUG}
	)
	
FIND_LIBRARY (
	PHYSX_COOKING_LIBRARY_DEBUG
	NAMES PhysX3CookingDEBUG_x86 PhysX3CookingDEBUG_x64 PhysX3CookingDEBUG
	PATHS ${PHYSX_LIBDIR_DEBUG}
	)

FIND_LIBRARY (
	PHYSX_PROFILE_SDK_LIBRARY_DEBUG
	NAMES PhysXProfileSDKDEBUG_x86 PhysXProfileSDKDEBUG_x64 PhysXProfileSDKDEBUG
	PATHS ${PHYSX_LIBDIR_DEBUG}
	)
	
FIND_LIBRARY (
	PHYSX_EX_LIBRARY_DEBUG
	NAMES PhysX3ExtensionsDEBUG_x86 PhysX3ExtensionsDEBUG_x64 PhysX3ExtensionsDEBUG
	PATHS ${PHYSX_LIBDIR_DEBUG}
	)

IF(PHYSX_LIBRARY AND PHYSX_COMMON_LIBRARY AND PHYSX_COOKING_LIBRARY AND PHYSX_PROFILE_SDK_LIBRARY AND PHYSX_EX_LIBRARY AND 
	PHYSX_LIBRARY_DEBUG AND PHYSX_COMMON_LIBRARY_DEBUG AND PHYSX_COOKING_LIBRARY_DEBUG AND PHYSX_PROFILE_SDK_LIBRARY_DEBUG AND PHYSX_EX_LIBRARY_DEBUG AND PHYSX_INCLUDE_DIR)
	SET(PHYSX_FOUND "YES")
ELSE()
	SET(PHYSX_FOUND "NO")
ENDIF()