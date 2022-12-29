# Ceres

[Ceres](https://en.wikipedia.org/wiki/Ceres_(mythology))

In ancient Roman religion, Ceres (/ˈsɪəriːz/ SEER-eez, Latin: [ˈkɛreːs]) was a goddess of agriculture, grain crops, fertility and motherly relationships.[3] She was originally the central deity in Rome's so-called plebeian or Aventine Triad, then was paired with her daughter Proserpina in what Romans described as "the Greek rites of Ceres". Her seven-day April festival of Cerealia included the popular Ludi Ceriales (Ceres' games). She was also honoured in the May lustratio of the fields at the Ambarvalia festival, at harvest-time, and during Roman marriages and funeral rites. She is usually depicted as a mature woman. 

Ceres is a simple graphics library I'm writting fully in C.

## Instalation

In case you already have git installed :

 - in a new folder, type `git clone https://github.com/ThibaultLycee/Ceres.git`
 - `cd` in Ceres and run `./build.sh`

If you do not use git :
 - download the projet from github
 - unzip your download
 - run `./build.sh` in the folder

## Usage

To use Ceres, just copy / paste `ceres.c` in your project folder, then include it in your main file. You can define a few macro to overwrite default values.

Exemple :
```c
// Includes Ceres in the project
#include "ceres.c"

// Creates the canva on which you will draw
static Color32 pixels[25*25];

int main(void) {
	// Fills the canva with white
	Ceres_FillPixels(pixels, 25*25, C_WHITE);
	// Draws and fill a red circle of radius 6 centered around (13, 16) -> pixels coordinate are 0-based
	Ceres_FillCircle(pixels, 25, 25, 12, 15, 6, C_RED);
	return 0;
}
```

## Preprocessor macros

Ceres defines multiple macros, in order to both simplify it's writting, but also for the user to customise the default behavior. Some other macros (math ones for instance) can be used in your project, feel free to do so, but these can't be overwritten.
To change the behavior you want, just #define a macro before including Ceres, and Ceres will avoid redefining them.

### CERES\_OUTPUT\_FILE

This macro allows you to choose the output file when using Ceres\_SavePpm. It's default value is `"output.ppm"`. If you want to redirect this output to another folder (relative or absolute), be sure to create said folder before running your program, as Ceres won't be able to do it by itself.

Example :
```c
#define CERES_OUTPUT_FILE "example.ppm"
#include "ceres.c"

int main(void) {
	// Do some stuff
	return 0;
}
```

### CERES\_COLORS

This macro allows you to overwrite defaults Ceres colors. Default colors are :
 - `C_WHITE` 	: `0xFFFFFFFF`
 - `C_BLACK` 	: `0xFF000000`
 - `C_RED`	: `0xFF0000FF`
 - `C_GREEN`	: `0xFF00FF00`
 - `C_BLUE`	: `0xFFFF0000`

These values are of the form `0xAABBGGRR`, and are calculated for litle-endian computers, so if you want to redefine them, be aware of your machine's endianess. If you are using big-endian (you're most likely not), then redefine the colors in this format : `1xRRGGBBAA`.

Example :
```c
#define CERES_COLORS
#define C_WHITE 0xFF000000 // Technically, this is black, but it's an exemple
#define C_BLACK 0xFFFFFFFF // And this is white
#define C_RED 0xFF0000FF
#define C_GREEN 0xFF00FF00
#define C_BLUE 0xFFFF0000
#define C_BG 0xFF181818 // You can add any color you want (you don't need to overwrite the CERES_COLORS macro for this)

#include "ceres.c"

int main(void) {
	// Do some stuff
	return 0;
}
```

### Other macros

Some other macros are defined to make writting Ceres easier. They are the following :
 - `MAX(a, b)`			: evaluates to `(a < b ? b : a)`
 - `MIN(a, b)` 			: evaluates to `(a < b ? a : b)`
 - `SQR(a)`			: evaluates to `((a) * (a))`
 - `SQRT_DIST(x1, y1, x2, y2)`	: evaluates to `(SQR(x1 - x2) + SQR(y1 - y2))`

### Other tags

By default, Ceres will define these tags :
 - `INCLUDE_CERES`	: makes sure to only include Ceres once when compiling

## Actual code usage

Ceres defines the following typedefs:

```c
typedef uint32_t Color32;	// A king of wrapper for the 32-bits colors
```

Ceres also defines the following functions

### ```c
void Ceres_FillPixels(Color32* pixels, size_t size, Color32 color);
```
