/**************************************************
 * @date    2024-06-06
 * @brief   Shohih (CXX Chess library)
 **************************************************/

#include "game.h"
#include "raylib.h"

using namespace Shohih;

int main()
{
    Game game;
    game.Play();

    // Raylib
    InitWindow(800, 450, "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
}