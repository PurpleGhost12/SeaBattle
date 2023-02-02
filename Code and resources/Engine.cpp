#include "Engine.h"

/// <summary>
/// Constructor
/// 1. Load textures
/// 2. Fill in const and variables
/// 3. Create a window
/// </summary>
Engine::Engine():comp(sf::Vector2f(77, 113), false),player("name", sf::Vector2f(825, 113), true)
{
    
    num_state = 0;
    RegisterGameState();

    /////////////////////////     Creating a window    //////////////////////
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    icon.loadFromFile("resources/images/logo.png");
    m_Window.create(sf::VideoMode(1440, 1080), "");
    m_Window.setIcon(455,533,icon.getPixelsPtr());

    WindowFocus = true;

}
void Engine::RegisterGameState()
{
    m_gameState[0] = new Menu(&player);
    m_gameState[1] = new StartGame(&player, &comp);
    m_gameState[2] = new PlayGame(&player, &comp);
}

void Engine::ChangeGameState()
{
    switch (nowState)
    {
    case State::Menu:
        num_state = 0;
        break;
    case State::SetShipPosition:
        num_state = 1;
        break;
    case State::Game:
        num_state = 2;
        break;
    case State::none:
        break;
    default:
        break;
    }
}

void Engine::start()
{
    // Time calculation
    Clock clock;   


    view.reset(sf::FloatRect(0.f+View_X0, 0.f, 1440, 1080));
    //view.setSize(sf::Vector2f(1440.f, 1080.f));
    m_Window.setView(view);
        m_Window.setFramerateLimit(60);

        m_Window.setKeyRepeatEnabled(false);
        State gamestate;
        bool game=false;
    while (m_Window.isOpen())
    {
        // Restart the timer and record the measured time in dt
        Time dt = clock.restart();

        float dtAsSeconds = dt.asSeconds();

        sf::Event event;
        //view.setCenter(720, 540);

        //view.setCenter(sf::Vector2f(720.f, 540.f));

        //float XSize = 400;
        //float YSize = 300;
 

        while (m_Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_Window.close();

            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);

                float NewX = event.size.width;
                float NewY = event.size.height;
                float z;
                float z2;
                float z3;
                if ((3.f / 4.f) > (NewY / NewX))
                {
                    z = NewY / MainArea_Hight;
                    z2 = z * MainArea_Width;
                    z3 = (NewX - z2) * (MainArea_Hight / NewY);

                    view.reset(sf::FloatRect(View_X0 - (z3 / 2), 0.f, (MainArea_Width + z3), MainArea_Hight));
                    m_Window.setView(view);
                }
                else
                {
                    z = NewX / MainArea_Width;
                    z2 = z * MainArea_Hight;
                    z3 = (NewY - z2) * (MainArea_Width / NewX);
                    view.reset(sf::FloatRect(View_X0 + 0.f, (-z3 / 2), MainArea_Width, MainArea_Hight + z3));
                    m_Window.setView(view);
                }

            }
        }
        if (WindowFocus) 
        {
            m_gameState[num_state]->Input(m_Window, event);
            nowState = m_gameState[num_state]->Update();
        }
        m_Window.clear(sf::Color(255, 255, 255));
        m_gameState[num_state]->Draw(m_Window);

        m_Window.display();

        if (nowState != State::none) ChangeGameState();


    }
}
