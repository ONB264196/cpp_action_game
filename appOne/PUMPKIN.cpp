#include"window.h"
#include"ANIM.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
#include"PUMPKIN.h"

void PUMPKIN::create()
{
	Chara = game()->container()->data().pumpkinChara;
	Pumpkin = game()->container()->data().pumpkin;
}

void PUMPKIN::appear(float wx, float wy, float vx, float vy)
{
	Chara.hp = game()->container()->data().pumpkinChara.hp;
	Chara.wx = wx;
	Chara.wy = wy;
	Chara.vx = Pumpkin.initVecX;
	Chara.vy = Pumpkin.initVecY;
	Chara.animId = Pumpkin.leftAnimId;
	Pumpkin.damageTime = 0;
	Pumpkin.fallFlag = 0;
}

void PUMPKIN::update()
{
	Move();
	CollisionWithMap();
	ChangeColor();
}

void PUMPKIN::Move()
{
	//落下
	if (Pumpkin.fallFlag) {
		Chara.vy += Pumpkin.gravity * delta;
		Chara.wy += Chara.vy * 60 * delta;
	}
	//現在の位置の保存
	Pumpkin.curWx = Chara.wx;
	//左右移動
	Chara.wx += Chara.vx * (Chara.speed * delta);
}

void PUMPKIN::CollisionWithMap()
{
	MAP* map = game()->map();
	//壁(マップチップ)で反転
	if (Pumpkin.fallFlag == 0) {
		if (map->collisionCharaLeft(Chara.wx, Chara.wy) ||
			map->collisionCharaRight(Chara.wx, Chara.wy)) {
			Chara.animId = 1 - Chara.animId;
			Chara.vx = -Chara.vx;
			Chara.wx = Pumpkin.curWx;
		}
	}
	//接地チェック
	if (map->collisionCharaBottom(Pumpkin.curWx, Chara.wy)) {
		Pumpkin.fallFlag = 0;
		Chara.vy = 0;
		Chara.wy = (int)Chara.wy / map->chipSize() * (float)map->chipSize();
	}
	else {
		//落とす
		Pumpkin.fallFlag = 1;
	}
	//画面外
	if (Chara.wx < map->wDispLeft()) {
		Chara.hp = 0;
	}
}

void PUMPKIN::ChangeColor()
{
	if (Pumpkin.damageTime > 0) {
		Pumpkin.damageTime -= delta;
		Chara.color = Pumpkin.damageColor;
	}
	else {
		Chara.color = Pumpkin.normalColor;
	}
}

void PUMPKIN::damage()
{
	if (Chara.hp > 0) {
		Pumpkin.damageTime = Pumpkin.damageInterval;
		Chara.hp--;
		if (Chara.hp == 0) {
			game()->characterManager()->appear(Pumpkin.explosionCharaId,
				Chara.wx, Chara.wy);
		}
	}
}
