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

    //mushroom = new TexRect(shroomFileName, -0.25, 0.5, 0.5, 0.5);
    Player1 = new Rect(-0.5, -0.50, 0.1, 0.25);
	Player2 = new Rect(0.5, -0.50, 0.1, 0.25, 1.0, 0, 0);
	//Player1 = new AnimatedRect(playerFileName, 2, 5, 60, true, true, -0.05, 0, 1, 1);
    explosion = new AnimatedRect(fireballFileName, 6, 6, 20, false, false, -0.25, 0.8, 0.5, 0.5);
    
    up = false;
    left = true;

	p1_moveLeft = false;
	p1_moveRight = false;
	p2_moveLeft = false;
	p2_moveRight = false;

    player1Visible = true;
	p1_attackVisible = false;
	player2Visible = true;
	p2_attackVisible = false;
    mushroomVisible = false;

	p1_canAttack = false;
	p2_canAttack = false;
    theta = 0;
    deg = 0;
    hit = false;
    
    setRate(1);
    start();
}

void Game::action(){
	/*
    float mx = 0.5;
    float my = 0;
    
    if (theta >= 2* M_PI) theta = 0;
    if (deg >= 360) deg = 0;
    
    mx = 0.5 * cos(theta);
    my = 0.5 * sin(theta);
    */
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
    
    /*
    mushroom->setX(mx - mushroom->getW()/2);
    mushroom->setY(my + mushroom->getH()/2);
    
    theta += 0.001;
    deg += 0.1;
    */
	
	/*
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
    } */

	
	if (p1_moveLeft) {
		//projectile->setMap("../ryu_fwdwlk.png", 2, 5);
		float xpos = Player1->getX();
		xpos -= 0.005;
		Player1->setX(xpos);
		p1_moveLeft = false;
	}
	else if (p1_moveRight) {
		//projectile->setMap("../ryu_backwlk.png", 2, 5);
		//player_fwdwalkVisible = true;
		float xpos = Player1->getX();
		xpos += 0.005;
		Player1->setX(xpos);
		p1_moveRight = false;
	}

	if (p1_canAttack) {
		p1_attackVisible = true;
		float atk1pos = Player1->getX();
		p1_attack = new Rect(atk1pos, -0.5, 0.4, 0.2, 0.0, 0.5, 0.0);
		atk1pos += 0.1;
		p1_attack->setX(atk1pos);
		if (Player2->contains(atk1pos+0.5, -0.5) && player2Visible) {
				player2Visible = false;
				p1_attackVisible = false;
				delete p1_attack;
				explosion->setX(Player2->getX());
				explosion->setY(Player2->getY());
				explosion->playOnce();
		}
		p1_attackVisible = false;
	}
    
	if (p2_moveLeft) {
		float xpos2 = Player2->getX();
		xpos2 -= 0.005;
		Player2->setX(xpos2);
		p2_moveLeft = false;
	}
	else if (p2_moveRight) {
		float xpos2 = Player2->getX();
		xpos2 += 0.005;
		Player2->setX(xpos2);
		p2_moveRight = false;
	}

	if (p2_canAttack) {
		p2_attackVisible = true;
		float atk2pos = Player2->getX();
		p2_attack = new Rect(atk2pos, -0.5, 0.4, 0.2, 0.0, 0.5, 0.0);
		atk2pos -= 0.3;
		p2_attack->setX(atk2pos);
		if (Player1->contains(atk2pos, -0.5) && player1Visible) {
			player1Visible = false;
			p2_attackVisible = false;
			delete p2_attack;
			explosion->setX(Player1->getX());
			explosion->setY(Player1->getY());
			explosion->playOnce();
		}
		p2_attackVisible = false;
	}
	/*
    if (hit){
        explosion->setY(explosion->getY()-0.0001);
    } */
}

void Game::draw() const {
    
    if (player1Visible){
		//projectile->setMap("ryu_idle.png", 2, 5);
        Player1->draw();
    }
	if (player2Visible) {
		Player2->draw();
	}
    if (p1_attackVisible){
		p1_attack->draw();
    }

	if (p2_attackVisible)
		p2_attack->draw();
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
		p1_moveLeft = true;
	}
	else if (key == 's') {
		p1_moveRight = true;
	}
	
	if (key == 'd' && p1_attackVisible == false)
		p1_canAttack = true;

	if (key == 'j') {
		p2_moveLeft = true;
	}
	else if (key == 'k') {
		p2_moveRight = true;
	}

	if (key == 'l' && p2_attackVisible == false)
		p2_canAttack = true;
}

void Game::handleKeyUp(unsigned char key, float x, float y) {
	if (key == 'a') {
		p1_moveLeft = false;
	}
	else if (key == 's') {
		p1_moveRight = false;
	}

	if (key == 'd' == p1_attackVisible == true) {
		p1_canAttack = false;
	}

	if (key == 'j') {
		p2_moveLeft = false;
	}
	else if (key == 'k') {
		p2_moveRight = false;
	}

	if (key == 'l' && p2_attackVisible == true) {
		p1_canAttack = false;
	}
}

Game::~Game(){
    stop();
    delete mushroom;
    delete explosion;
    delete Player1;
	delete Player2;
	delete p1_attack;
}
