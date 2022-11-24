# Install script for directory: /Users/huangyanxing/Desktop/程设/CLiTBot/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

set(CMAKE_BINARY_DIR "/Users/huangyanxing/Desktop/程设/CLiTBot/xcproj")

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/AudioDevice.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/AudioStream.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/BoundingBox.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Camera2D.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Camera3D.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Color.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Font.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Functions.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Gamepad.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Image.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Material.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Matrix.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Mesh.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Model.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/ModelAnimation.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Mouse.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Music.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/physac.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Ray.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/RayCollision.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/RaylibException.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/raylib-cpp-utils.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/raylib-cpp.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/raylib.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/raymath.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Rectangle.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/RenderTexture.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Shader.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Sound.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Text.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Texture.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/TextureUnmanaged.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Touch.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Vector2.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Vector3.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Vector4.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/VrStereoConfig.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Wave.hpp"
    "/Users/huangyanxing/Desktop/程设/CLiTBot/include/Window.hpp"
    )
endif()

