#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "Timer.h"
//#include "playerController.h"

class Game: public AppComponent, private Timer{
    TexRect* mushroom;
    AnimatedRect* projectile;
	AnimatedRect* player_fwdwalk;
    
    bool projectileVisible;
	bool player_fwdwalkVisible;
    bool mushroomVisible;
    bool up;
    bool left;
	bool moveLeft;
	bool moveRight;
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
