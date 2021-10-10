#pragma once
#include "GAME_OBJECT.h"
class MAP :
    public GAME_OBJECT
{
public:
    struct DATA {
        const char* fileName = 0;
        int blockImg = 0;
        int goalImg = 0;
        int chipSize = 0;
        char* data = 0;
        int cols = 0;
        int rows = 0;
        int dispCols = 0;
        int dispRows;
        float wx = 0;
        float wy = 0;
        float worldWidth = 0;
        float worldHeight = 0;
        float worldEndX = 0;
        float WorldEndY = 0;
        float centerX = 0;
    };
    enum CHARA_ID {
        PLAYER_ID = 'a',
        PLAYER_BULLET_ID = 'b',
        PUMPKIN_ID = 'c',
        BAT_ID = 'd',
        BAT_BULLET_ID = 'e',
        EXPLOSION_ID = 'f'
    };
private:
    DATA Map;
public:
    MAP(class GAME* game);
    ~MAP();
    void create();
    void init();
    void update();
    void draw();
    float wx() { return Map.wx; }
    float wy() { return Map.wy; }
    int chipSize() { return Map.chipSize; }

    bool collisionCheck(float wx, float wy);
    bool collisionCharaLeft(float wx, float wy);
    bool collisionCharaRight(float wx, float wy);
    bool collisionCharaTop(float wx, float wy);
    bool collisionCharaBottom(float wx, float wy);
    bool collisionCharaRect(float wLeft, float wTop, float wRight, float wBottom);
    float wDispLeft();
    float wDispRight();
};

