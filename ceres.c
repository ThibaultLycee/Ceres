#ifndef INCLUDE_CERES
#define INCLUDE_CERES

#include <stdint.h>
#include <stdio.h>

#include "ceres_math.c"

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
	int x0 = CERES_MIN(CERES_MAX(0, x), img_w);
	int x1 = CERES_MIN(CERES_MAX(0, x + w), img_w);
	int y0 = CERES_MIN(CERES_MAX(0, y), img_h);
	int y1 = CERES_MIN(CERES_MAX(0, y + h), img_h);

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
	int x0 = CERES_MIN(CERES_MAX(0, x - radius), width);
	int y0 = CERES_MIN(CERES_MAX(0, y - radius), height);
	int x1 = CERES_MIN(CERES_MAX(0, x + radius), width);
	int y1 = CERES_MIN(CERES_MAX(0, y + radius), height);

	for (int i = x0; i < x1; ++i) {
		for (int j = y0; j < y1; ++j) {
			if (CERES_SQRT_DIST(i, j, x, y) <= radius * radius)
				pixels[j * width + i] = color;
		}
	}
}

void Ceres_FillFrom(Color32* pixels,
		int width, int height,
		int x, int y, Color32 color) {
	if (pixels[y * width + x] == color) return;
	
	typedef struct {
		int x;
		int y;
	} Coord;
	Coord neighbours[] = {
		{x, y-1},
		{x, y+1},
		{x-1, y},
		{x+1, y},
	};

	if (x >= 0 && x < width
			&& y >= 0 && y < width) {
		pixels[y * width + x] = color;
		for (size_t i = 0; i < 4; ++i) {
			Coord here = neighbours[i];
			Ceres_FillFrom(pixels, width, height, here.x, here.y, color);
		}
	}
}

void Ceres_Line(Color32* pixels,
		int width, int height,
		int x1, int y1,
		int x2, int y2,
		Color32 color) {
	int dx = x2 - x1;
	int dy = y2 - y1;

	if (dx == 0 && dy == 0) return;

	if (CERES_ABS(dx) > CERES_ABS(dy)) {
		float slope = (float) CERES_ABS(dy) / CERES_ABS(dx);
		for (int i = 0; i <= dx; ++i) {
			int x = x1 + i;
			int y = slope * i + x1;
			if (x >= 0 && y >= 0 && x < width && y < height)
				pixels[y * width + x] = color;
		}
	} else {
		float slope = CERES_ABS(dx) / CERES_ABS(dy);
		for (int i = 0; i <= dy; ++i) {
			int y = y1 + i;
			int x = x1 + i * slope;
			if (x >= 0 && y >= 0 && x < width && y < height)
				pixels[y * width + x] = color;
		}
	}

}


void Ceres_Bezier2(Color32* pixels,
		int width, int height,
		int x1, int y1,
		int x2, int y2,
		int x3, int y3,
		Color32 color) {
	for (size_t t = 0; t < 100000; ++t) {
		int px1 = __CeresMath_Lerp(x1, x2, (float) t / 100000);
		int px2 = __CeresMath_Lerp(x2, x3, (float) t / 100000);
		int py1 = __CeresMath_Lerp(y1, y2, (float) t / 100000);
		int py2 = __CeresMath_Lerp(y2, y3, (float) t / 100000);
		
		int x = __CeresMath_Lerp(px1, px2, (float) t / 100000);
		int y = __CeresMath_Lerp(py1, py2, (float) t / 100000);

		if (x >= 0 && x < width && y >= 0 && y < height)
			pixels[y * width + x] = color;
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
