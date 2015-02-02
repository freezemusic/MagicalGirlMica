#include "Role.h"

USING_NS_CC;

Role::Role()
{
	m_type = ROLE_TYPE_NULL;

	m_id = 0;
	m_speed = 0;
	m_name = "";

	m_layer = nullptr;
	physicsBody = nullptr;

	directToR = false;
	m_controlable = false;
}

void Role::setControlable(bool b)
{
	m_controlable = true;
}

void Role::stand()
{
	if (m_stat == ROLE_INJURED || m_stat == ROLE_ATTACK || m_stat == ROLE_TURN){
		return;
	}
	if (m_arm && m_stat != ROLE_STAND){
		m_stat = ROLE_STAND;
		physicsBody->SetLinearVelocity(b2Vec2(0, 0));
		m_arm->getAnimation()->play(m_name + "stand");
		CCLOG("id=%d:stand", m_id);
	}
}

void Role::walk(float x, float y)
{
	if (m_stat == ROLE_ATTACK){
		return;
	}
	physicsBody->SetLinearVelocity(b2Vec2(x*m_speed, physicsBody->GetLinearVelocity().y));
	if (m_arm && m_stat != ROLE_WALK){
		m_stat = ROLE_WALK;
		m_arm->getAnimation()->play(m_name + "walk");
		CCLOG("id=%d:walk", m_id);
		CCLOG("walk");
	}
}

void Role::turn()
{
	if (m_stat == ROLE_ATTACK){
		return;
	}
	if (m_arm && m_stat != ROLE_TURN){
		m_stat = ROLE_TURN;
		physicsBody->SetLinearVelocity(b2Vec2(0, 0));
		m_arm->getAnimation()->play(m_name + "turn");

		std::function<void(Armature*, MovementEventType, const std::string&)> armatureFun = [=](Armature* armature, MovementEventType type, const std::string& id)
		{
			if (type == MovementEventType::COMPLETE)
			{
				directToR = !directToR;
				m_stat = ROLE_NULL;
				this->stand();
			}
		};
		m_arm->getAnimation()->setMovementEventCallFunc(armatureFun);
		CCLOG("id=%d:turn", m_id);
		CCLOG("turn");
	}
}

void Role::attack()
{
	if (m_stat == ROLE_INJURED){
		return;
	}
	if (m_arm && m_stat != ROLE_ATTACK){
		m_stat = ROLE_ATTACK;
		physicsBody->SetLinearVelocity(b2Vec2(0, 0));
		m_arm->getAnimation()->play(m_name + "attack");
		std::function<void(Armature*, MovementEventType, const std::string&)> armatureStand = [=](Armature* armature, MovementEventType type, const std::string& id)
		{
			if (type == MovementEventType::COMPLETE)
			{
				m_stat = ROLE_NULL;
				this->stand();
			}
		};
		m_arm->getAnimation()->setMovementEventCallFunc(armatureStand);

		CCLOG("id=%d:attack", m_id);
		CCLOG("attack");
	}
}

void Role::updateDirection(float delta)
{
	if (directToR)
		setScaleX(-1.0f);
	else
		setScaleX(1.0f);
}