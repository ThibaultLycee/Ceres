#include <stdio.h>
#include <stdint.h>

#include "ceres.c"

#define WIDTH 50
#define HEIGHT 50

#define IMG_SIZE (WIDTH * HEIGHT)

static Color32 pixels[IMG_SIZE];

int main(void) {
	Ceres_FillPixels(pixels, IMG_SIZE, C_WHITE);

	Ceres_Line(pixels, WIDTH, HEIGHT, 1, 1, 48, 48, C_BLACK);
	Ceres_Line(pixels, WIDTH, HEIGHT, 1, 1, 1, 48, C_RED);
	Ceres_Line(pixels, WIDTH, HEIGHT, -2, -3, 21, 7, C_BLUE);
	Ceres_Line(pixels, WIDTH, HEIGHT, 1, 1, 21, 7, C_GREEN);

	Ceres_SavePpm(pixels, WIDTH, HEIGHT);
	return 0;
}
