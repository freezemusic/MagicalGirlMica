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
		: m_text(text)
{}

Toast::Toast(string &&text)
		: m_text(std::move(text))
{}

Node* Toast::getView()
{
	Node *view = getView_();
	const float half_h = view->getContentSize().height / 2;
	// -10 is just to play safe
	view->setPosition(ResManager::getDesignW() / 2, ResManager::getDesignH()
			+ half_h + 10);
	view->runAction(MoveBy::create(0.25f, Vec2(0, -half_h - 10 - 100)));

	view->setCascadeOpacityEnabled(true);
	view->setOpacity(0);
	view->runAction(FadeIn::create(0.25f));

	auto dismiss = [view](const float)
			{
				view->removeFromParent();
			};
	auto exit = [view, dismiss](const float)
			{
				view->runAction(ScaleTo::create(0.25f, 0.0f));
				view->runAction(FadeOut::create(0.25f));
				view->getScheduler()->schedule(dismiss, view, 0.25f, 0, 0.0f,
						false, "toast_dismiss");
			};
	view->getScheduler()->schedule(exit, view, 2.0f + m_text.size() * 0.1f,
			0, 0.0f, false, "toast_exit");

	return view;
}

Node* Toast::getView_()
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

	auto *group = Node::create();
	group->addChild(bg);
	group->addChild(label);
	group->setContentSize(toast_size);

	return group;
}

}
