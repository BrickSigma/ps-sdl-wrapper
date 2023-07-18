cc := gcc

OBJDIR := objects
CFLAGS := -g -O1 -fpic

# Make a window.o object file
object.o: object.h object.c
	$(cc) -c $(CFLAGS) -o $@ object.c

# ================================================================ #

.PHONY: clean

clean:
	rm -rf $(OBJDIR) ./*.a ./*.o ./*.out

# ================================ #