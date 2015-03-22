/*
 * ai_node.h
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#pragma once

#include <libutils/type/behavior_tree/leaf_node.h>

namespace mica
{

class Stage;

namespace character
{

class Character;

}
}

namespace mica
{
namespace character
{

class AiNode : public utils::type::behavior_tree::LeafNode
{
public:
	struct Config
	{
		/// The Character attached
		Character *character;
		const Stage *world;
	};

	explicit AiNode(const Config &config)
			: m_character(config.character),
			  m_world(*config.world)
	{}

protected:
	Character* getCharacter()
	{
		return m_character;
	}

	const Stage& getStage()
	{
		return m_world;
	}

private:
	Character *m_character;
	const Stage &m_world;
};

}
}
