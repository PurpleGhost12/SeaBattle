#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Players.h"
#include "GameState.h"

using namespace sf;
class Engine
{
private:

    /// Окно
    RenderWindow m_Window;

    View view;

    //void input();
    //void update(float dtAsSeconds);
    //void draw();

     
    ////////////// Window and View

    ///////////// 
    //const float FoneSize_Width = 1920.f;
    //const float FoneSize_Hight = 1080.f;

    ///////////// Фон основной размер 4:3
    const float MainArea_Width = 1440.f;
    const float MainArea_Hight = 1080.f;

    const float View_X0 = 0;//(FoneSize_Width - MainArea_Width)/2;

    sf::Image icon;

    Player player;
    Computer comp;

    State nowState;
    State LastState;

    GameState* m_gameState[3];
    int num_state;

    bool WindowFocus;

    void RegisterGameState();
    void ChangeGameState();


public:

    Engine();

    void start();

};


