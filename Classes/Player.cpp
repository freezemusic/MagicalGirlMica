#include "cocos2d_wrapper.h"

#include "Player.h"

namespace mica
{

Player::Player()
{
	m_id = 1;
}

Player* Player::create(const std::string& name)
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

bool Player::init(const std::string& name)
{
	m_name = name;
	float scale = 0.6;
	m_arm = Armature::create(name);
	m_arm->getAnimation()->play("stand");
	m_arm->setScale(0.8f);
	setContentSize(Size(120 * scale, 256 * scale));
	m_arm->setTag(1);
	addChild(m_arm, 1);

	this->schedule(schedule_selector(Character::updateDirection), 0);

	return true;
}

void Player::interact(Interactable *other)
{}

}
