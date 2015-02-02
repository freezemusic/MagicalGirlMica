#include "Hero.h"

USING_NS_CC;

Hero::Hero()
{
	m_id = 1;
	m_name = "mica-";
}

Hero* Hero::create(const std::string& name)
{
	Hero *hero = new Hero();
	if (hero && hero->init(name))
	{
		hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return nullptr;
}

bool Hero::init(const std::string& name)
{
	float scale = 0.6;
	m_arm = Armature::create(name);
	m_arm->getAnimation()->play(m_name + "stand");
	//m_arm->setScale(0.6f);
	setContentSize(Size(120 * scale, 256 * scale));
	m_arm->setTag(1);
	addChild(m_arm, 1);

	this->schedule(schedule_selector(Role::updateDirection), 0);

	return true;
}


void Hero::response(float interval, float x, float y, JoystickEventType type)
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