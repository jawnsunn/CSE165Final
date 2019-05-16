#include "App.h"

int main(int argc, char** argv) {
	GlutApp* app = new App(argc, argv, 640, 360, "footsies");

    app->run();
}
