#include <stdio.h>
#include <dirent.h>
#include "../headers/main.h"
#include <math.h>
#include<windows.h> 
#include<unistd.h>
#include <dirent.h> 



/**
 * ceilTexture - Renders the ceiling texture
 * @instance: Pointer to the SDL instance that contains the renderer
 * @ceilingTexture: SDL texture to be used for the ceiling
 * @p: Pointer to the player's position
 * @direction: Direction of the player
 * @plan: Projection plane for raycasting
 * 
 * This function renders the ceiling texture by calculating the ceiling
 * projection based on the player's position and direction, similar to 
 * how the floor projection is handled in renderCeilAndGround.
 */

void ceilTexture(SDL_Instance *instance, SDL_Texture *ceilingTexture, Player *p, Direction direction, Plan plan){
    RayDirection ray0 = {.x = direction.x - plan.x , .y= direction.y - plan.y};
    RayDirection ray1 = {.x = direction.x + plan.x , .y= direction.y + plan.y};
    int y = SCREEN_HEIGHT / 2;
    if (ceilingTexture) {
        for (; y >= 0; y--) {
            int pY = y - SCREEN_HEIGHT / 2;
            double rowDistance = (0.5 * SCREEN_HEIGHT) / pY;
            double ceilingStepX = rowDistance * (ray1.x - ray0.x) / SCREEN_WIDTH;
            double ceilingStepY = rowDistance * (ray1.y - ray0.y) / SCREEN_WIDTH;
            double ceilingX = p->x + rowDistance * ray0.x;
            double ceilingY = p->y + rowDistance * ray0.y;

            for (int x = 0; x < SCREEN_WIDTH; x++) {
                int cellX = (int)ceilingX;
                int cellY = (int)ceilingY;
                int tx = (int)(64 * (ceilingX - cellX)) & (64 - 1);
                int ty = (int)(64 * (ceilingY - cellY)) & (64 - 1);
                ceilingX += ceilingStepX;
                ceilingY += ceilingStepY;
                SDL_Rect srcRect = {tx, ty, 1, 1};
                SDL_Rect destRect = {x, y, 1, 1};
                SDL_RenderCopy(instance->renderer, ceilingTexture, &srcRect, &destRect);
            }
        }
    }
}