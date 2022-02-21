#include"window.h"
#include"ANIM.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
#include "PLAYER_BULLET.h"

void PLAYER_BULLET::create()
{
	Chara = game()->container()->data().playerBulletChara;
}

void PLAYER_BULLET::appear(float wx, float wy, float vx, float vy)
{
	Chara.hp = game()->container()->data().playerBulletChara.hp;
	Chara.wx = wx;
	Chara.wy = wy;
	Chara.vx = vx;
	Chara.vy = rand() % 4 - (float) 12;
}

void PLAYER_BULLET::update()
{
	float gravity = 49.0f;
	Chara.wx += Chara.vx * (Chara.speed * delta);
	Chara.vy += gravity * delta;
	Chara.wy += Chara.vy * 60 * delta;

	if (game()->map()->collisionCharaRect(wLeft(), wTop(), wRight(), wBottom()) ||
		Chara.wx < game()->map()->wDispLeft() ||
		Chara.wx > game()->map()->wDispRight()) {
		Chara.hp = 0;
	}
}
