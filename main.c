#include <stdio.h>
#include <stdint.h>

#include "ceres.c"

#define WIDTH 50
#define HEIGHT 50

#define IMG_SIZE (WIDTH * HEIGHT)

static Color32 pixels[IMG_SIZE];

int main(void) {
	Ceres_FillPixels(pixels, IMG_SIZE, C_WHITE);

	pixels[20 * WIDTH + 5] = C_RED;
	pixels[10 * WIDTH + 15] = C_RED;
	pixels[30 * WIDTH + 45] = C_RED;
	Ceres_Bezier2(pixels, WIDTH, HEIGHT, 5, 20, 15, 10, 45, 30, C_BLACK);

	Ceres_SavePpm(pixels, WIDTH, HEIGHT);
	return 0;
}
