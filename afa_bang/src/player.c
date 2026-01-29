#include "../include/player.h"
#include "../include/map.h"
#include "../include/raylib.h"
#include <math.h>




Player player;

void InitPlayer(void) {
    player.pos = (Vector2){ 12.0f, 12.0f }; 
    player.dir = (Vector2){ -1.0f, 0.0f };  
    player.plane = (Vector2){ 0.0f, 0.66f }; 
    player.moveSpeed = 3.0f; 
    player.rotSpeed = 2.0f;  
}




void UpdatePlayer(void) {
    //
    float frameTime = GetFrameTime();
    float moveStep = player.moveSpeed * frameTime;
    float rotStep = player.rotSpeed * frameTime;



    // ذکمه 
    if (IsKeyDown(KEY_LEFT)) {
        float oldDirX = player.dir.x;
        player.dir.x = player.dir.x * cosf(rotStep) - player.dir.y * sinf(rotStep);
        player.dir.y = oldDirX * sinf(rotStep) + player.dir.y * cosf(rotStep);
        
        float oldPlaneX = player.plane.x;
        player.plane.x = player.plane.x * cosf(rotStep) - player.plane.y * sinf(rotStep);
        player.plane.y = oldPlaneX * sinf(rotStep) + player.plane.y * cosf(rotStep);
    }
    if (IsKeyDown(KEY_RIGHT)) {
        float oldDirX = player.dir.x;
        player.dir.x = player.dir.x * cosf(-rotStep) - player.dir.y * sinf(-rotStep);
        player.dir.y = oldDirX * sinf(-rotStep) + player.dir.y * cosf(-rotStep);
        
        float oldPlaneX = player.plane.x;
        player.plane.x = player.plane.x * cosf(-rotStep) - player.plane.y * sinf(-rotStep);
        player.plane.y = oldPlaneX * sinf(-rotStep) + player.plane.y * cosf(-rotStep);
    }

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S)) {
        float direction = (IsKeyDown(KEY_W)) ? 1.0f : -1.0f;
        float newX = player.pos.x + player.dir.x * moveStep * direction;
        if (worldMap[(int)player.pos.y][(int)newX] == 0) {
            player.pos.x = newX;
        }
        float newY = player.pos.y + player.dir.y * moveStep * direction;
        if (worldMap[(int)newY][(int)player.pos.x] == 0) {
            player.pos.y = newY;
        }
    }

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) {
        float direction = (IsKeyDown(KEY_A)) ? 1.0f : -1.0f;
        float perpDirX = -player.dir.y;
        float perpDirY = player.dir.x;
        float newX = player.pos.x + perpDirX * moveStep * direction;
        if (worldMap[(int)player.pos.y][(int)newX] == 0) {
            player.pos.x = newX;
        }
        float newY = player.pos.y + perpDirY * moveStep * direction;
        if (worldMap[(int)newY][(int)player.pos.x] == 0) {
            player.pos.y = newY;
        }
    }
}