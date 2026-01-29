#include "../include/game.h"
#include "../include/player.h"
#include "../include/map.h"
#include "../include/raycast.h"
#include "../include/raylib.h"
#include <math.h>


GameState gameState = GAME_STATE_3D;

void InitGame(void) {
    InitPlayer();
    InitMap();
}

void ShootRay(int action) {
    double rayDirX = player.dir.x;
    double rayDirY = player.dir.y;

    int mapX = (int)player.pos.x;
    int mapY = (int)player.pos.y;

    double sideDistX;
    double sideDistY;

    double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
    double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

    int stepX;
    int stepY;

    int hit = 0;
    int side = 0;
    (void)side;


    // فاصله بندی
    double maxDist = 1.5; 

    if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (player.pos.x - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - player.pos.x) * deltaDistX;
    }

    if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (player.pos.y - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - player.pos.y) * deltaDistY;
    }

    // DDA برای ساخت و حذف دیوار 
    while (hit == 0) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        
        // محاسبه فاصله فعلی از بازیکن
        double currentDist = sqrt(pow(mapX - player.pos.x, 2) + pow(mapY - player.pos.y, 2));

        // دورتر حد مجاز 
        if (currentDist > maxDist) {
            hit = 1;
            
            // ساخت دیوار
            if (action == 1) {
                // چک کردن نقشه
                if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT) {
                    worldMap[mapY][mapX] = 1;
                }
            }
        }
        // برخورد با دیوار
        else if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT) {
            hit = 1; 
        } else if (worldMap[mapY][mapX] > 0) {
            hit = 1;
            
            float dist = sqrtf(powf(player.pos.x - mapX, 2) + powf(player.pos.y - mapY, 2));
            if (dist > 1.2f) {
                if (action == 0) {
                    worldMap[mapY][mapX] = 0; // خراب کردن
                } else if (action == 1) {
                    worldMap[mapY][mapX] = 1; // ساخت
                }
            }
        }
    }
}

// رسم مینیمپ
void DrawMiniMap(void) {
    int mapSize = 200;
    int tileSize = mapSize / MAP_WIDTH;
    
    // رسم دیوارهای نقشه در مینیمپ
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (worldMap[y][x] > 0) {
                DrawRectangle(10 + x * tileSize, 10 + y * tileSize, tileSize, tileSize, WHITE);
            }
        }
    }

    // موقعیت بازیکن
    int playerPixelX = 10 + (int)(player.pos.x * tileSize);
    int playerPixelY = 10 + (int)(player.pos.y * tileSize);
    DrawCircle(playerPixelX, playerPixelY, 5, RED);

    // جهت نگاه
    Vector2 lineEnd = {
        playerPixelX + player.dir.x * 10,
        playerPixelY + player.dir.y * 10
    };
    DrawLineV((Vector2){playerPixelX, playerPixelY}, lineEnd, GREEN);
}


// اصلی
void UpdateGame(void) {
    // مپ
    if (IsKeyPressed(KEY_M)) {
        if (gameState == GAME_STATE_3D) {
            gameState = GAME_STATE_2D;
        }
        else {
            gameState = GAME_STATE_3D;
        }
    }

    // سیو و لود
    if (IsKeyPressed(KEY_K)) {
        SaveMap();
    }
    if (IsKeyPressed(KEY_L)) {
        LoadMap();
    }

    // حالت سه‌بعدی
    if (gameState == GAME_STATE_3D) {
        UpdatePlayer(); // آپدیت حرکت و چرخش بازیکن
        
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            ShootRay(0);
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            ShootRay(1);
        }
    } 
    // حالت دو بعدی
    else if (gameState == GAME_STATE_2D) {
        EditMap();
    }
}

// اصلی
void DrawGame(void) {
    BeginDrawing();
    ClearBackground(RAYWHITE);



    if (gameState == GAME_STATE_3D) {
        CastRays();
        DrawMiniMap();
        
        DrawText("'M' : Map | 'K' : save | 'L' : load | 'O' : fullscreen", 10, GetScreenHeight() - 55, 20, WHITE);
        DrawText("'WASD' : Move | <- -> : Look | L-Click : Break | R-Click : create", 10, GetScreenHeight() - 30, 20, WHITE);
    } 

    else if (gameState == GAME_STATE_2D) {
        DrawMap2D();
        
        int TILE_SIZE = 40;
        int mapPixelW = MAP_WIDTH * TILE_SIZE;
        int mapPixelH = MAP_HEIGHT * TILE_SIZE;
        int offX = (GetScreenWidth() - mapPixelW) / 2;
        int offY = (GetScreenHeight() - mapPixelH) / 2;

        // محاسبه پیکسل دقیق بازیکن
        int playerPixelX = offX + (int)(player.pos.x * TILE_SIZE);
        int playerPixelY = offY + (int)(player.pos.y * TILE_SIZE);

        // رسم دایره قرمز بازیکن
        DrawCircle(playerPixelX, playerPixelY, 5, RED);
        
        // رسم خط جهت نگاه
        Vector2 center = { playerPixelX, playerPixelY };
        Vector2 lookDir = { center.x + player.dir.x * 15, center.y + player.dir.y * 15 };
        DrawLineV(center, lookDir, BLACK);
        
        DrawText("2D Map View - Left Click: Build | Right Click: Remove", 10, 10, 20, BLACK);
    }

    EndDrawing();
}


