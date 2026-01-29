#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct {
    Vector2 pos;
    Vector2 dir;
    Vector2 plane;
    float moveSpeed;
    float rotSpeed;
} Player;

extern Player player;

void InitPlayer(void);
void UpdatePlayer(void);

#endif