#include "GameSystem.hpp"
#include "UI/Button.hpp"

void Game::run()
{
    init();
        
    sf::Clock clock;
    sf::Time dt;
    
    sf::Text scoreText;
    
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile(g_selectedBackground);
    sf::Sprite background(backgroundTexture);
    background.setPosition(g_screen.left - 500, g_screen.top);
    background.scale(2, 2);
    // background.setColor(sf::Color(128, 128, 128, 255));
    
    scoreText.setFont(g_font);
    scoreText.setColor(sf::Color::White);
    scoreText.setPosition(g_screen.left + 10, g_screen.top + 10);
    scoreText.setCharacterSize(30);
    
    // loadBlockTexture("block.png");
    
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
                    betterCheckLine();
                    instantiate(randomShape(), 
                                randomPosition(), 
                                randomColor(), 
                                50);
                }
            }
            
            scoreText.setString(std::to_string(g_score));
            
            window.clear(sf::Color::Black);
                window.draw(background);
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
                                    randomColor(), 
                                    50);
                    }
                }
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
            
            sf::Text tryAgain;
            tryAgain.setFont(g_font);
            tryAgain.setColor(sf::Color::White);
            tryAgain.setCharacterSize(30);
            tryAgain.setString("Press space to try again");
            tryAgain.setOrigin(tryAgain.getLocalBounds().width / 2, tryAgain.getLocalBounds().height / 2);
            tryAgain.setPosition(0, 100);
            
            Button button;
            button.setButtonPosition(sf::Vector2f(0, 200))
                  .setOrigin(sf::Vector2f(100, 25))
                  .setButtonSize(sf::Vector2f(200, 50))
                  .setButtonColor(sf::Color::Red)
                  .setButtonOnHover([&]()
                                    {
                                        button.setButtonColor(sf::Color::Green);
                                    });
            
            button.update(window);
            
            window.clear(sf::Color::Black);
                window.draw(background);
                window.draw(loseText);
                window.draw(scoreText);
                window.draw(tryAgain);
                window.draw(button);
            window.display();
        }
    }
}

void Game::init()
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
    
    g_font.loadFromFile(g_selectedFont);
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
    
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::Left)
            move.x -= offset;
        if (event.key.code == sf::Keyboard::Right)
            move.x += offset;
        if (event.key.code == sf::Keyboard::Up)
            rotateBlockCluster(blockCluster);
        if (event.key.code == sf::Keyboard::Down)
            move.y += offset;
    }
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
            std::cout << "\nPos : " << block.getPosition().x + offset.x << ", " << block.getPosition().y + offset.y << std::endl;
            std::cout << "Out of bound" <<std::endl;
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
                    std::cout << "\nPos : " << block.getPosition().x + offset.x << ", " << block.getPosition().y + offset.y << std::endl;
                    std::cout << "Collide" <<std::endl;
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
                    std::cout << "Pos : " << block.getPosition().x << ", " << block.getPosition().y << std::endl;
                    std::cout << "Collide\n" <<std::endl;
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
        std::cout << "\nPos : " << block.getPosition().x + offset.x << ", " << block.getPosition().y + offset.y << std::endl;
        std::cout << "Out of bound" <<std::endl;
        return false;
    }
    
    for (auto & blockCluster : blockClusters)
    {
        for (auto & b : blockCluster.getBlocks())
        {
            if (block.getPosition() + offset == b.getPosition())
            {
                std::cout << "\nPos : " << block.getPosition().x + offset.x << ", " << block.getPosition().y + offset.y << std::endl;
                std::cout << "Collide" <<std::endl;
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
                std::cout << "Lose" << std::endl;
                return true;
            }
        }
    }
    return false;
}
