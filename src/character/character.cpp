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
		: m_context(context)
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

void Character::move(const int, const int)
{}

void Character::attack()
{}

void Character::interact(Interactable*)
{}

}
