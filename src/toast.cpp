/*
 * toast.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <string>

#include <2d/CCActionInterval.h>
#include <2d/CCLabel.h>
#include <base/CCScheduler.h>
#include <math/CCGeometry.h>
#include <ui/UIScale9Sprite.h>

#include "res_manager.h"
#include "toast.h"

using namespace cocos2d;
using namespace std;

namespace mica
{

Toast::Toast(const string &text)
		: m_text(text),
		  m_view(nullptr)
{}

Toast::Toast(string &&text)
		: m_text(std::move(text)),
		  m_view(nullptr)
{}

Toast::~Toast()
{
	m_view->removeFromParent();
}

Node* Toast::getView()
{
	if (!m_view)
	{
		initView();
		const float half_h = m_view->getContentSize().height / 2;
		// -10 is just to play safe
		m_view->setPosition(ResManager::getDesignW() / 2, ResManager::getDesignH()
				+ half_h + 10);
		m_view->runAction(MoveBy::create(0.25f, Vec2(0, -half_h - 10 - 100)));

		m_view->setCascadeOpacityEnabled(true);
		m_view->setOpacity(0);
		m_view->runAction(FadeIn::create(0.25f));

		auto dismiss = [this](const float)
				{
					m_view->removeFromParent();
				};
		auto exit = [this, dismiss](const float)
				{
					m_view->runAction(ScaleTo::create(0.25f, 0.0f));
					m_view->runAction(FadeOut::create(0.25f));
					m_view->getScheduler()->schedule(dismiss, m_view, 0.25f, 0,
							0.0f, false, "toast_dismiss");
				};
		const float duration = 2.0f + m_text.size() * 0.1f;
		m_view->getScheduler()->schedule(exit, m_view, duration, 0, 0.0f, false,
				"toast_exit");
	}
	return m_view;
}

void Toast::initView()
{
	// Use default font on the platform
	auto *label = Label::createWithSystemFont(m_text, "", 20.0f, Size::ZERO,
			TextHAlignment::CENTER, TextVAlignment::CENTER);

	auto *bg = ui::Scale9Sprite::create(Rect(30, 30, 4, 4),
			ResManager::get().getSystem("toast"));
	Size toast_size = label->getContentSize();
	toast_size.width += 64;
	toast_size.height += 64;
	bg->setContentSize(toast_size);

	m_view = Node::create();
	m_view->addChild(bg);
	m_view->addChild(label);
	m_view->setContentSize(toast_size);
}

}
