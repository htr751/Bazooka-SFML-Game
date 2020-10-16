cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
project(SimpleSfmlGame CXX)

set(INCLUDE_SRC ${CMAKE_CURRENT_LIST_DIR} "src/include")
set(INCLUDE_DIRECTORIES ${INCLUDE_SRC})

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} "src/source/")
set(SOURCES "${SOURCE_DIR}/Character.cpp" "${SOURCE_DIR}/CharacterMovement.cpp" "${SOURCE_DIR}/Enemy.cpp"
    "${SOURCE_DIR}/EventsHandling.cpp" "${SOURCE_DIR}/Game.cpp" "${SOURCE_DIR}/Hero.cpp" 
    "${SOURCE_DIR}/JumpAction.cpp" "${SOURCE_DIR}/main.cpp" "${SOURCE_DIR}/Rocket.cpp"
    "${SOURCE_DIR}/SceneUpdater.cpp" "${SOURCE_DIR}/Sprite.cpp" "${SOURCE_DIR}/TreeWorldMap.cpp")

add_executable(SimpleSfmlGame ${SOURCES} ${INCLUDE_DIRECTORIES})

include_directories(SYSTEM ${INCLUDE_DIRECTORIES})

find_package(SFML 2.5 COMPONENTS graphics audio window system  REQUIRED)
target_link_libraries(SimpleSfmlGame sfml-graphics sfml-audio sfml-window sfml-system sfml-network)

find_package(effolkronium_random REQUIRED)
target_link_libraries(SimpleSfmlGame effolkronium_random)

