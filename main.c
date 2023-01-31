#include <stdio.h>
#include <stdint.h>

#include "ceres.c"

#define WIDTH 500
#define HEIGHT 500

#define IMG_SIZE (WIDTH * HEIGHT)

static Color32 pixels[IMG_SIZE];

int main(void) {
	Ceres_FillPixels(pixels, IMG_SIZE, C_WHITE);

	pixels[200 * WIDTH + 50] = C_RED;
	pixels[100 * WIDTH + 150] = C_RED;
	pixels[300 * WIDTH + 450] = C_RED;
	Ceres_Bezier2(pixels, WIDTH, HEIGHT, 50, 200, 150, 100, 450, 300, C_BLACK);

	Ceres_SavePpm(pixels, WIDTH, HEIGHT);
	return 0;
}
