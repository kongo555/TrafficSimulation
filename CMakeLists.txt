cmake_minimum_required(VERSION 3.5)
project(Kod)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lglut -lGL")

set(EXECUTABLE_NAME "MySFML")
add_executable(${EXECUTABLE_NAME}
        imgui/imconfig.h
        imgui/imgui.cpp imgui/imgui.h
        imgui/imgui_draw.cpp
        imgui/imgui_internal.h
        imgui/stb_rect_pack.h
        imgui/stb_textedit.h
        imgui/stb_truetype.h
        imgui/imgui_demo.cpp
        imgui/imgui-SFML.cpp imgui/imgui-SFML.h
        imgui/imgui_user.inl imgui/imgui_user.h
        imgui/imguidock.cpp imgui/imguidock.h
        imgui/imguiplotvar.cpp imgui/imguiplotvar.h

        main.cpp
        Map.cpp Map.h
        Random.cpp Random.h
        Simulation.cpp Simulation.h
        Car.cpp Car.h
        GUI.cpp GUI.h
        Renderer.cpp Renderer.h CameraController.cpp CameraController.h)



# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmakeModules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
