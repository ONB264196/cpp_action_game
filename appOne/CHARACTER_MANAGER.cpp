#include"GAME.h"
#include"CONTAINER.h"
#include"CHARACTER.h"
#include"PLAYER.h"
#include"PLAYER_BULLET.h"
#include"PUMPKIN.h"
#include"BAT.h"
#include"BAT_BULLET.h"
#include"EXPLOSION.h"
#include"CHARACTER_MANAGER.h"

CHARACTER_MANAGER::CHARACTER_MANAGER(GAME* game) : GAME_OBJECT(game)
{
}

CHARACTER_MANAGER::~CHARACTER_MANAGER()
{
	for (int i = 0; i < Total; i++) {
		delete Characters[i];
	}
	delete[] Characters;
}

void CHARACTER_MANAGER::create()
{
	CharaMag = game()->container()->data().charaMng;

	Total = 0;
	Total += CharaMag.numPlayers;
	Total += CharaMag.numPlayerBullets;
	Total += CharaMag.numPumpkins;
	Total += CharaMag.numBats;
	Total += CharaMag.numBatBullets;
	Total += CharaMag.numExplosions;
	Characters = new CHARACTER * [Total];

	Player = new PLAYER(game());
	int i, j = 0;
	for (i = 0; i < CharaMag.numPlayers; i++)       Characters[j++] = Player;
	for (i = 0; i < CharaMag.numPlayerBullets; i++) Characters[j++] = new PLAYER_BULLET(game());
	for (i = 0; i < CharaMag.numPumpkins; i++)      Characters[j++] = new PUMPKIN(game());
	for (i = 0; i < CharaMag.numBats; i++)          Characters[j++] = new BAT(game());
	for (i = 0; i < CharaMag.numBatBullets; i++)    Characters[j++] = new BAT_BULLET(game());
	for (i = 0; i < CharaMag.numExplosions; i++)     Characters[j++] = new EXPLOSION(game());

	for (int i = 0; i < Total; i++) {
		Characters[i]->create();
	}
}

void CHARACTER_MANAGER::init()
{
	for (int i = 0; i < Total; i++) {
		Characters[i]->init();
	}
}

void CHARACTER_MANAGER::appear(char charaId, float wx, float wy, float vx, float vy)
{
	for (int i = 0; i < Total; i++) {
		if (Characters[i]->charaId() == charaId) {
			if (Characters[i]->hp() <= 0) {
				Characters[i]->appear(wx, wy, vx, vy);
				break;
			}
		}
	}
}

void CHARACTER_MANAGER::update()
{
	for (int i = 0; i < Total; i++) {
		if (Characters[i]->hp() > 0) {
			Characters[i]->update();
		}
	}

	for (int i = 0; i < Total - 1; i++) {
		if (Characters[i]->hp() == 0) {
			continue;
		}
		for (int j = i + 1; j < Total; j++) {
			if (Characters[j]->hp() == 0) {
				continue;
			}
			if (Characters[i]->groupId() == Characters[j]->groupId()) {
				continue;
			}
			if (Characters[i]->wLeft() < Characters[j]->wRight() &&
				Characters[j]->wLeft() < Characters[i]->wRight() &&
				Characters[i]->wTop() < Characters[j]->wBottom() &&
				Characters[j]->wTop() < Characters[i]->wBottom()) {
				//“–‚½‚Á‚½
				Characters[i]->damage();
				Characters[j]->damage();
			}
		}
	}
}

void CHARACTER_MANAGER::draw()
{
	for (int i = 0; i < Total; i++) {
		if (Characters[i]->hp() > 0) {
			Characters[i]->draw();
		}
	}
}
