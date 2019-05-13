#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "playerController.h"

playerController::playerController() {
	// Some cross-platform compatimility stuff

	const char* playerFileName;

	// In Windows (Visual Studio only) the image files are found in the enclosing folder in relation to the project
	// In other environments the image files are in the same folder as the project

	#if defined WIN32
	playerFileName = "../ryu_idle.png";
	#else
	playerFileName = "ryu_idle.png";
	#endif

	projectile = new AnimatedRect("ryu_idle.png", 2, 5, 20, true, true, -0.25, 0.8, 0.5, 0.5);
	//projectile = new Rect(-0.05, -0.8, 0.1, 0.1);

	moveLeft = false;
	moveLeft = false;
	attack = false;

	setRate(1);
	start();
}

playerController::action() {
	if (moveLeft) {
		float xpos = projectile->getX();
		xpos -= 0.005;
		projectile->setX(xpos);
		moveLeft = false;
	}
	else if (moveRight) {
		float xpos = projectile->getX();
		xpos += 0.005;
		projectile->setX(xpos);
		moveRight = false;
	}
	else {
		float xpos = projectile->getX();
		projectile->setX(xpos);
	}
}

void playerController:draw() const {
	projectile->draw(0.1);
}

void playerController::handleKeyDown(unsigned char key, float x, float y) {
	if (key == 'a') {
		moveLeft = true;
	}
	else if (key == 's') {
		moveRight = true;
	}
}

void playerController::handleKeyUp(unsigned char key, float x, float y) {
	if (key == 'a') {
		moveLeft = false;
	}
	else if (key == 's') {
		moveRight = false;
	}
}

playerController::~playerController() {
	stop();
	delete projectile;
}