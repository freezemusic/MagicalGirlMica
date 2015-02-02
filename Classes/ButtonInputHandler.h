#ifndef __BTNINPUT_HANDLER_H__
#define __BTNINPUT_HANDLER_H__

#include "ActionCommand.h"

class ButtonInputHandler
{
public: 
	enum BUTTON_TYPE{
		BUTTON_NULL,
		BUTTON_JUMP,
		BUTTON_ATTACK,
		BUTTON_SKILL1,
		BUTTON_SKILL2,
	};

	static ButtonInputHandler* getInstance()
	{
		if (!m_instance)
			m_instance = new ButtonInputHandler();
		return m_instance;
	}

	~ButtonInputHandler();
	ActionCommand* handleInput();
	bool setCommandToButton(ActionCommand* cmd, char c);

private:
	ButtonInputHandler();

	static ButtonInputHandler* m_instance;

public:
	BUTTON_TYPE btn_type;

private:
	ActionCommand* buttonXCmd;
	ActionCommand* buttonYCmd;
	ActionCommand* buttonACmd;
	ActionCommand* buttonBCmd;
};

#endif // __BTNINPUT_HANDLER_H__ 