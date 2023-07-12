cc := gcc

OBJDIR := objects
CFLAGS := -g -O1 -fpic

# Make a window.o object file
area.o: area.h area.c
	$(cc) -c $(CFLAGS) -o $@ area.c

# ================================================================ #

.PHONY: clean

clean:
	rm -rf $(OBJDIR) ./*.a ./*.o ./*.out

# ================================ #