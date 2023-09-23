#define SFML_DEFINE_DISCRETE_GPU_PREFERENCE

#include "System/GameSystem.hpp"
#include <filesystem>


int main(const int argc, const char** argv)
{
    #ifdef NDEBUG
        std::string exedir = argv[0];
        std::string exepath = exedir.substr(0, exedir.find_last_of("\\/"));
        std::filesystem::current_path(exepath);
    #endif //NDEBUG
    
    try
    {
        Game game;
        game.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}