CFLAGS = -Wall -g -ansi -O2 -std=c99

OBJS1 = filter.o main.o

all : denoise

denoise: $(OBJS1)
	$(CC) -pg -o $@ $?

clean:
	rm -rf $(OBJS1) denoise *~
