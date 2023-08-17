#include "GameSystem.hpp"
#include "Scene/GameplayScene.hpp"
#include "UI/Button.hpp"

#include <SFML/Audio.hpp>

void Game::run()
{   
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(600, 800), "Tetromino Castle", sf::Style::Close);
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(window.getSize()));   
    window.setView(view);
    
    initScreen(view);
    
    g_font.loadFromFile(firaFontPath);
    
    Button playButton;
    playButton.setButtonPosition(sf::Vector2f(0, 200))
            .setOrigin(sf::Vector2f(115, 40))
            .setButtonSize(sf::Vector2f(230, 80))
            .setButtonTexture(getTexture(buttonTexturePath))
            
            .setTextPosition(sf::Vector2f(0, 195))
            .setTextString("PLAY")
            .setTextSize(30)
            .setTextCenter()
            .setFont(g_font)
            
            .setButtonOnHover([&]()
            {
                playButton.setTextPosition(sf::Vector2f(0, 200));
                playButton.setButtonTexture(getTexture(buttonOnHoverTexturePath));
            })
            .setButtonOnClick([&]()
            {
                g_currentScene = enumScene::gameplay;
            })
            .setButtonOnUpdate([&]()
            {
                playButton.setButtonTexture(getTexture(buttonTexturePath))
                          .setTextPosition(sf::Vector2f(0, 195));
            });
            
    Button quitButton;
    quitButton.setButtonPosition(sf::Vector2f(0, 300))
            .setOrigin(sf::Vector2f(115, 40))
            .setButtonSize(sf::Vector2f(230, 80))
            .setButtonTexture(getTexture(buttonTexturePath))
            
            .setTextPosition(sf::Vector2f(0, 295))
            .setTextString("QUIT")
            .setTextSize(30)
            .setTextCenter()
            .setFont(g_font)
            
            .setButtonOnHover([&]()
            {
                quitButton.setTextPosition(sf::Vector2f(0, 300));
                quitButton.setButtonTexture(getTexture(buttonOnHoverTexturePath));
            })
            .setButtonOnUpdate([&]()
            {
                quitButton.setButtonTexture(getTexture(buttonTexturePath))
                          .setTextPosition(sf::Vector2f(0, 295));
            })
            .setButtonOnClick([&]()
            {
                window.close();
            });
    
    Scene * scene = new GameplayScene();
    
    sf::Sprite background(getTexture(castleBackgroundPath));
    background.setOrigin(background.getLocalBounds().width / 2, background.getLocalBounds().height / 2);
    background.setPosition(0, -170);
    background.setScale(3.5, 3.5);
    
    sf::RectangleShape bg_overlay;
    bg_overlay.setSize(sf::Vector2f(g_screen.width, g_screen.height));
    bg_overlay.setFillColor(sf::Color(0, 0, 0, 64));
    bg_overlay.setOrigin(bg_overlay.getLocalBounds().width / 2, bg_overlay.getLocalBounds().height / 2);
    bg_overlay.setPosition(0, 0);
    
    sf::Sprite title;
    title.setTexture(getTexture(g_titleTexturePath));
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
    title.setPosition(0, -250);
    title.setScale(0.4, 0.45);
    
    sf::Music bgm;
    bgm.openFromFile(g_bgmPath);
    bgm.setLoop(true);
    bgm.setVolume(5);
    bgm.play();
    
    std::array<float, 6> lightRadius = {15, 25, 40, 25, 25, 40};
    std::array<sf::Vector2f, 6> lightPositions = 
        { 
            sf::Vector2f(-202, -9),
            sf::Vector2f(-127, -28),
            sf::Vector2f(-117, -95),
            sf::Vector2f(-47, -105),
            sf::Vector2f(65, -104),
            sf::Vector2f(141, -86)
        };
    std::array<sf::CircleShape, 6> lights;
    
    for (int i = 0; i < lights.size(); ++i)
    {
        lights[i].setRadius(lightRadius[i]);
        lights[i].setOrigin(lights[i].getLocalBounds().width / 2, lights[i].getLocalBounds().height / 2);
        lights[i].setFillColor(sf::Color(255, 210, 28, 20));
        lights[i].setPosition(lightPositions[i]);
    }
    
    sf::Clock clock;
    sf::Time dt;
    
    while (window.isOpen())
    {
        dt = clock.restart();
        
        static float lightTime = 0;
        lightTime += dt.asSeconds();
        if (lightTime >= 0.1)
        {
            lightTime = 0;
            for (int i = 0; i < lights.size(); ++i)
            {
                float scale = rand() % 20 + 90;
                scale /= 100;
                lights[i].setRadius(lightRadius[i] * scale);
                lights[i].setOrigin(lights[i].getLocalBounds().width / 2, lights[i].getLocalBounds().height / 2);
            }
        }
           
        if (g_currentScene == enumScene::menu)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                        std::cout << mousePos.x << "," << mousePos.y << std::endl;
                    }
                }
            }
            window.clear(g_screenColor);
            window.draw(background);
            window.draw(bg_overlay);
            
            for(auto & light : lights)
                window.draw(light);
            
            window.draw(title);
            
            playButton.update(window);
            quitButton.update(window);
            
            window.draw(playButton);
            window.draw(quitButton);
            window.display();
        }
        else 
        {
            scene->init(window);
            scene->run(window);
        }
    }
    
    delete scene;
}
