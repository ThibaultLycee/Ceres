#include <string.h>

#include "ceres.c"

#define TESTS_OUTPUT "./tests_out/"
#define TESTS_ERROR  "./tests_out/diff/"
#define STD_WIDTH 50
#define STD_HEIGHT 50

#define MAKE_CASE(name) \
{ \
	.test = test_##name, \
	.id = #name, \
	.ref_path = TESTS_OUTPUT #name ".ppm", \
	.err_path = TESTS_ERROR #name ".ppm", \
}

typedef struct {
	void (*test)(Color32*);
	char* id;
	char* ref_path;
	char* err_path;
} Test_Case;

void test_Ceres_FillRect(Color32* pixels) {
	Ceres_FillRect(pixels, STD_WIDTH, STD_HEIGHT, 1, 1, 48, 48, C_RED);
	Ceres_FillRect(pixels, STD_WIDTH, STD_HEIGHT, -2, 6, 9, 21, C_GREEN);
	Ceres_FillRect(pixels, STD_WIDTH, STD_HEIGHT, 3, 3, 12, 75, C_BLUE);
}

void test_Ceres_FillCircle(Color32* pixels) {
	Ceres_FillCircle(pixels, STD_WIDTH, STD_HEIGHT, 0, 0, 15, C_RED);
	Ceres_FillCircle(pixels, STD_WIDTH, STD_HEIGHT, 37, 56, 21, C_BLUE);
	Ceres_FillCircle(pixels, STD_WIDTH, STD_HEIGHT, 51, 31, 6, C_GREEN);
}

void test_Ceres_FillFrom(Color32* pixels) {
	Ceres_FillRect(pixels, STD_WIDTH, STD_HEIGHT, 1, 1, 48, 1, C_RED);
	Ceres_FillRect(pixels, STD_WIDTH, STD_HEIGHT, 1, 1, 1, 48, C_RED);
	Ceres_FillRect(pixels, STD_WIDTH, STD_HEIGHT, 1, 48, 48, 1, C_RED);
	Ceres_FillRect(pixels, STD_WIDTH, STD_HEIGHT, 48, 1, 1, 48, C_RED);

	Ceres_FillFrom(pixels, STD_WIDTH, STD_HEIGHT, 25, 25, C_RED);
}

void test_Ceres_Line(Color32* pixels) {
	Ceres_Line(pixels, STD_WIDTH, STD_HEIGHT, 1, 1, 48, 48, C_BLACK);
	Ceres_Line(pixels, STD_WIDTH, STD_HEIGHT, 1, 1, 1, 48, C_RED);
	Ceres_Line(pixels, STD_WIDTH, STD_HEIGHT, -2, -3, 21, 7, C_BLUE);
	Ceres_Line(pixels, STD_WIDTH, STD_HEIGHT, 1, 1, 21, 7, C_GREEN);
}

void test_Ceres_Bezier2(Color32* pixels) {
	Ceres_Bezier2(pixels, STD_WIDTH, STD_HEIGHT, 2, 2, 35, 36, 10, 5, C_BLACK);
}

static Test_Case tests[] = {
	MAKE_CASE(Ceres_FillRect),
	MAKE_CASE(Ceres_FillCircle),
	MAKE_CASE(Ceres_FillFrom),
	MAKE_CASE(Ceres_Line),
	MAKE_CASE(Ceres_Bezier2),
};

#define TESTS_COUNT (sizeof(tests) / sizeof(Test_Case))

int save_output(Color32* pixels, char* path) {
	FILE* fp = fopen(path, "wb");
	if (fp == NULL) return CERES_FALSE;

	fprintf(fp, "P6\n%d %d 255\n", STD_WIDTH, STD_HEIGHT);

	for (size_t y = 0; y < STD_HEIGHT; ++y) {
		for (size_t x = 0; x < STD_WIDTH; ++x) {
			Color32 pixel = pixels[y * STD_WIDTH + x];
			uint8_t bytes[3] = {
				pixel & 0x0000FF,
				(pixel & 0x00FF00) >> 8,
				(pixel & 0xFF0000) >> 16,
			};
			fwrite(bytes, sizeof(bytes), 1, fp);
		}
	}

	fclose(fp);
	return CERES_TRUE;
}

int read_ppm(Color32* pixels, char* path) {
	FILE* fp = fopen(path, "rb");
	if (fp == NULL) return CERES_FALSE;

	uint8_t P6_header[3];
	fread(P6_header, sizeof(P6_header), 1, fp);

	uint8_t curr = 0;
	while (curr != 10)
		fread(&curr, sizeof(uint8_t), 1, fp);
	
	uint8_t data[STD_WIDTH*STD_HEIGHT*3];
	fread(data, sizeof(data), 1, fp);

	for (size_t i = 0; i < STD_WIDTH*STD_HEIGHT*3; i += 3) {
		size_t idx = i / 3;
		Color32 pixel = 0xFF000000 | data[i] | (data[i+1] << 8) | (data[i+2] << 16);
		pixels[idx] = pixel;
	}

	fclose(fp);
	return CERES_TRUE;
}

int cmp_images(Color32* img_a, Color32* img_b) {
	for (size_t i = 0; i < STD_WIDTH * STD_HEIGHT; ++i) {
		if (img_a[i] != img_b[i]) return CERES_FALSE;
	}
	return CERES_TRUE;
}

void run_tests(void) {
	printf("Running the tests\n");
	for (size_t i = 0; i < TESTS_COUNT; ++i) {
		printf("\tTest n°%ld ", i+1);
		Test_Case test = tests[i];

		// Creates a blank canva
		Color32 pixels[STD_WIDTH * STD_HEIGHT];
		Ceres_FillPixels(pixels, STD_WIDTH * STD_HEIGHT, C_WHITE);

		// Runs the calculation of the output
		(*test.test)(pixels);

		// Reads the reference output
		Color32 reference[STD_WIDTH * STD_HEIGHT];
		if (!read_ppm(reference, test.ref_path)) {
			printf("FAILED (no reference)\n");
			return;
		}

		// Compares the reference to the output
		if (cmp_images(pixels, reference))
			printf("OK\n");
		// If different, creates the secondary output file
		else {
			printf("FAILED\n");
			save_output(pixels, test.err_path);
		}
	}
}

void record_tests(void) {
	printf("Recording the tests\n");
	for (size_t i = 0; i < TESTS_COUNT; ++i) {
		printf("\tTest n°%ld ", i+1);
		Test_Case test = tests[i];
		
		// Creates a blank canva
		Color32 pixels[STD_WIDTH * STD_HEIGHT];
		Ceres_FillPixels(pixels, STD_WIDTH * STD_HEIGHT, C_WHITE);
		
		// Runs the calculation of the output
		(*test.test)(pixels);
		
		// Saves the output to the correct file
		save_output(pixels, test.ref_path);
		printf("DONE\n");
	}
}

int main(int argc, char** argv) {
	if (argc == 1) {
		printf("Run ./tests <run/record>\n");
		return 0;
	}

	if (!strcmp(argv[1], "run"))
		run_tests();

	if (!strcmp(argv[1], "record"))
		record_tests();
	
	return 0;
}
