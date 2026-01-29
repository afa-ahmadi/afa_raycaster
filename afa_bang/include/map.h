#ifndef MAP_H
#define MAP_H

#define MAP_WIDTH 15
#define MAP_HEIGHT 15

extern int worldMap[MAP_WIDTH][MAP_HEIGHT];

void InitMap(void);
void DrawMap2D(void);
void EditMap(void);
void SaveMap(void);
void LoadMap(void);

#endif