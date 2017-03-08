//
// Created by kongo on 27.10.16.
//
#include <fstream>

#include "GUI.h"
#include "imgui/imgui-SFML.h"
#include "imgui/imguidock.h"
#include "imgui/imguiplotvar.h"

GUI::GUI(Map& map, Simulation& simulation, CameraController& cameraController)
        :map(&map), simulation(&simulation), cameraController(&cameraController) {

}

void GUI::render(sf::Sprite &sprite) {
    renderMenu();
    renderScene(sprite);
}

void GUI::renderScene(sf::Sprite &sprite) {
    ImGui::SetNextWindowPos(ImVec2(menuWidth, 0));
    if (!ImGui::Begin("Scene", NULL, ImVec2(0,0), 0.3f, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoSavedSettings
                                                        | ImGuiWindowFlags_NoCollapse ))
    {
        ImGui::End();
        return;
    }

    ImGui::Image(sprite);
    if (ImGui::IsItemHovered()) {
        if(ImGui::IsMouseDown(0))
            cameraController->changePosition(ImGui::GetIO().MouseDelta);

        cameraController->applyZoom();
    }
    ImGui::End();
}


void GUI::renderMenu() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(menuWidth, 1000));
    if (!ImGui::Begin("Menu", NULL, ImVec2(0,0), 0.3f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
    {
        ImGui::End();
        return;
    }

    if (ImGui::CollapsingHeader("Map", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Text("Size");
        ImGui::SliderInt("Width", &mapWidth, 30, 120);
        ImGui::SliderInt("Height", &mapHeight, 30, 120);
        ImGui::Separator();

        ImGui::Text("Streets");
        int w = (mapWidth / 15);
        int h = (mapHeight / 15);
        ImGui::SliderInt("Horizontal", &horizontalStreets, 2, h);
        ImGui::SliderInt("Vertical", &verticalStreets, 2, w);
        if(horizontalStreets > h)
            horizontalStreets = h;
        else if(horizontalStreets < 2)
            horizontalStreets = 2;
        if(verticalStreets > w)
            verticalStreets = w;
        else if(verticalStreets < 2)
            verticalStreets = 2;
        if(verticalStreets > 90)
            verticalStreets = 90;

        ImGui::Separator();

        ImGui::Text("Cars");
        ImGui::SliderInt("Density", &carsDensity, 1, 50, "%.0f%%");
        if (ImGui::Button("Submit")) {
            map->init(mapWidth, mapHeight, horizontalStreets, verticalStreets);
            simulation->init(carsDensity);
        }
    }
    if (ImGui::CollapsingHeader("Simulation", ImGuiTreeNodeFlags_DefaultOpen )) {
        ImGui::SliderFloat("Delay", &simulation->delay, 0.001f, 1.0f, "%.3f s");
        if (ImGui::Button("Gather Data"))
            ImGui::OpenPopup("Gather Data");
        renderGatherData();
    }
    ImGui::End();
}

void GUI::resize(sf::Event::SizeEvent sizeEvent) {

}

void GUI::renderGatherData() {
    if (ImGui::BeginPopupModal("Gather Data", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Warning! This operation can take a while (up to a few houres).");
        ImGui::Text("Result file will be placed in data/result.csv");

        if (ImGui::Button("Accept")) {
            gatherData();
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();
        if (ImGui::Button("Close")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void GUI::gatherData() {
    int mapWidth = 50;
    int mapHeight = 50;
    int horizontalStreets = 2;
    int verticalStreets = 2;
    int numberOfIterations = 10000;
    int vMax = 5;
    float propability0 = 0.3f;
    float propability1 = 0.5f;
    int maxMapIncrease = 5;
//    int maxCarsDensity = 20;
    int maxCarsDensity = 90;
    int abandonedIterations = 100;
//    int numberOfTests = 4;
    int numberOfTests = 10;
    static int progress = 0;
    static float max = maxMapIncrease * maxCarsDensity * numberOfTests;

    std::string filename = "result";
    //filename += i +'0';
    filename += ".csv";
    std::ofstream myfile (filename.c_str());
    myfile << "width,height,horizontalStreets,verticalStreets,density,stream\n";

    for (int i = 1; i <= maxMapIncrease; ++i) {
        for (int carsDensity = 1; carsDensity <= maxCarsDensity; ++carsDensity) {
            myfile << mapWidth * i << "," << mapHeight * i << "," << horizontalStreets * i << "," <<
            verticalStreets * i << "," <<  carsDensity;

            float totalFlow = 0;
            for (int k = 0; k < numberOfTests; ++k) {
                Map map(mapWidth * i, mapHeight * i, 32, horizontalStreets * i, verticalStreets * i);
                Simulation simulation(map, vMax, propability0, propability1, carsDensity);

                float flow = 0;
                for (int j = 0; j < numberOfIterations; ++j) {
                    simulation.update();
                    if(j >= abandonedIterations) {
//                        sum += simulation.averageSpeed;
                        //myfile << simulation.averageSpeed << ",";
                        flow += simulation.totalSpeed / map.numberOfStreetTiles;
                    }
                }
                //sum /= (numberOfIterations - abandonedIterations);
                totalFlow += flow / (numberOfIterations - abandonedIterations);

                progress++;
                printf("Progress %d%%\n", (int) ((progress * 100) / max));
            }
            totalFlow /= numberOfTests;
            myfile << "," << totalFlow << "\n";
        }
        myfile << "\n";
    }
    myfile.close();
}





























