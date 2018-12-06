CC = gcc
I_HEADER = -I../header/
OBJS = bitmap.o blur.o crop.o invert.o threshold.o bitmap_write.o saltpepper.o monochrome.o

libbmp.a: $(OBJS)
	ar rv libbmp.a $(OBJS)

%.o: %.c
	$(CC) -c $< -o $@ $(I_HEADER)

clean:
	rm -f *.o *.a

