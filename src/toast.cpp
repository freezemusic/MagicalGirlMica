/*
 * toast.cpp
 *
 * Copyright (C) 2014-2015  Ming Tsang, Nathan Ng
 * Refer to LICENSE for details
 */

#include <functional>
#include <string>

#include <2d/CCActionInterval.h>
#include <2d/CCLabel.h>
#include <base/CCScheduler.h>
#include <math/CCGeometry.h>
#include <ui/UIScale9Sprite.h>

#include "context.h"
#include "notification_manager.h"
#include "res_manager.h"
#include "toast.h"

using namespace cocos2d;
using namespace std;

namespace mica
{

Toast::Toast(const Context &context, const string &text)
		: m_context(context),
		  m_text(text),
		  m_duration(0.0f)
{}

Toast::Toast(const Context &context, string &&text)
		: m_context(context),
		  m_text(std::move(text)),
		  m_duration(0.0f)
{}

Node* Toast::getView()
{
	Node *view = createView();
	const float half_h = view->getContentSize().height / 2;
	// -10 is just to play safe
	view->setPosition(ResManager::getDesignW() / 2, ResManager::getDesignH()
			+ half_h + 10);
	view->runAction(MoveBy::create(0.25f, Vec2(0,
			-view->getContentSize().height - 10 - 16)));

	view->setCascadeOpacityEnabled(true);
	view->setOpacity(0);
	view->runAction(FadeIn::create(0.25f));

	auto dismiss = [this, view](const float)
			{
				view->removeFromParent();
				invokeListeners();
				// FIXME
				m_context.getNotificationManager()->next();
			};
	auto exit = [this, view, dismiss](const float)
			{
				view->runAction(ScaleTo::create(0.25f, 0.0f));
				view->runAction(FadeOut::create(0.25f));
				view->getScheduler()->schedule(dismiss, view, 0.25f, 0, 0.0f,
						false, "toast_dismiss");
			};
	const float duration = (m_duration == 0.0f) ? 2.0f + m_text.size() * 0.1f
			: m_duration;
	view->getScheduler()->schedule(exit, view, duration, 0, 0.0f, false,
			"toast_exit");

	return view;
}

Node* Toast::createView()
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

	auto *view = Node::create();
	view->addChild(bg);
	view->addChild(label);
	view->setContentSize(toast_size);

	return view;
}

}
