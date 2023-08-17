#include "GameSystem.hpp"
#include "Scene/GameplayScene.hpp"
#include "UI/Button.hpp"

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
    background.setPosition(0, -200);
    background.setScale(3.5, 3.5);
    
    sf::RectangleShape bg_overlay;
    bg_overlay.setSize(sf::Vector2f(g_screen.width, g_screen.height));
    bg_overlay.setFillColor(sf::Color(0, 0, 0, 64));
    bg_overlay.setOrigin(bg_overlay.getLocalBounds().width / 2, bg_overlay.getLocalBounds().height / 2);
    bg_overlay.setPosition(0, 0);
    
    while (window.isOpen())
    {
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
            }
            window.clear(g_screenColor);
            window.draw(background);
            window.draw(bg_overlay);
            
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
