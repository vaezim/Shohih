/**************************************************
 * @date    2024-06-06
 * @brief   Shohih (CXX Chess library)
 **************************************************/

#include "game.h"
#include "raylib.h"

using namespace Shohih;

int main()
{
    // Create a game object
    Game game;

    // This function will not return unless ESC key is pressed,
    // Window is closed, or program is killed with Ctrl+C.
    game.Play();
}