// This is the extended version of the game CLiTBot. We will bring about much more features to the project.
// We will do this later in this term.

#include "struct.h"
#include "raylib-cpp.hpp"
#include "const.h"

int main_ex(){
    // This is the entrance of the extended version of the game CLiTBot, and it will be called in main.cpp.

    raylib::Window window(cst::SCREEN_WIDTH, cst::SCREEN_HEIGHT, "GLiTBot!");

    SetTargetFPS(cst::TARGET_FPS);

    while (!window.ShouldClose())
    {
        BeginDrawing();

        window.ClearBackground(RAYWHITE);

        DrawText("This is the window for testing.", 190, 200, 20, LIGHTGRAY);

        // Object methods.
        EndDrawing();
    }

    // UnloadTexture() and CloseWindow() are called automatically.
    return 0;
}
