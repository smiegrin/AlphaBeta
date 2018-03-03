#minumum cmake version
cmake_minimum_required(VERSION 2.8)

#used to make YCM predict more readily
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#project name
project(AlphaBeta)

#make an executable: add_ececutable(name, [project files, ...])
add_executable(AlphaBeta
    Controller.cpp
    Controller.h
    KeyClicks.cpp
    KeyClicks.h
    LevelSelect.cpp
    LevelSelect.h
    MainMenu.cpp
    MainMenu.h
    Model.cpp
    Model.h
    PlayLevel.cpp
    PlayLevel.h
    SelectionGrid.cpp
    SelectionGrid.h
    Slider.cpp
    Slider.h
    UserInterface.cpp
    View.cpp
    ViewCutscene.cpp
    ViewCutscene.h
    View.h
    WorldGrid.cpp
    WorldGrid.h
)

target_link_libraries(AlphaBeta sfml-system sfml-graphics sfml-window sfml-audio)

