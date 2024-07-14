/**************************************************
 * @date    2024-06-06
 * @brief   Shohih (CXX Chess library)
 **************************************************/

#include "game.h"

int main()
{
    // Create a game object
    Shohih::Game game;

    // This function will not return unless ESC key is pressed,
    // window is closed, or program is killed with Ctrl+C.
    game.Play();
}