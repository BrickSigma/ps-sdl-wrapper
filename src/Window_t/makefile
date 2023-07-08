cc := gcc

OBJDIR := objects
CFLAGS := -g -O1 -fpic

# Make a window.o object file
window.o: window.h window.c
	$(cc) -c $(CFLAGS) -o $@ window.c

# ================================================================ #

.PHONY: clean

clean:
	rm -rf $(OBJDIR) ./*.a ./*.o ./*.out

# ================================ #