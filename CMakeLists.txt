cmake_minimum_required(VERSION 3.10)
project(Game VERSION "0.0.1")

set(CMAKE_CXX_STANDARD 14)

include_directories(
  include
)

set(GAME_sources
  ${CMAKE_SOURCE_DIR}/src/CReader.cpp
  ${CMAKE_SOURCE_DIR}/src/CLocation.cpp
  ${CMAKE_SOURCE_DIR}/src/CGameAdmin.cpp
  ${CMAKE_SOURCE_DIR}/src/Defence/CDefenceUnit.cpp
  ${CMAKE_SOURCE_DIR}/src/Offence/COffenceUnit.cpp
  ${CMAKE_SOURCE_DIR}/src/Unit/CUnitProperty.cpp
)


add_library(GameAdminLib 
  ${GAME_sources}
)

target_include_directories(GameAdminLib PUBLIC
${CMAKE_SOURCE_DIR}/src
${CMAKE_SOURCE_DIR}/src/Defence
${CMAKE_SOURCE_DIR}/src/Offence
${CMAKE_SOURCE_DIR}/src/Unit/
)

add_executable(Game 
  src/Game.cpp
)

target_link_libraries(Game
GameAdminLib
)