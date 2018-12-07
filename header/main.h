#define NUM_OPTIONS 9
#define PARAM_LENGTH 100

#define OPT_HELP 0
#define OPT_OUT 1
#define OPT_THRESH 2
#define OPT_INVERT 3
#define OPT_MONO 4
#define OPT_CROP 5
#define OPT_BLUR 6
#define OPT_SALTPEPPER 7

#define CROP_DIMENSIONS 4

#define FALSE 0
#define TRUE !FALSE

void print_usage(void);
void print_dimensions(Bitmap *bitmap);
