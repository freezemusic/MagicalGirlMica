/*
 * character.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <functional>
#include <string>

#include <2d/CCNode.h>
#include <cocostudio/CCArmature.h>
#include <cocostudio/CCArmatureDataManager.h>

#include "character.h"
#include "character_control.h"
#include "context.h"
#include "hittable.h"
#include "log.h"
#include "res_manager.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace std;

#define NS_TAG "mica::"
#define TAG NS_TAG "Character::"

namespace mica
{

Character::Character(const Context &context)
		: m_context(context),
		  m_stat(Status::kNull),
		  m_speed(0),
		  directToR(false)
{}

Character::Character(const Context &context, Config &&config)
		: Character(context)
{
	init(std::move(config));
}

Character::~Character()
{
	uninit();
}

bool Character::init(Config &&config)
{
	uninit();

	m_control = std::move(config.control);
	setGood(initView(config) && initControl());
	getView()->setPosition(config.pos.x, config.pos.y);
	return *this;
}

bool Character::initView(const Config &config)
{
	ArmatureDataManager::getInstance()->addArmatureFileInfo(getContext()
			.getResManager()->getCharacterArmature(config.identifier));
	Armature *view = Armature::create(config.identifier);
	if (!view)
	{
		LOG_E(TAG "Character", "Failed while Armature::create");
		return false;
	}

	setView(view);
	return true;
}

bool Character::initControl()
{
	auto control = [this](const float)
			{
				m_control->control(this);
			};
	getView()->schedule(control, 0, "control");
	return true;
}

void Character::uninit()
{
	setView(nullptr);
}

void Character::stand()
{
	if (m_stat == Status::kAttack || m_stat == Status::kTurn){
		return;
	}
	if (getView() && m_stat != Status::kStand){
		m_stat = Status::kStand;
		//physicsBody->SetLinearVelocity(b2Vec2(0, 0));
		getView()->getAnimation()->play("stand");
	}
}

void Character::move(const float x, const float)
{
	if (m_stat == Status::kAttack || !getView())
	{
		return;
	}

	//physicsBody->SetLinearVelocity(b2Vec2(x*m_speed, physicsBody->GetLinearVelocity().y));
	if (x == 0.0f)
	{
		stand();
	}
	else if ((x > 0) != directToR)
	{
		turn();
	}
	else if (m_stat != Status::kWalk)
	{
		m_stat = Status::kWalk;
		getView()->getAnimation()->play("walk");
	}
}

void Character::turn()
{
	if (m_stat == Status::kAttack){
		return;
	}
	if (getView() && m_stat != Status::kTurn){
		m_stat = Status::kTurn;
		//physicsBody->SetLinearVelocity(b2Vec2(0, 0));
		getView()->getAnimation()->play("turn");

		function<void(Armature*, MovementEventType, const string&)> armatureFun = [=](Armature* armature, MovementEventType type, const string& id)
		{
			if (type == MovementEventType::COMPLETE)
			{
				directToR = !directToR;
				getView()->setScaleX(-getView()->getScaleX());
				m_stat = Status::kNull;
				this->stand();
			}
		};
		getView()->getAnimation()->setMovementEventCallFunc(armatureFun);
	}
}

void Character::attack()
{
	if (getView() && m_stat != Status::kAttack){
		m_stat = Status::kAttack;
		//physicsBody->SetLinearVelocity(b2Vec2(0, 0));
		getView()->getAnimation()->play("attack");
		function<void(Armature*, MovementEventType, const string&)> armatureStand = [=](Armature* armature, MovementEventType type, const string& id)
		{
			if (type == MovementEventType::COMPLETE)
			{
				m_stat = Status::kNull;
				this->stand();
			}
		};
		getView()->getAnimation()->setMovementEventCallFunc(armatureStand);
	}
}

}
