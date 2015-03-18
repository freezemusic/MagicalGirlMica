#include <functional>
#include <string>

#include <2d/CCNode.h>
#include <cocostudio/CCArmature.h>

#include "character.h"
#include "hittable.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace std;

namespace mica
{

Character::Character()
{
	m_speed = 0;

	directToR = false;
}

void Character::stand()
{
	if (m_stat == Status::kAttack || m_stat == Status::kTurn){
		return;
	}
	if (m_arm && m_stat != Status::kStand){
		m_stat = Status::kStand;
		//physicsBody->SetLinearVelocity(b2Vec2(0, 0));
		m_arm->getAnimation()->play("stand");
	}
}

void Character::walk(float x, float y)
{
	if (m_stat == Status::kAttack){
		return;
	}
	//physicsBody->SetLinearVelocity(b2Vec2(x*m_speed, physicsBody->GetLinearVelocity().y));
	if (m_arm && m_stat != Status::kWalk){
		m_stat = Status::kWalk;
		m_arm->getAnimation()->play("walk");
	}
}

void Character::turn()
{
	if (m_stat == Status::kAttack){
		return;
	}
	if (m_arm && m_stat != Status::kTurn){
		m_stat = Status::kTurn;
		//physicsBody->SetLinearVelocity(b2Vec2(0, 0));
		m_arm->getAnimation()->play("turn");

		function<void(Armature*, MovementEventType, const string&)> armatureFun = [=](Armature* armature, MovementEventType type, const string& id)
		{
			if (type == MovementEventType::COMPLETE)
			{
				directToR = !directToR;
				m_stat = Status::kNull;
				this->stand();
			}
		};
		m_arm->getAnimation()->setMovementEventCallFunc(armatureFun);
	}
}

void Character::attack()
{
	if (m_arm && m_stat != Status::kAttack){
		m_stat = Status::kAttack;
		//physicsBody->SetLinearVelocity(b2Vec2(0, 0));
		m_arm->getAnimation()->play("attack");
		function<void(Armature*, MovementEventType, const string&)> armatureStand = [=](Armature* armature, MovementEventType type, const string& id)
		{
			if (type == MovementEventType::COMPLETE)
			{
				m_stat = Status::kNull;
				this->stand();
			}
		};
		m_arm->getAnimation()->setMovementEventCallFunc(armatureStand);
	}
}

void Character::updateDirection()
{
	if (directToR)
		m_arm->setScaleX(-1.0f);
	else
		m_arm->setScaleX(1.0f);
}

}
