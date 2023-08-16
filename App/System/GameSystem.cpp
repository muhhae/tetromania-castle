#include "GameSystem.hpp"
#include "UI/Button.hpp"

void Game::run()
{
    std::cout << "Game is starting" << std::endl;
    
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(600, 800), "Tetris", sf::Style::Close);
    init(window);
    
    g_font.loadFromFile(firaFontPath);
    
    std::cout << "Game is running" << std::endl;
        
    sf::Clock clock;
    sf::Time dt;
    sf::Time dt_fixed;
    float TimeScale = 1;
    
    int fps = 0;
    
    sf::Text scoreText;
    sf::Sprite background(getTexture(castleBackgroundPath));
    background.setPosition(g_screen.left - 500, g_screen.top);
    background.scale(2, 2);
    
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
    
    while (window.isOpen())
    {
        dt_fixed = clock.restart();
        dt = dt_fixed * TimeScale;
        if (!lose)
        {
            sf::Event event;
            
            while (window.pollEvent(event))
            {
                bool inputResult = false;
                if (TimeScale) inputResult = input(blockClusters.back(), event);
                
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::Resized)
                {
                    view.setSize(event.size.width, event.size.height);
                    window.setView(view);
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
                fps = 1 / dt.asSeconds();
                elapsedTime = 0;
                if (!moveBlockCluster(blockClusters.back(), sf::Vector2f(0, blockClusters.back().getSize())))
                {
                    betterCheckLine();
                    instantiate(randomShape(), 
                                randomPosition(), 
                                randomColor(), 
                                50);
                }
            }
            
            fpsText.setString("FPS: " + std::to_string(fps));
            scoreText.setString(std::to_string(g_score));
            
            pauseButton.update(window);
            
            window.clear(sf::Color::Black);
                window.draw(background);
                for (const auto& blockCluster : blockClusters)
                    window.draw(blockCluster);
                
                if (TimeScale == 0)
                {
                    sf::RectangleShape pauseBackground(sf::Vector2f(g_screen.width, g_screen.height));
                    pauseBackground.setFillColor(sf::Color(0, 0, 0, 128));
                    pauseBackground.setOrigin(pauseBackground.getLocalBounds().width / 2, pauseBackground.getLocalBounds().height / 2);
                    pauseBackground.setPosition(0, 0);
                    window.draw(pauseBackground);
                    
                    sf::Text pauseText = sf::Text("PAUSE", g_font, 50);
                    pauseText.setColor(sf::Color::White);
                    pauseText.setOrigin(pauseText.getLocalBounds().width / 2, pauseText.getLocalBounds().height / 2);
                    pauseText.setPosition(0, 0);
                    window.draw(pauseText);
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
            loseText.setPosition(0, -50);
            
            sf::Text scoreText;
            scoreText.setFont(g_font);
            scoreText.setColor(sf::Color::White);
            scoreText.setCharacterSize(30);
            scoreText.setString("Your score: " + std::to_string(g_score));
            scoreText.setOrigin(scoreText.getLocalBounds().width / 2, scoreText.getLocalBounds().height / 2);
            scoreText.setPosition(0, 50);
            
            Button button;
            button.setButtonPosition(sf::Vector2f(0, 200))
                  .setOrigin(sf::Vector2f(115, 40))
                  .setButtonSize(sf::Vector2f(230, 80))
                  .setButtonTexture(getTexture(buttonTexturePath))
                  
                  .setTextPosition(sf::Vector2f(0, 195))
                  .setTextString("TRY AGAIN")
                  .setTextSize(30)
                  .setTextCenter()
                  .setFont(g_font)
                  
                  .setButtonOnHover([&]()
                    {
                        button.setTextPosition(sf::Vector2f(0, 200));
                        button.setButtonTexture(getTexture(buttonOnHoverTexturePath));
                    })
                  .setButtonOnClick([&]()
                    {
                        restart();
                    })
                  .update(window);
            
            window.clear(sf::Color::Black);
                window.draw(background);
                window.draw(loseText);
                window.draw(scoreText);
                window.draw(button);
            window.display();
        }
    }
}
void Game::init(sf::RenderWindow& window)
{
    srand(time(NULL));
    
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(window.getSize()));   
    window.setView(view);
    
    g_screen.bottom = view.getSize().y / 2;
    g_screen.top = view.getSize().y / -2;
    g_screen.left = view.getSize().x / -2;
    g_screen.right = view.getSize().x / 2;
    
    g_screen.width = view.getSize().x;
    g_screen.height = view.getSize().y;
}
void Game::restart()
{
    lose = false;
    g_score = 0;
    blockClusters.clear();
    instantiate(randomShape(), 
                randomPosition(), 
                randomColor(), 
                50);
}
void Game::instantiate(BlockCluster::Shape shape, 
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
void Game::betterCheckLine()
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
    
    if (lineCount <= 0) return;
    
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
}
bool Game::input(BlockCluster& blockCluster, sf::Event event)
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
bool Game::moveBlockCluster(BlockCluster& blockCluster, sf::Vector2f offset)
{
    for (auto& block : blockCluster.getBlocks())
    {
        if (block.getPosition().x + offset.x < g_screen.left ||
            block.getPosition().x + offset.x >= g_screen.right ||
            block.getPosition().y + offset.y >= g_screen.bottom)
        {
            // std::cout << "\nPos : " << block.getPosition().x + offset.x << ", " << block.getPosition().y + offset.y << std::endl;
            // std::cout << "Out of bound" <<std::endl;
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
                    // std::cout << "\nPos : " << block.getPosition().x + offset.x << ", " << block.getPosition().y + offset.y << std::endl;
                    // std::cout << "Collide" <<std::endl;
                    return false;
                }
            }
        }
    }
    blockCluster.move(offset);
    return true;
}
bool Game::rotateBlockCluster(BlockCluster& blockCluster)
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
bool Game::moveBlock(Block & block, sf::Vector2f offset)
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
bool Game::checkLose()
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
