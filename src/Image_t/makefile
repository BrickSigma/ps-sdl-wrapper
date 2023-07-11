cc := gcc

OBJDIR := objects
CFLAGS := -g -O1 -fpic

# Make a window.o object file
image.o: image.h image.c
	$(cc) -c $(CFLAGS) -o $@ image.c

# ================================================================ #

.PHONY: clean

clean:
	rm -rf $(OBJDIR) ./*.a ./*.o ./*.out

# ================================ #