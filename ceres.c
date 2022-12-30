#ifndef INCLUDE_CERES
#define INCLUDE_CERES

#include <stdint.h>
#include <stdio.h>

#ifndef CERES_COLORS
#define CERES_COLORS
#define C_WHITE 	0xFFFFFFFF
#define C_BLACK 	0xFF000000
#define C_BLUE  	0xFFFF0000
#define C_GREEN 	0xFF00FF00
#define C_RED   	0xFF0000FF
#define C_GRAY  	0xFF181818
#define C_YELLOW	0xFF00BBFF
#endif

#define CERES_TRUE 1
#define CERES_FALSE 0

#ifndef CERES_OUTPUT_FILE
#define CERES_OUTPUT_FILE "output.ppm"
#endif

#define MAX(a, b) (a < b ? b : a)
#define MIN(a, b) (a < b ? a : b)
#define SQR(a) ((a) * (a))
#define SQRT_DIST(x1, y1, x2, y2) (SQR(x1 - x2) + SQR(y1 - y2))

typedef uint32_t Color32;

void Ceres_FillPixels(Color32* pixels, size_t size, Color32 color) {
	for (size_t i = 0; i < size; ++i) {
		pixels[i] = color;
	}
}

void Ceres_FillRect(Color32* pixels,
		int img_w, int img_h,
		int x, int y,
		int w, int h,
		Color32 color) {
	int x0 = MIN(MAX(0, x), img_w);
	int x1 = MIN(MAX(0, x + w), img_w);
	int y0 = MIN(MAX(0, y), img_h);
	int y1 = MIN(MAX(0, y + h), img_h);

	for (int i = x0; i < x1; ++i) {
		for (int j = y0; j < y1; ++j) {
			pixels[j * img_w + i] = color;
		}
	}
}

void Ceres_FillCircle(Color32* pixels,
		int width, int height,
		int x, int y,
		int radius,
		Color32 color) {
	int x0 = MIN(MAX(0, x - radius), width);
	int y0 = MIN(MAX(0, y - radius), height);
	int x1 = MIN(MAX(0, x + radius), width);
	int y1 = MIN(MAX(0, y + radius), height);

	for (int i = x0; i < x1; ++i) {
		for (int j = y0; j < y1; ++j) {
			if (SQRT_DIST(i, j, x, y) <= radius * radius)
				pixels[j * width + i] = color;
		}
	}
}

int Ceres_SavePpm(Color32* pixels, int width, int height) {
	FILE* fp = fopen(CERES_OUTPUT_FILE, "wb");
	if (fp == NULL) return 1;

	fprintf(fp, "P6\n%d %d 255\n", width, height);

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Color32 pixel = pixels[y * width + x];
			uint8_t bytes[3] = {
				pixel & 0x0000FF,
				(pixel & 0x00FF00) >> 8,
				(pixel & 0xFF0000) >> 16,
			};

			fwrite(bytes, sizeof(bytes), 1, fp);
		}
	}
	fclose(fp);
	return 0;
}

void Ceres_PrintCanvas(Color32* pixels, int width, int height) {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			printf("%x ", pixels[y * width + x]);
		}
		printf("\n");
	}
}

#endif
