#include "Window.h"

int main() {
	int w = 800, h = 600;
	char* retardedTitle = "Fereastra";
	Window wind(w, h, retardedTitle);
	wind.run();
	return 0;
}


