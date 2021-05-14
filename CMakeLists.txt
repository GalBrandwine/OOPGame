cmake_minimum_required(VERSION 3.10)
project(Game VERSION "0.0.1")

set(CMAKE_CXX_STANDARD 14)

## Some boilerplate I love to add for getting more information while compiling..
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

## Keep track of the project version
message(STATUS "${BoldCyan}Compiling: ${PROJECT_NAME} version: ${PROJECT_VERSION}${ColourReset}")

set(CMAKE_BUILD_TYPE Debug)


IF(CMAKE_BUILD_TYPE MATCHES Debug)
  add_definitions ( -DShowDebugMap )
  message(STATUS "${BoldRed}${PROJECT_NAME} is in Debug, this will reduce effeciency. Continuing.. ${ColourReset}")
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)


find_package(OpenCV REQUIRED)

include_directories(
  include
  ${OpenCV_INCLUDE_DIRS}
)

set(GAME_sources
  ${CMAKE_SOURCE_DIR}/src/CReader.cpp
  ${CMAKE_SOURCE_DIR}/src/CGameAdmin.cpp
  ${CMAKE_SOURCE_DIR}/src/Defence/CDefenceUnit.cpp
  ${CMAKE_SOURCE_DIR}/src/Offence/COffenceUnit.cpp
  ${CMAKE_SOURCE_DIR}/src/Unit/CUnitProperty.cpp
  ${CMAKE_SOURCE_DIR}/src/utils/CLocation.cpp
  ${CMAKE_SOURCE_DIR}/src/utils/CAuxiliary.cpp
  ${CMAKE_SOURCE_DIR}/src/Map/Map.cpp
)


add_library(GameAdminLib 
  ${GAME_sources}
)

target_include_directories(GameAdminLib PUBLIC
${CMAKE_SOURCE_DIR}/src
${CMAKE_SOURCE_DIR}/src/Defence
${CMAKE_SOURCE_DIR}/src/Offence
${CMAKE_SOURCE_DIR}/src/Unit
${CMAKE_SOURCE_DIR}/src/Map
)

add_executable(Game 
  src/Game.cpp
)

target_link_libraries(Game
GameAdminLib
${OpenCV_LIBS}
)