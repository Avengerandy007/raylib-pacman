#include "../include/UI.hpp"
#include "../include/Levels.hpp"
#include "../include/Update.hpp"
#include "../Raylib/include/raylib.h"

namespace UI{
	UIMode mode = UIMode::MENU;
	void NavigateUI(){
		if (mode == UIMode::MENU){
			switch(GetKeyPressed()){
				case KEY_S:
					LevelLogic::SelectionScreen();
					break;
				case KEY_Q:
					running = false;
					break;
			}
		}else if (IsKeyPressed(KEY_ESCAPE)){
			mode = UIMode::MENU;
		}
	}
}
