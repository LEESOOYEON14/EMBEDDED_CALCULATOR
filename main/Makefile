CC = gcc
I_HEADER = -I../header/
L_PATH = -L../source/
OBJS = bitmap.o blur.o crop.o invert.o monochrome.o threshold.o saltpepper.o bitmap_write.o 

main: main.o ../source/libbmp.a
	$(CC) -o main main.c $(I_HEADER) $(L_PATH) -lbmp

main.o: main.c
	$(CC) -c main.c $(I_HEADER)

clean:
	rm -f *.o *.a *.bmp
	rm main

