#include "GameplayScene.hpp"
#include "UI/Button.hpp"

#include <SFML/Audio.hpp>

void GameplayScene::run(sf::RenderWindow& window)
{
    sf::Clock clock;
    sf::Time dt;
    sf::Time dt_fixed;
    float TimeScale = 1;
    
    int fps = 0;
    
    sf::Text scoreText;
    sf::Sprite background(getTexture(g_backgroundPath + "bg.png"));
    background.setOrigin(background.getLocalBounds().width / 2, background.getLocalBounds().height / 2);
    background.setPosition(0, -100);
    background.scale(3, 3);
    
    sf::RectangleShape bg_overlay;
    bg_overlay.setSize(sf::Vector2f(g_screen.width, g_screen.height));
    bg_overlay.setFillColor(sf::Color(0, 0, 0, 64));
    bg_overlay.setOrigin(bg_overlay.getLocalBounds().width / 2, bg_overlay.getLocalBounds().height / 2);
    bg_overlay.setPosition(0, 0);
    
    scoreText.setFont(g_font);
    scoreText.setColor(sf::Color::White);
    scoreText.setPosition(g_screen.left + 10, g_screen.top + 10);
    scoreText.setCharacterSize(50);
    
    sf::Text fpsText;
    fpsText.setFont(g_font);
    fpsText.setColor(sf::Color::White);
    fpsText.setPosition(g_screen.left + 10, g_screen.top + 60);
    fpsText.setCharacterSize(20);
    
    restart();
    
    Button pauseButton;
    pauseButton.setButtonTexture(getTexture(pauseButtonTexturePath))
                .setButtonPosition(sf::Vector2f(g_screen.right - 50, g_screen.top + 50))
                .setButtonSize(sf::Vector2f(75, 75))
                .setTextString("")
                .setOrigin(sf::Vector2f(37, 37))
                .setButtonOnUpdate([&]()
                {
                    pauseButton.setButtonColor(sf::Color(255, 255, 255, 255));
                })
                .setButtonOnHover([&]()
                {
                    pauseButton.setButtonColor(sf::Color(128, 128, 128, 255));
                })
                .setButtonOnClick([&]()
                {
                    if (TimeScale == 1)
                        TimeScale = 0;
                    else
                        TimeScale = 1;
                });
                
    Button restartButton;
    restartButton.setButtonPosition(sf::Vector2f(0, 100))
            .setOrigin(sf::Vector2f(115, 40))
            .setButtonSize(sf::Vector2f(230, 80))
            .setButtonTexture(getTexture(buttonTexturePath))
            
            .setTextPosition(sf::Vector2f(0, 95))
            .setTextString("TRY AGAIN")
            .setTextSize(30)
            .setTextCenter()
            .setFont(g_font)
            
            .setButtonOnHover([&]()
            {
                restartButton.setTextPosition(sf::Vector2f(0, 100));
                restartButton.setButtonTexture(getTexture(buttonOnHoverTexturePath));
            })
            .setButtonOnClick([&]()
            {
                restart();
            })
            .setButtonOnUpdate([&]()
            {
                restartButton.setButtonTexture(getTexture(buttonTexturePath))
                             .setTextPosition(sf::Vector2f(0, 95));
            });
    Button menuButton;
    menuButton.setButtonPosition(sf::Vector2f(0, 200))
            .setOrigin(sf::Vector2f(115, 40))
            .setButtonSize(sf::Vector2f(230, 80))
            .setButtonTexture(getTexture(buttonTexturePath))
            
            .setTextPosition(sf::Vector2f(0, 195))
            .setTextString("MAIN MENU")
            .setTextSize(30)
            .setTextCenter()
            .setFont(g_font)
            
            .setButtonOnHover([&]()
            {
                menuButton.setTextPosition(sf::Vector2f(0, 200));
                menuButton.setButtonTexture(getTexture(buttonOnHoverTexturePath));
            })
            .setButtonOnUpdate([&]()
            {
                menuButton.setButtonTexture(getTexture(buttonTexturePath))
                          .setTextPosition(sf::Vector2f(0, 195));
            })
            .setButtonOnClick([&]()
            {
                g_currentScene = enumScene::menu;
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
            
    sf::RectangleShape pauseBackground(sf::Vector2f(g_screen.width, g_screen.height));
    pauseBackground.setFillColor(sf::Color(0, 0, 0, 128));
    pauseBackground.setOrigin(pauseBackground.getLocalBounds().width / 2, pauseBackground.getLocalBounds().height / 2);
    pauseBackground.setPosition(0, 0);
    
    std::array<float, 4> lightRadius = {30, 30, 60, 70};
    std::array<sf::Vector2f, 4> lightPositions = 
        { 
            sf::Vector2f(-125, -48), 
            sf::Vector2f(70, -48), 
            sf::Vector2f(-78, 123), 
            sf::Vector2f(163, 125) 
        };
    std::array<sf::CircleShape, 4> lights;
    
    for (int i = 0; i < lights.size(); ++i)
    {
        lights[i].setRadius(lightRadius[i]);
        lights[i].setOrigin(lights[i].getLocalBounds().width / 2, lights[i].getLocalBounds().height / 2);
        lights[i].setFillColor(sf::Color(255, 210, 28, 20));
        lights[i].setPosition(lightPositions[i]);
    }
    
    sf::SoundBuffer candleBuffer;
    candleBuffer.loadFromFile(g_candlePath);
    sf::Sound candleSound;
    candleSound.setBuffer(candleBuffer);
    candleSound.setLoop(true);
    candleSound.setVolume(20);
    candleSound.play();
    
    sf::SoundBuffer crumblingBuffer;
    sf::Sound crumblingSound;
    sf::SoundBuffer fallingBuffer;
    sf::Sound fallingSound;
    
    crumblingBuffer.loadFromFile(g_crumblingPath);
    crumblingSound.setBuffer(crumblingBuffer);
    
    fallingBuffer.loadFromFile(g_fallingPath);
    fallingSound.setBuffer(fallingBuffer);
    fallingSound.setPlayingOffset(sf::seconds(1));
    
    while (window.isOpen())
    {
        if (g_currentScene != enumScene::gameplay) break;
        dt_fixed = clock.restart();
        dt = dt_fixed * TimeScale;
        
        const static float maxTimeSpeed = 2;
        static float timeSpeed = 1; 
        
        static float elapsedTime = 0;
        elapsedTime += dt.asSeconds() * timeSpeed;
        
        static float elapsedTime_fixed = 0;
        elapsedTime_fixed += dt_fixed.asSeconds();   
        
        if (!lose)
        {
            sf::Event event;
            
            while (window.pollEvent(event))
            {
                bool inputResult = false;
                if (TimeScale) inputResult = input(blockClusters.back(), event);
                
                if (inputResult && event.key.code == sf::Keyboard::Down) elapsedTime = 0;
                
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::Resized)
                {
                    view.setSize(event.size.width, event.size.height);
                    window.setView(view);
                }
                if (event.type == sf::Event::LostFocus)
                {
                    TimeScale = 0;
                }
                if (event.type == sf::Event::KeyReleased)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        if (TimeScale == 1)
                            TimeScale = 0;
                        else
                            TimeScale = 1;
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                        sf::Vector2f mousePosition_world = window.mapPixelToCoords(mousePosition);
                        std::cout << mousePosition_world.x << ", " << mousePosition_world.y << std::endl;
                    }
                }
            }
            
            static bool soundPlayed = false;
            if (!moveBlockCluster(blockClusters.back(), sf::Vector2f(0, blockClusters.back().getSize())))
            {
                if (!soundPlayed)
                    fallingSound.play();
                soundPlayed = true;
            }
            else
            {
                moveBlockCluster(blockClusters.back(), sf::Vector2f(0, -blockClusters.back().getSize()));
                soundPlayed = false;
            }
            
            if (elapsedTime >= 1)
            {
                elapsedTime = 0;
                if (!moveBlockCluster(blockClusters.back(), sf::Vector2f(0, blockClusters.back().getSize())))
                {
                    if (timeSpeed < maxTimeSpeed) timeSpeed += 0.1;
                    if (betterCheckLine()) crumblingSound.play();
                    instantiate(randomShape(), 
                                randomPosition(), 
                                randomColor(), 
                                50);
                    for (int i = 0; i < rand() % 4; i++) rotateBlockCluster(blockClusters.back());
                }
            }
            
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
            if (elapsedTime_fixed >= 0.4)
            {   
                elapsedTime_fixed = 0;
                fps = 1 / dt_fixed.asSeconds();
            }
            
            fpsText.setString("FPS: " + std::to_string(fps));
            scoreText.setString(std::to_string(g_score));
            
            pauseButton.update(window);

            
            window.clear(g_screenColor);
                window.draw(background);
                window.draw(bg_overlay);
                for (const auto& light : lights)
                    window.draw(light);
                for (const auto& blockCluster : blockClusters)
                    window.draw(blockCluster);
                
                if (TimeScale == 0)
                {
                    window.draw(pauseBackground);
                    
                    sf::Text pauseText = sf::Text("PAUSE", g_font, 80);
                    pauseText.setColor(sf::Color::White);
                    pauseText.setOrigin(pauseText.getLocalBounds().width / 2, pauseText.getLocalBounds().height / 2);
                    pauseText.setPosition(0, -100);
                    window.draw(pauseText);
                    
                    quitButton.update(window);
                    restartButton.update(window);
                    menuButton.update(window);
                    window.draw(menuButton);
                    window.draw(quitButton);
                    window.draw(restartButton);
                }
                window.draw(pauseButton);
                window.draw(fpsText);
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
            }
            sf::Text loseText;
            loseText.setFont(g_font);
            loseText.setColor(sf::Color::White);
            loseText.setCharacterSize(50);
            loseText.setString("GAME OVER");
            loseText.setOrigin(loseText.getLocalBounds().width / 2, loseText.getLocalBounds().height / 2);
            loseText.setPosition(0, -150);
            
            sf::Text scoreText;
            scoreText.setFont(g_font);
            scoreText.setColor(sf::Color::White);
            scoreText.setCharacterSize(30);
            scoreText.setString("Your score: " + std::to_string(g_score));
            scoreText.setOrigin(scoreText.getLocalBounds().width / 2, scoreText.getLocalBounds().height / 2);
            scoreText.setPosition(0, -50);
            
            restartButton.update(window);
            menuButton.update(window);
            quitButton.update(window);
            
            window.clear(g_screenColor);
                window.draw(background);
                window.draw(pauseBackground);
                window.draw(loseText);
                window.draw(scoreText);
                window.draw(quitButton);
                window.draw(menuButton);
                window.draw(restartButton);
            window.display();
        }
    }
}

void GameplayScene::init(sf::RenderWindow& window)
{
    srand(time(NULL));
    
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(window.getSize()));   
    window.setView(view);
}
void GameplayScene::restart()
{
    lose = false;
    g_score = 0;
    blockClusters.clear();
    instantiate(randomShape(), 
                randomPosition(), 
                randomColor(), 
                50);
}
void GameplayScene::instantiate(BlockCluster::Shape shape, 
                       sf::Vector2f position,
                       sf::Color color, 
                       float size)
{
    blockClusters.push_back(BlockCluster());
    blockClusters.back().setPosition(position)
                        .setColor(color)
                        .setSize(size)
                        .setShape(shape);
    blockClusters.back().create();   
}
bool GameplayScene::betterCheckLine()
{   
    bool trueResult = false;
    while (1)
    {
        const int maxLine = 12;
        
        struct lineInfo
        {
            lineInfo(float y, int count) : y(y), count(count) {}
            float y;
            int count = 0;
        };
        
        std::vector<lineInfo> lines;
        
        for (auto& bc : blockClusters)
        {
            auto& blocks = bc.getBlocks();
            for (auto& block : blocks)
            {
                auto iter = std::find_if(lines.begin(), lines.end(), 
                                                                [&](lineInfo& line) 
                                                                {
                                                                    return line.y == block.getPosition().y;
                                                                });
                if (iter != lines.end())
                {
                    iter->count++;
                }
                else
                {
                    lines.push_back(lineInfo(block.getPosition().y, 1));
                } 
            }
        }
        
        int lineCount = 0;
        
        for (auto& line : lines)
        {
            if (line.count >= maxLine)
            {
                lineCount++;
                g_score += 1000;
                for (auto & blockCluster : blockClusters)
                {
                    auto & blocks = blockCluster.getBlocks();
                    
                    deleteAll<Block>(blocks, [&](Block& block){return block.getPosition().y == line.y;});
                }  
            }
        }
        
        if (lineCount <= 0) break;
        
        deleteAll<BlockCluster>(blockClusters, [&](BlockCluster& blockCluster){return blockCluster.getBlocks().empty();});
        std::multimap<float, Block&> OrderedBlockMap;
        
        for (auto& blockCluster : blockClusters)
        {
            for (auto& block : blockCluster.getBlocks())
            {
                OrderedBlockMap.insert(std::pair<float, Block&>(block.getPosition().y, block));
            }
        }
        
        for (auto it = OrderedBlockMap.rbegin(); it != OrderedBlockMap.rend(); ++it)
        {
            for (int i = 0; i < lineCount; i++)
            {
                moveBlock(it->second, sf::Vector2f(0, it->second.getSize().y));
            }
        }
        
        trueResult = true;
    }
    
    return trueResult;
}
bool GameplayScene::input(BlockCluster& blockCluster, sf::Event event)
{
    sf::Vector2f move;
    float offset = blockCluster.getSize();
    
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Left)
            move.x -= offset;
        if (event.key.code == sf::Keyboard::Right)
            move.x += offset;
        if (event.key.code == sf::Keyboard::Up)
            rotateBlockCluster(blockCluster);
        if (event.key.code == sf::Keyboard::Down)
            move.y += offset;
    } else return false;
    return moveBlockCluster(blockCluster, move);
}
bool GameplayScene::moveBlockCluster(BlockCluster& blockCluster, sf::Vector2f offset)
{
    for (auto& block : blockCluster.getBlocks())
    {
        if (block.getPosition().x + offset.x < g_screen.left ||
            block.getPosition().x + offset.x >= g_screen.right ||
            block.getPosition().y + offset.y >= g_screen.bottom)
        {
            return false;
        }
    }
    
    for (auto& bc : blockClusters)
    {
        if (&blockCluster == &bc) continue;
        
        for (auto& block : blockCluster.getBlocks())
        {
            for (auto& b : bc.getBlocks())
            {   
                if (block.getPosition() + offset == b.getPosition())
                {
                    return false;
                }
            }
        }
    }
    blockCluster.move(offset);
    return true;
}
bool GameplayScene::rotateBlockCluster(BlockCluster& blockCluster)
{
    BlockCluster temp = blockCluster;
    temp.rotate();
    
    for (auto& block : temp.getBlocks())
    {
        if (!block.getActive()) continue;
        
        if (block.getPosition().x < g_screen.left ||
            block.getPosition().x >= g_screen.right ||
            block.getPosition().y >= g_screen.bottom)
        {
            // std::cout << "Out of bound" <<std::endl;
            // std::cout << "failRotate" <<std::endl;
            return false;
        }
    }
    
    for (auto& bc : blockClusters)
    {
        if (&blockCluster == &bc) continue;
        
        for (auto& block : temp.getBlocks())
        {
            if (!block.getActive()) continue;
            
            for (auto& b : bc.getBlocks())
            {   
                if (!b.getActive()) continue;
                if (block.getPosition() == b.getPosition())
                {
                    // std::cout << "Pos : " << block.getPosition().x << ", " << block.getPosition().y << std::endl;
                    // std::cout << "Collide\n" <<std::endl;
                    return false;
                }
            }
        }
    }
    blockCluster.rotate();
}
bool GameplayScene::moveBlock(Block & block, sf::Vector2f offset)
{
    if (block.getPosition().x + offset.x < g_screen.left ||
        block.getPosition().x + offset.x >= g_screen.right ||
        block.getPosition().y + offset.y >= g_screen.bottom)
    {
        // std::cout << "\nPos : " << block.getPosition().x + offset.x << ", " << block.getPosition().y + offset.y << std::endl;
        // std::cout << "Out of bound" <<std::endl;
        return false;
    }
    
    for (auto & blockCluster : blockClusters)
    {
        for (auto & b : blockCluster.getBlocks())
        {
            if (block.getPosition() + offset == b.getPosition())
            {
                // std::cout << "\nPos : " << block.getPosition().x + offset.x << ", " << block.getPosition().y + offset.y << std::endl;
                // std::cout << "Collide" <<std::endl;
                return false;
            }
        }
    }
    
    block.move(offset);
    return true;
}
bool GameplayScene::checkLose()
{
    for (auto& blockCluster : blockClusters)
    {
        if (&blockCluster == &blockClusters.back()) break;
        for (auto& block : blockCluster.getBlocks())
        {
            if (block.getPosition().y <= g_screen.top)
            {
                // std::cout << "Lose" << std::endl;
                return true;
            }
        }
    }
    return false;
}
