cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

project(zEngine C CXX)

if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

if(NOT "${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
endif()

set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
)

include(CMake/GlobalSettingsInclude.cmake OPTIONAL)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(PROJECT_NAME zEngine)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "Engine/Component/Model/Model.cpp"
    "Engine/Component/Model/Model.h"
    "Engine/Core/InputSystem/InputSystem.cpp"
    "Engine/Core/InputSystem/InputSystem.h"
    "Engine/Core/TextureAssimp/TextureAssimp.cpp"
    "Engine/Core/TextureAssimp/TextureAssimp.h"
    "Engine/Core/Vertex/Vertex.cpp"
    "Engine/Core/Vertex/Vertex.h"
    "Engine/SubSystem/AssetSystem.cpp"
    "Engine/SubSystem/AssetSystem.h"
    "Header.h"
    "Levels/BoxWithMat/DrawBoxWithMat.cpp"
    "Levels/BoxWithMat/DrawBoxWithMat.h"
    "Levels/DrawAdvanceLight/DrawAdvanceLight.cpp"
    "Levels/DrawAdvanceLight/DrawAdvanceLight.h"
    "Levels/NanoSuit0/DrawNanosuit.cpp"
    "Levels/NanoSuit0/DrawNanosuit.h"
    "main.cpp"
    "MeshData/Box/Mesh_Box.cpp"
    "MeshData/Box/Mesh_Box.h"
    "Objects/BoxWithMaterial.cpp"
    "Objects/BoxWithMaterial.h"
    "Objects/DrawAdvanceBox/BoxV3.cpp"
    "Objects/DrawAdvanceBox/BoxV3.h"
    "Objects/DriectLight/DriectLight.cpp"
    "Objects/DriectLight/DriectLight.h"
    "Objects/PointLight/PointLightV3.cpp"
    "Objects/PointLight/PointLightV3.h"
    "Objects/PointLightV2.cpp"
    "Objects/PointLightV2.h"
    "Objects/SpotLight/SpotLight.cpp"
    "Objects/SpotLight/SpotLight.h"
    "Shaders/Light/pointLight.fsc"
    "Shaders/Light/pointLight.vsc"
    "Shaders/Light/SpotLight.fsc"
    "Shaders/Light/SpotLight.vsc"
    "ToolKit/TimerToolkit.cpp"
    "ToolKit/TimerToolkit.h"
    "Engine/Component/Component.cpp"
    "Engine/Component/Component.h"
    "Engine/zEngine.cpp"
    "Engine/zEngine.h"
    "Engine/Component/Mesh/Mesh.cpp"
    "Engine/Component/Mesh/Mesh.h"
    "Engine/Core/Level.cpp"
    "Engine/Core/Level.h"
    "Engine/Core/Shader.cpp"
    "Engine/Core/Shader.h"
    "Engine/Core/ShaderProgram.cpp"
    "Engine/Core/ShaderProgram.h"
    "Engine/Core/Camera/Camera.cpp"
    "Engine/Core/Camera/Camera.h"
    "Engine/Core/Texture2D/Texture2D.cpp"
    "Engine/Core/Texture2D/Texture2D.h"
    "Engine/Object/Object.cpp"
    "Engine/Object/Object.h"
    "Levels/LevelHeader.h"
    "Levels/BoxWithLight/DrawBoxWithLight.cpp"
    "Levels/BoxWithLight/DrawBoxWithLight.h"
    "Levels/DrawRTSJX/DrawRTSJX.cpp"
    "Levels/DrawRTSJX/DrawRTSJX.h"
    "Levels/DrawSJX/DrawSanjiaoxing.cpp"
    "Levels/DrawSJX/DrawSanjiaoxing.h"
    "Levels/DrawTexBox/DrawTexBox.cpp"
    "Levels/DrawTexBox/DrawTexBox.h"
    "Levels/TexBoxWithLight/DrawTexBoxWithLight.cpp"
    "Levels/TexBoxWithLight/DrawTexBoxWithLight.h"
    "Levels/DrawBox/DrawBox.cpp"
    "Levels/DrawBox/DrawBox.h"
    "LogPrinter/Log.cpp"
    "LogPrinter/Log.h"
    "Objects/ObjectHeader.h"
    "Objects/Box.cpp"
    "Objects/Box.h"
    "Objects/BoxWithLight.cpp"
    "Objects/BoxWithLight.h"
    "Objects/PointLight.cpp"
    "Objects/PointLight.h"
    "Objects/SanJiaoXing.cpp"
    "Objects/SanJiaoXing.h"
    "Objects/TexBox.cpp"
    "Objects/TexBox.h"
    "Objects/TexBoxWithLight.cpp"
    "Objects/TexBoxWithLight.h"
    "Objects/roteSJX.cpp"
    "Objects/roteSJX.h"
    "ToolKit/FileToolKit.cpp"
    "ToolKit/FileToolKit.h"
    "ToolKit/glad.c"
    "ToolKit/GLLib.cpp"
    "ToolKit/GLLib.h"
    "ToolKit/ImgToolKit.cpp"
    "ToolKit/ImgToolKit.h"
    "ToolKit/stb_img.cpp"
    "ToolKit/stb_img.h"
    "ToolKit/Typedef.h"
)
source_group("" FILES ${no_group_source_files})

set(ALL_FILES
    ${no_group_source_files}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})


include_directories(.)

include_directories(SYSTEM ThirdParty/lib-assimp/include)
include_directories(SYSTEM ThirdParty/glad/include)
include_directories(SYSTEM ThirdParty/lib-glfw/include)
include_directories(SYSTEM ThirdParty/)
include_directories(SYSTEM ThirdParty/glm)

set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_LIBRARY_OUTPUT_DIRECTORY ThirdParty/lib-assimp/linux)
add_subdirectory(ThirdParty/assimp)

set(GLFW_BUILD_WIN32 OFF)
set(GLFW_BUILD_COCOA OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_WAYLAND OFF)

set(GLFW_BUILD_X11 ON)

add_subdirectory(ThirdParty/glfw)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux" AND ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    message("Linux GCC")
    add_compile_definitions(PLATFORM LINUX)
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
            "assimp"
            "glfw"
    )
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows" AND ${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    message("Windows MSVC")

    add_compile_definitions(PLATFORM WINDOWS)

    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        set(ADDITIONAL_LIBRARY_DEPENDENCIES
                "$<$<CONFIG:Debug>:"
                "assimp-vc143-mtd;"
                "zlibstaticd"
                ">"
                "$<$<CONFIG:Release>:"
                "assimp-vc143-mt;"
                "zlibstatic"
                ">"
                "glfw3"
        )
    endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")
