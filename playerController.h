#ifndef playerController_hpp
#define playerController_hpp 

#include "AppComponent.h"
#include "AnimatedRect.h"

class playerContoller: public AppComponent{
	bool player1Visible;

	bool moveLeft;
	bool moveRight;
	bool attack;

public:
	AnimatedRect* projectile;

	playerController();

	void draw() const;
	void handleKeyDown(unsigned char, float, float);
	void handleKeyUp(unsigned char, float, float);
	void action();

	~playerController();
};

#endif