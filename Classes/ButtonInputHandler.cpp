#include "ButtonInputHandler.h"

ButtonInputHandler* ButtonInputHandler::m_instance = NULL;

ButtonInputHandler::ButtonInputHandler(){
	buttonXCmd = nullptr;
	buttonYCmd = nullptr;
	buttonACmd = nullptr;
	buttonBCmd = nullptr;

	btn_type = BUTTON_NULL;

}

ButtonInputHandler::~ButtonInputHandler()
{
	if (buttonXCmd)
		delete buttonXCmd;
	if (buttonYCmd)
		delete buttonYCmd;
	if (buttonACmd)
		delete buttonACmd;
	if (buttonBCmd)
		delete buttonBCmd;
	if (m_instance)
		delete m_instance;
}

ActionCommand* ButtonInputHandler::handleInput()
{
	BUTTON_TYPE btn_tmp = btn_type;
	btn_type = BUTTON_NULL;
	if (btn_tmp == BUTTON_X) {
		return buttonXCmd; 
	}
	
	if (btn_tmp == BUTTON_Y) return buttonYCmd;
	if (btn_tmp == BUTTON_A) return buttonACmd;
	if (btn_tmp == BUTTON_B) return buttonBCmd;

	// Nothing pressed, so do nothing.
	return NULL;
}

bool ButtonInputHandler::setCommandToButton(ActionCommand* cmd, char c)
{
	switch (c){
	case BUTTON_TYPE::BUTTON_X:
		buttonXCmd = cmd;
		break;

	case BUTTON_TYPE::BUTTON_Y:
		buttonYCmd = cmd;
		break;

	case BUTTON_TYPE::BUTTON_A:
		buttonACmd = cmd;
		break;

	case BUTTON_TYPE::BUTTON_B:
		buttonBCmd = cmd;
		break;

	default:
		return false;
	}
	return true;
}
