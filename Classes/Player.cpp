#include "Player.h"

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

void Player::response(float interval, float x, float y, JoystickEventType type)
{
	Point pos = getPosition();

	std::string str;
	m_speed = 5;

	switch (type)
	{
	case JoystickEventType::JET_TOUCH_BEGIN:
		this->stand();
		str = "Begin";
		break;
	case JoystickEventType::JET_TOUCH_MOVE:
		if (x == 0){
			this->stand();
		}
		else if (x < 0 && directToR){
			this->turn();
		}
		else if (x > 0 && !directToR){
			this->turn();
		}
		else{
			this->walk(x, y);
		}
		//str = "Move" + Misc<float>::to_string(visibleSize.width);
		str = "Move";
		//CCLOG("direct:%d isRun:%d", directToR, isRunningAction);
		break;
	case JoystickEventType::JET_TOUCH_END:
		this->stand();
		str = "End";
		break;
	}
	//label->setString(str.c_str());
}
