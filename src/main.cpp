/**************************************************
 * @date    2024-06-06
 * @brief   Shohih (CXX Chess library)
 **************************************************/

#include "game.h"

void PrintUsage(const std::string &);

int main(int argc, char **argv)
{
    // Game mode (offline|online)
    Shohih::GameMode gameMode;
    std::string addr;

    // Parse arguments
    std::string progName(argv[0]);
    if (argc < 3) {
        PrintUsage(progName);
        return 0;
    }
    std::string modeFlag(argv[1]);
    std::string mode(argv[2]);
    if ((modeFlag != "-m" && modeFlag != "--mode") ||
        (mode != "online" && mode != "offline")) {
        PrintUsage(progName);
        return 0;
    }
    if (mode == "online") {
        if (argc < 5) {
            PrintUsage(progName);
            return 0;
        }
        std::string hostFlag(argv[3]);
        if (hostFlag != "-u" && hostFlag != "--host") {
            PrintUsage(progName);
            return 0;
        }
        addr = argv[4];
        addr += std::string(":8080");
    }
    gameMode = (mode == "online") ? Shohih::GameMode::ONLINE : Shohih::GameMode::OFFLINE;

    // Create a game object
    Shohih::Game game(gameMode, addr);

    // This function will not return unless ESC key is pressed,
    // window is closed, or program is killed with Ctrl+C.
    game.Play();
}

void PrintUsage(const std::string &progName)
{
    std::cout << COLOR_YELLOW
        << "Usage: " << progName << " [OPTIONS]\n"
        << "Options:\n"
        << "-m, --mode\tSelect game mode (online|offline)\n"
        << "-u, --host\tSet server address in online mode\n"
        << "Example: ./shohih_main --mode offline\n"
        << "Example: ./shohih_main -m online --host 10.12.24.36\n"
        << "NOTE: Server address can be ip address or url\n"
        << "NOTE: Server is listening on port 8080\n"
        << COLOR_DEFAULT << std::endl;
}
