cc := gcc

OBJDIR := objects
CFLAGS := -g -O1 -fpic

LDFLAGS := -lSDL2 -lSDL2_image -lm

all: main.c
	$(cc) $(CFLAGS) -o a.out $^ $(LDFLAGS) ../../libps.a

.PHONY: clean

clean:
	rm -rf $(OBJDIR) ./*.a ./*.o ./*.out