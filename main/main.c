#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>

#include "bitmap.h"
#include "bitmap_write.h"

#include "threshold.h"
#include "invert.h"
#include "crop.h"
#include "monochrome.h"
#include "blur.h"
#include "saltpepper.h"

#include "main.h"


int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        print_usage();
        return EXIT_SUCCESS;
    }

    int flags[NUM_OPTIONS] = { FALSE };
    
    char *file_out = strdup("out.bmp");              // Default output file
    float threshold = 0.5;                           // Default threshold value
    int blur_radius = 1;                             // Default blur radius
    char monochrome_mode = 'G';                      // Default greyscale mode
    int crop_values[CROP_DIMENSIONS] = {0, 0, 0, 0}; // Default crop values
    int saltpepper_radius = 1;

    char op;
    while( (op = getopt(argc, argv, "ho:t:im:c:b:s:")) != -1) {
        switch(op) {
            case 'h':
                flags[OPT_HELP] = TRUE;
                break;
            case 'o':
                flags[OPT_OUT] = TRUE;
                free(file_out);
                file_out = strdup(optarg);
                break;

            case 't':
                flags[OPT_THRESH] = TRUE;
                threshold = atof(optarg);
                break;

            case 'i':
                flags[OPT_INVERT] = TRUE;
                break;

            case 'm':
                if (optarg[0] == 'G' || optarg[0] == 'r' || optarg[0] == 'g' || optarg[0] == 'b') {
                    flags[OPT_MONO] = TRUE;
                    monochrome_mode = optarg[0];
                } else {
                    printf("Invalid argument '%c' for -m. Valid values: G, r, g, b.\n", optarg[0]);
                }
                break;

            case 'c':
                flags[OPT_CROP] = TRUE;

                optind--;
                int arg_counter = 0;
                while (optind < argc && *argv[optind] != '-' && arg_counter < 4) {
                    crop_values[arg_counter] = atoi(argv[optind]);
                    optind++;
                    arg_counter++;
                }

                if (arg_counter < 4) {
                    printf("CROP ERROR.\n");
                    flags[OPT_CROP] = FALSE;
                }
                break;

            case 'b':
                flags[OPT_BLUR] = TRUE;
                blur_radius = atoi(optarg);
		break;

            case 's':
		flags[OPT_SALTPEPPER] = TRUE;
		saltpepper_radius = atoi(optarg);
		break;

        }
    }

    char *file_in = NULL;
    for (int i = optind; i < argc; i++) {
        if (!file_in) {
            file_in = strdup(argv[i]);
        } else {
            printf("Non-option argument: %s\n", argv[i]);
        }
    }


    if (!file_in) {
        printf("No input file\n");
        print_usage();
        return EXIT_SUCCESS;
    }

    Bitmap *bitmap = new_bitmap(file_in);
    read_pixels(bitmap, file_in);

    print_dimensions(bitmap);

    if(flags[OPT_HELP] == TRUE) {
        print_usage();
    }

    if(flags[OPT_CROP] == TRUE) {
        printf("Crop mode\n");
        crop_filter(bitmap, crop_values[0], crop_values[1], crop_values[2], crop_values[3]);
    }

    if(flags[OPT_THRESH] == TRUE) {
        printf("Threshold mode\n");
        threshold_filter(bitmap, threshold);

    }

    if(flags[OPT_INVERT] == TRUE) {
        printf("Invert mode\n");
        invert_filter(bitmap);
    }

    if(flags[OPT_MONO] == TRUE) {
        printf("Monochrome mode\n");
        switch (monochrome_mode) {
            case 'G':
                greyscale_filter(bitmap);
                break;
            case 'r':
                red_filter(bitmap);
                break;
            case 'g':
                green_filter(bitmap);
                break;
            case 'b':
                blue_filter(bitmap);
                break;
        }
    }

    if(flags[OPT_BLUR] == TRUE) {
        printf("Blur mode\n");
        horizontal_blur(bitmap, blur_radius);
        vertical_blur(bitmap, blur_radius);
    }

	if(flags[OPT_SALTPEPPER] == TRUE){
        printf("Salt & Pepper mode\n");
        saltpepper(bitmap,saltpepper_radius);
    }

	write_bitmap(bitmap, file_out);

    free_bitmap(bitmap);

    free(file_in);
    free(file_out);

    return EXIT_SUCCESS;
}

void print_dimensions(Bitmap *bitmap) {
    printf("Image width: %d\n", bitmap->info_header->width);
    printf("Image height: %d\n", bitmap->info_header->height);
}


void print_usage(void) {
	printf("OUTPUT FILE : -o FILE\n");
	printf("THRESHOLD : -t [0 - 1]\n");
	printf("INVERT : -i \n");
	printf("MONOCHROME : -m [G / r / g / b ]\n");
	printf("CROP : -c [top] [bottom] [left] [right]\n");
	printf("BLUR : -b [radius] \n");
	printf("SALT&PEPPER : -s [radius] \n");
}
