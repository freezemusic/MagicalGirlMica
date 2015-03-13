#include <string>

#include <math/CCGeometry.h>

#include "Character.h"
#include "Interactable.h"
#include "Player.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace std;

namespace mica
{

Player::Player()
{
	m_id = 1;
}

Player* Player::create(const string& name)
{
	Player *player = new Player();
	if (player && player->init(name))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

bool Player::init(const string& name)
{
	m_name = name;
	float scale = 0.6;
	m_arm = Armature::create(name);
	m_arm->getAnimation()->play("stand");
	m_arm->setScale(0.8f);
	setContentSize(Size(120 * scale, 256 * scale));
	m_arm->setTag(1);
	addChild(m_arm, 1);

	this->scheduleUpdate();

	return true;
}

void Player::update(float delta)
{
	Player::updateDirection();
}

void Player::interact(Interactable *other)
{}

}
