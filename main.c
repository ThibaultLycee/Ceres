#include <stdio.h>
#include <stdint.h>

#include "ceres.c"

#define WIDTH 25
#define HEIGHT 25

#define IMG_SIZE (WIDTH * HEIGHT)

static Color32 pixels[IMG_SIZE];

int main(void) {
	Ceres_FillPixels(pixels, IMG_SIZE, C_WHITE);

	Ceres_FillCircle(pixels, WIDTH, HEIGHT, 9, 9, 13, C_GREEN);

	Ceres_SavePpm(pixels, WIDTH, HEIGHT);
	return 0;
}
