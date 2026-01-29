#include "../include/raylib.h"
#include "../include/game.h"
#include <math.h>


int main(void) {
    InitWindow(800, 600, "afa_Raycaster");
    SetTargetFPS(60);
    
    InitGame();
    

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_O)) {
            ToggleFullscreen();
        }
        UpdateGame();
        DrawGame();
    }
    
    CloseWindow();
    return 0;
}