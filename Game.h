#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "Timer.h"
//#include "playerController.h"

class Game: public AppComponent, private Timer{
    TexRect* mushroom;
    //AnimatedRect* Player1;
	Rect* Player1;
	Rect* Player2;
	Rect* p1_attack;
	Rect* p2_attack;

	int player1_score;
	int player2_score;
    
    bool player1Visible;
	bool player2Visible;
	//bool player_fwdwalkVisible;
    bool mushroomVisible;
	bool p1_attackVisible;
	bool p2_attackVisible;

    bool up;
    bool left;

	bool p1_moveLeft;
	bool p1_moveRight;
	bool p2_moveLeft;
	bool p2_moveRight;

	bool p1_canAttack;
	bool p2_canAttack;

    bool hit;
    float theta;
    float deg;
public:
    AnimatedRect* explosion;
    Game();
    
    void draw() const ;
    void handleKeyDown(unsigned char, float, float);
	void handleKeyUp(unsigned char, float, float);
    void action();

    ~Game();

};

#endif 
