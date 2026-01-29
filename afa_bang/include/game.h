#ifndef GAME_H
#define GAME_H

typedef enum {
    GAME_STATE_3D,
    GAME_STATE_2D
} GameState;

extern GameState gameState;

void InitGame(void);
void UpdateGame(void);
void DrawGame(void);

#endif