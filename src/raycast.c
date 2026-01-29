#include "../include/raycast.h"
#include "../include/player.h"
#include "../include/map.h"
#include "../include/raylib.h"
#include <math.h>
#include <stdlib.h>

void CastRays(void) {
    // مختصات
    int w = GetScreenWidth();
    int h = GetScreenHeight();

    // آسمان
    DrawRectangle(0, 0, w, h / 2, BLACK);

    // زمین
    DrawRectangle(0, h / 2, w, h / 2, GRAY);

    // ذیوار
    for (int x = 0; x < w; x++) {
        // موقعیت دید
        double cameraX = 2 * x / (double)w - 1; 
        double rayDirX = player.dir.x + player.plane.x * cameraX;
        double rayDirY = player.dir.y + player.plane.y * cameraX;

        // موقعیت فعلی بازیکن روی نقشه
        int mapX = (int)player.pos.x;
        int mapY = (int)player.pos.y;

        double sideDistX; // فاصله تا اولین مرز افقی
        double sideDistY; // فاصله تا اولین مرز عمودی

        // فاصله بین خطوط شبکه (1 واحد روی نقشه) در جهت پرتو
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        double perpWallDist; // فاصله عمودی تا دیوار

        int stepX; // جهت حرکت پرتو در محور X
        int stepY; // جهت حرکت پرتو در محور Y

        int hit = 0; // برخورد به دیوار
        int side;    // 0 = دیوار عمودی، 1 = دیوار افقی

        // تعیین جهت حرکت پرتو و فاصله اولیه تا اولین مرز
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

        // dda بررسی برخورد
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
            
            // بررسی برخورد با دیوار
            if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT) {
                hit = 1;
            } else if (worldMap[mapY][mapX] > 0) {
                hit = 1;
            }
        }

        // ساخت دیوار
        if (side == 0) 
            perpWallDist = (sideDistX - deltaDistX);
        else           
            perpWallDist = (sideDistY - deltaDistY);

        // محاسبه ارتفاع خط دیوار در صفحه نمایش
        int lineHeight = (int)(h / perpWallDist);

        // تعیین نقاط شروع و پایان رسم دیوار در محور Y
        int drawStart = -lineHeight / 2 + h / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + h / 2;
        if (drawEnd >= h) drawEnd = h - 1;

        // تعیین رنگ دیوار بسته به نوع دیوار و طرف برخورد
        Color wallColor;
        if (worldMap[mapY][mapX] == 1) {
            wallColor = BLUE;
            if (side == 1) wallColor = DARKBLUE; // سایه دیوارهای افقی
        } else {
            wallColor = PURPLE;
        }

        // رسم خط دیوار در ستون فعلی
        DrawRectangle(x, drawStart, 1, drawEnd - drawStart, wallColor);
    }
}
