#include <iostream>
#include <SFML/Graphics.hpp>

#include "Object/block.hpp"
#include "System/GameSystem.hpp"

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(600, 800), "SFML works!", sf::Style::Close);
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(window.getSize()));
    window.setView(view);
    
    g_screen.bottom = view.getSize().y / 2;
    g_screen.top = view.getSize().y / -2;
    g_screen.left = view.getSize().x / -2;
    g_screen.right = view.getSize().x / 2;
    
    g_screen.width = view.getSize().x;
    g_screen.height = view.getSize().y;
        
    sf::Clock clock;
    sf::Time dt;
    
    sf::Text scoreText;
    sf::Font firaFont;
    
    firaFont.loadFromFile("firaFont.ttf");
    
    scoreText.setFont(firaFont);
    scoreText.setColor(sf::Color::White);
    scoreText.setPosition(g_screen.left + 10, g_screen.top + 10);
    scoreText.setCharacterSize(30);
    
    instantiate(randomShape(), 
                randomPosition(), 
                randomColor(), 
                50);
    
    bool lose = false;
    
    while (window.isOpen())
    {
        dt = clock.restart();
        if (!lose)
        {
            sf::Event event;
            
            while (window.pollEvent(event))
            {
                input(blockClusters.back(), event);
                
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::Resized)
                {
                    view.setSize(event.size.width, event.size.height);
                    window.setView(view);
                }
                if (event.type == sf::Event::KeyReleased)
                {
                    if (event.key.code == sf::Keyboard::X)
                    {
                        instantiate(randomShape(), 
                                    randomPosition(), 
                                    sf::Color::Red, 
                                    50);
                    }
                }
            }
            
            static float elapsedTime = 0;
            elapsedTime += dt.asSeconds();
            
            if (elapsedTime >= 1)
            {
                elapsedTime = 0;
                if (!moveBlockCluster(blockClusters.back(), sf::Vector2f(0, blockClusters.back().getSize())))
                {
                    checkLine();
                    instantiate(randomShape(), 
                                randomPosition(), 
                                randomColor(), 
                                50);
                }
            }
            
            scoreText.setString(std::to_string(g_score));
            
            window.clear(sf::Color::Black);
                for (const auto& blockCluster : blockClusters)
                    window.draw(blockCluster);
                window.draw(scoreText);
            window.display();
            lose = checkLose();
        }
        else
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Space)
                    {
                        lose = false;
                        g_score = 0;
                        blockClusters.clear();
                        instantiate(randomShape(), 
                                    randomPosition(), 
                                    sf::Color::Red, 
                                    50);
                    }
                }
            }
            sf::Text loseText;
            loseText.setFont(firaFont);
            loseText.setColor(sf::Color::White);
            loseText.setCharacterSize(50);
            loseText.setString("YOU LOSE");
            loseText.setOrigin(loseText.getLocalBounds().width / 2, loseText.getLocalBounds().height / 2);
            loseText.setPosition(0, -50);
            
            sf::Text scoreText;
            scoreText.setFont(firaFont);
            scoreText.setColor(sf::Color::White);
            scoreText.setCharacterSize(30);
            scoreText.setString("Your score: " + std::to_string(g_score));
            scoreText.setOrigin(scoreText.getLocalBounds().width / 2, scoreText.getLocalBounds().height / 2);
            scoreText.setPosition(0, 50);
            
            sf::Text tryAgain;
            tryAgain.setFont(firaFont);
            tryAgain.setColor(sf::Color::White);
            tryAgain.setCharacterSize(30);
            tryAgain.setString("Press space to try again");
            tryAgain.setOrigin(tryAgain.getLocalBounds().width / 2, tryAgain.getLocalBounds().height / 2);
            tryAgain.setPosition(0, 100);
            
            window.clear(sf::Color::Black);
                window.draw(loseText);
                window.draw(scoreText);
                window.draw(tryAgain);
            window.display();
        }
    }

    return 0;
}