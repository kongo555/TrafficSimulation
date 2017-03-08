//
// Created by kongo on 27.10.16.
//

#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include "Renderer.h"
#include "imgui/imgui-SFML.h"


Renderer::Renderer(sf::RenderWindow& window, Simulation& simulation, Map& map, GUI& gui, CameraController& cameraController)
        :window(&window), simulation(&simulation), map(&map), gui(&gui), cameraController(&cameraController){

    if (!renderTexture.create(window.getSize().x - gui.menuWidth- 15, window.getSize().y - 40))
    {
        std::cout << "error renderTexture\n";
        // error...
    }
    sprite =  sf::Sprite(renderTexture.getTexture());
    cameraController.view = renderTexture.getView();
}

void Renderer::render(sf::Time elapsed) {
    renderTexture.clear();
    //cameraController->view.zoom(cameraController->zoom);
    renderTexture.setView(cameraController->view);

    map->render(renderTexture);
    simulation->render(renderTexture);

    renderTexture.display();

    ImGui::SFML::Update(elapsed);
    window->clear();
    gui->render(sprite);
    ImGui::Render();

    window->display();
}

void Renderer::resize(sf::Event::SizeEvent sizeEvent) {
    gui->resize(sizeEvent);
//    if (!renderTexture.create(sizeEvent.width - gui->menuWidth, sizeEvent.height))
//    {
//        std::cout << "error renderTexture\n";
//         error...
//    }
}





