#pragma once
#include <SFML/Graphics.hpp>
#include "Fleet.h"
#include "Players.h"
#include "Button.h" 

#include <fstream>

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>


enum class State {
    Menu = 0,
    SetShipPosition,
    Game,
    none,
};


enum class KeyboardInput
{
    escape=0,
    anything,
    none,
};
class GameState
{
protected:
    sf::Texture BackGround_texture;
    sf::Sprite BackGround_sprite;

    sf::Texture window_texture;
    sf::Sprite window_sprite;

    sf::Font m_font;

    KeyboardInput keyboard;
    MouseInput mouse_move;

    sf::Vector2f GotCoordsPeople;

    bool first = true;

public:
    GameState();
    void InputKeyboard(sf::Event& mevent);
    virtual void Input(sf::RenderWindow& mWindow, sf::Event& mevent) {};
    virtual State Update() { return State::none; };
    virtual void Draw(sf::RenderWindow& mWindow) {};
};



//////////////////////////////////// MENU
class Menu: public GameState //
{
private:

    sf::Texture menuName_background_texture;
    sf::Sprite menuName_background_sprite;

    sf::Texture textInput_texture;
    sf::Sprite textInput_sprite;

    Button button_start;
    Button button_name;

    Button button_readyName;

    bool wasClick = false;
    bool wasKey = false;

    bool ChangeName = false;
    bool start;

    Player* people;
    std::string name;

    sf::Text Input_name;
    sf::Text text;

public:

    Menu(Player* player);

    void Input(sf::RenderWindow& mWindow, sf::Event& mevent);
    State Update();
    void Draw(sf:: RenderWindow& mWindow);
};

//////////////////////////////////// STARTGAME
class StartGame : public GameState  //
{
private:
    Player* people;
    Computer* computer;

    Num_Ship now_move;

    Button button_back;
    Button button_start;
    Button button_random;
    Button button_clear;

    bool wasClick=false;
    bool ReadyPeople = false;


public:
    StartGame(Player* player, Computer* computer);
    void Input(sf::RenderWindow& mWindow, sf::Event& mevent);
    State Update();
    void Draw(sf::RenderWindow& mWindow);
};

//////////////////////////////////// PLAYGAME
class PlayGame : public GameState //
{
private:

    Player* people;
    Computer* computer;

    sf::Font mFont;

    sf::Text people_name;
    sf::Text computer_name;

    sf::Texture arrow_texture;
    sf::Sprite arrow_sprite;

    sf::Texture GameOver_texture;
    sf::Sprite GameOver_Sprite;

    sf::Texture Winner_texture;
    sf::Sprite Winner_sprite;

    sf::Texture Loser_texture;
    sf::Sprite Loser_Sprite;

    sf::Text text;
    sf::Text text2;

    enum class Who 
    {
        player1=0,
        player2=1
    };
    Who now_move;
    //State m_state;

    sf::Vector2i GotCoordsComp;

    bool ChooseOne = true;
    Button button_people;
    Button button_computer;
    Button button_random;

    Button button_yes;
    Button button_no;

    bool game = true;
    bool BackMenu = false;
    bool win = false;
    bool show_gameover=false;
    bool ShowEnd=false;

    //bool moveDone=false;

    bool wasClick = false;
    bool wasClick_mouse = false;;

    void ChangeMove();


public:
    PlayGame(Player* player, Computer* computer);
    void Input(sf::RenderWindow& mWindow, sf::Event& mevent);//Получаем координаты
    State Update();//Передаем в класс для обновления
    void Draw(sf::RenderWindow& mWindow);
};





