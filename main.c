#include <stdio.h>
#include <stdint.h>

#include "ceres.c"

#define WIDTH 50
#define HEIGHT 50

#define IMG_SIZE (WIDTH * HEIGHT)

static Color32 pixels[IMG_SIZE];

int main(void) {
	Ceres_FillPixels(pixels, IMG_SIZE, C_WHITE);
	
	Ceres_FillRect(pixels, WIDTH, HEIGHT, 1, 1, 48, 1, C_RED);
	Ceres_FillRect(pixels, WIDTH, HEIGHT, 1, 1, 1, 48, C_RED);
	Ceres_FillRect(pixels, WIDTH, HEIGHT, 1, 48, 48, 1, C_RED);
	Ceres_FillRect(pixels, WIDTH, HEIGHT, 48, 1, 1, 48, C_RED);

	Ceres_FillFrom(pixels, WIDTH, HEIGHT, 25, 25, C_RED);

	Ceres_SavePpm(pixels, WIDTH, HEIGHT);
	return 0;
}
