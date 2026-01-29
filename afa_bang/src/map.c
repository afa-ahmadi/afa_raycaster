#include "../include/map.h"
#include "../include/player.h"
#include "../include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int worldMap[MAP_WIDTH][MAP_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void InitMap(void) { }

void DrawMap2D(void) {
    int TILE_SIZE = 40;
    int mapPixelW = MAP_WIDTH * TILE_SIZE;
    int mapPixelH = MAP_HEIGHT * TILE_SIZE;
    int offX = (GetScreenWidth() - mapPixelW) / 2;
    int offY = (GetScreenHeight() - mapPixelH) / 2;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            Color c = (worldMap[y][x] == 0) ? LIGHTGRAY : BLUE;
            DrawRectangle(offX + x * TILE_SIZE, offY + y * TILE_SIZE, TILE_SIZE, TILE_SIZE, c);
            DrawRectangleLines(offX + x * TILE_SIZE, offY + y * TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKGRAY);
        }
    }
}

void EditMap(void) {
    // متغییر مپ
    int TILE_SIZE = 40;
    int mapPixelW = MAP_WIDTH * TILE_SIZE;
    int mapPixelH = MAP_HEIGHT * TILE_SIZE;
    int offX = (GetScreenWidth() - mapPixelW) / 2;
    int offY = (GetScreenHeight() - mapPixelH) / 2;

    // موس
    Vector2 mousePos = GetMousePosition();
    int mapX = (int)((mousePos.x - offX) / TILE_SIZE);
    int mapY = (int)((mousePos.y - offY) / TILE_SIZE);

    // چک
    if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT) {
        
        int playerMapX = (int)player.pos.x;
        int playerMapY = (int)player.pos.y;

        // چک کردن موقغیت و نساختن دیوار
        if (mapX == playerMapX && mapY == playerMapY) {
            return; 
        }

        // منطق کلیک
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            worldMap[mapY][mapX] = 1;       
        } 
        else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            worldMap[mapY][mapX] = 0;
        } 
    }
}





// سیو
void SaveMap(void) {
    FILE *file = fopen("assets/maps/custom_map.txt", "w");
    if (file != NULL) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                fprintf(file, "%d ", worldMap[y][x]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }
}
// لود 
void LoadMap(void) {
    FILE *file = fopen("assets/maps/custom_map.txt", "r");
    if (file != NULL) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                fscanf(file, "%d", &worldMap[y][x]);
            }
        }
        fclose(file);
    }
}