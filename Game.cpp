#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "Game.h"

Game::Game(){

	// Some cross-platform compatimility stuff

	const char* shroomFileName;
	const char* fireballFileName;
	const char* playerFileName;
	const char* playerfwdwalkFileName;
	const char* playerbackwlkFileName;

	// In Windows (Visual Studio only) the image files are found in the enclosing folder in relation to the project
	// In other environments the image files are in the same folder as the project

	#if defined WIN32
	shroomFileName = "../mushroom.png";
	playerFileName = "../ryu_fwdwalk.png";
	fireballFileName = "../fireball.bmp";
	playerfwdwalkFileName = "../ryu_fwdwalk.png";
	playerbackwlkFileName = "../ryu_backwlk.png";
	#else
	shroomFileName = "mushroom.png";
	playerFileName = "ryu_fwdwalk.png";
	playerfwdwalkFileName = "ryu_fwdwalk.png";
	playerbackwlkFileName = "ryu_backwlk.png";
	fireballFileName = "fireball.bmp";
	#endif

    mushroom = new TexRect(shroomFileName, -0.25, 0.5, 0.5, 0.5);
    //projectile = new Rect(-0.05, -0.8, 0.1, 0.1);
	projectile = new AnimatedRect(playerFileName, 2, 5, 60, true, true, -0.05, 0, 1, 1);
    explosion = new AnimatedRect(fireballFileName, 6, 6, 20, false, false, -0.25, 0.8, 0.5, 0.5);
    
    up = false;
    left = true;
	moveLeft = false;
	moveRight = false;
    projectileVisible = true;
	player_fwdwalkVisible = false;
    mushroomVisible = true;
    theta = 0;
    deg = 0;
    hit = false;
    
    setRate(1);
    start();
}

void Game::action(){
    float mx = 0.5;
    float my = 0;
    
    if (theta >= 2* M_PI) theta = 0;
    if (deg >= 360) deg = 0;
    
    mx = 0.5 * cos(theta);
    my = 0.5 * sin(theta);
    
//    if (left)
//        mx -= 0.0005;
//    else
//        mx += 0.0005;
//
//    if (mx < -1.6f){
//        left = false;
//    }
//    if (mx > 1.6 - mushroom->getW()){
//        left = true;
//    }
    
    
    mushroom->setX(mx - mushroom->getW()/2);
    mushroom->setY(my + mushroom->getH()/2);
    
    theta += 0.001;
    deg += 0.1;
    
	
    if (!hit && up){
        float ypos = projectile->getY();
        ypos +=0.001;
        projectile->setY(ypos);

        if (mushroom->contains(0, ypos-0.005)){
            up = false;
            hit = true;
            projectileVisible = false;
            mushroomVisible = false;
            explosion->setX(mushroom->getX());
            explosion->setY(mushroom->getY());
            explosion->playOnce();
        }
    } 

	
	if (moveLeft) {
		projectile->setMap("../ryu_fwdwlk.png", 2, 5);
		float xpos = projectile->getX();
		xpos -= 0.005;
		projectile->setX(xpos);
		moveLeft = false;
	}
	else if (moveRight) {
		projectile->setMap("../ryu_backwlk.png", 2, 5);
		//player_fwdwalkVisible = true;
		float xpos = projectile->getX();
		xpos += 0.005;
		moveRight = false;
	}
	else {
		float xpos = projectile->getX();
		projectile->setX(xpos);
	} 
    
    if (hit){
        explosion->setY(explosion->getY()-0.0001);
    }
}

void Game::draw() const {
    
    if (projectileVisible){
		//projectile->setMap("ryu_idle.png", 2, 5);
        projectile->draw(0.1);
    }
    if (mushroomVisible){
        mushroom->draw(0.0);
    }
	if (player_fwdwalkVisible) {
		projectile->draw(0.1);
	}
    explosion->draw(0.1);
}

void Game::handleKeyDown(unsigned char key, float x, float y){
    if (key == ' '){
        up = true;
    }
    else if (key == 'p'){
        stop();
    }
    else if (key == 'r'){
        start();
    }

	if (key == 'a') {
		moveLeft = true;
	}
	if (key == 's') {
		moveRight = true;
	}
}

void Game::handleKeyUp(unsigned char key, float x, float y) {
	if (key == 'a') {
		moveLeft = false;
	}
	if (key == 's') {
		moveRight = false;
	}
}

Game::~Game(){
    stop();
    delete mushroom;
    delete explosion;
    delete projectile;
}
