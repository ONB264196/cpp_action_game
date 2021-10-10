#include"window.h"
#include"input.h"
#include"graphic.h"
#include"ANIMS.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
#include "PLAYER.h"

void PLAYER::create()
{
	Chara = game()->container()->data().playerChara;
	Player = game()->container()->data().player;
}

void PLAYER::appear(float wx, float wy, float vx, float vy)
{
	Chara.hp = game()->container()->data().playerChara.hp;
	Chara.wx = wx;
	Chara.wy = wy;
	Chara.animId = Player.rightAnimId;
	Player.jumpFlag = 0;
	State = STATE::STRUGGLING;
}

void PLAYER::update()
{
	Launch();
	Move();
	CollisionWithMap();
	CheckState();
}

void PLAYER::Launch()
{
	if (isPress(KEY_J) || isPress(KEY_S) || isPress(KEY_DOWN)) {
		float vx = 1.0f;
		if (Chara.animId == Player.leftAnimId) vx = -1.0f;
		float wx = Chara.wx + Player.bulletOffsetX * vx;
		float wy = Chara.wy;
		game()->characterManager()->appear(Player.bulletCharaId, wx, wy, vx);
	}
}

void PLAYER::Move()
{
	//ジャンプ
	if (Player.jumpFlag == 0) {
		if (isTrigger(KEY_UP) || isTrigger(KEY_K) || isTrigger(KEY_W)){
		Chara.vy = Player.initVecUp;
		Player.jumpFlag = 1; }
	}
	if (Player.jumpFlag == 1) {
		Chara.vy += Player.gravity * delta;
		Chara.wy += Chara.vy * 60 * delta;
	}
	
	//左右移動
	Chara.vx = 0.0f;
	if (isPress(KEY_A) || isPress(KEY_LEFT)) {
		Chara.vx = -Chara.speed * delta;
		Chara.animId = Player.leftAnimId;
	}
	if (isPress(KEY_D) || isPress(KEY_RIGHT)) {
		Chara.vx = Chara.speed * delta;
		Chara.animId = Player.rightAnimId;
	}
	//移動前の位置を保存→( ※1 マップに食い込んでいたら保存してある更新前の位置に戻す)
	Player.curWx = Chara.wx;
	if (Chara.vx != 0.0f) {
		Chara.wx += Chara.vx;
	}
	else {
		Chara.animData.imgIdx = 0;
		Chara.animData.elapsedTime = -delta;
	}
}

void PLAYER::CollisionWithMap()
{
	MAP* map = game()->map();
	// ※1　キャラ右側
	if (Chara.animId == Player.rightAnimId) {
		if (map->collisionCharaRight(Chara.wx, Chara.wy)) {
			Chara.wx = Player.curWx;
		}
	}
	// ※1　キャラ左側
	else {
		if (map->collisionCharaLeft(Chara.wx, Chara.wy) || Chara.wx < map->wx()) {
			Chara.wx = Player.curWx;
		}
	}
	// ※1　キャラ上側
	if (map->collisionCharaTop(Chara.wx, Chara.wy)) {
		Chara.vy = Player.initVecDown;
	}
	// ※1　キャラ下側
	if (map->collisionCharaBottom(Player.curWx, Chara.wy)) {
		Player.jumpFlag = 0;
		Chara.vy = 0.0f;
		Chara.wy = (int)Chara.wy / map->chipSize() * (float)map->chipSize();
	}
	else {
		Player.jumpFlag = 1;
	}
}

void PLAYER::CheckState()
{
	//落下
	if (Chara.wy > height + game()->map()->chipSize()) {
		State = STATE::FALL;
		Chara.hp = 0;
		return;
	}
	//ステージクリア
	if (Chara.wx > game()->map()->wDispRight()) {
		State = STATE::SURVIVED;
		Chara.hp = 0;
	}
}

void PLAYER::damage()
{
	if (Chara.hp > 0) {
		Chara.hp--;
		if (Chara.hp == 0) {
			State = STATE::DIED;
			Chara.vy = Player.initVecUp;
		}
	}
}

bool PLAYER::died()
{
	if (State == STATE::DIED) {
		Chara.vy += Player.gravity * delta;
		Chara.wy += Chara.vy += 60 * delta;
		draw();
		return true;
	}
	else if (State == STATE::FALL) {
		return true;
	}
	return false;
}

bool PLAYER::survived()
{
	return State == STATE::SURVIVED;
}

float PLAYER::overCenterVx()
{
	float centerWx = (game()->map()->wx() + width / 2 - game()->map()->chipSize() / 2);
	float overCenterVx = Chara.wx - centerWx;
	if (overCenterVx < 0 || Chara.hp == 0) overCenterVx = 0;
	return overCenterVx;
}
