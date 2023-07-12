cc := gcc

OBJDIR := objects
CFLAGS := -g -O1 -fpic

LDFLAGS := -lSDL2 -lSDL2_image -lm

AR := ar
ARFLAGS := -r -c 

all: $(OBJDIR)/guard.o $(OBJDIR)/window.o $(OBJDIR)/image.o

# Make a guard.o object file
$(OBJDIR)/guard.o: guard/guard.c
	$(cc) -c $(CFLAGS) -o $@ $^

# Make a window.o object file
$(OBJDIR)/window.o: src/Window_t/window.c
	$(cc) -c $(CFLAGS) -o $@ $^

# Make an image.o object file
$(OBJDIR)/image.o: src/Image_t/image.c
	$(cc) -c $(CFLAGS) -o $@ $^

# Make an area.o object file
$(OBJDIR)/area.o: src/Area_t/area.c
	$(cc) -c $(CFLAGS) -o $@ $^

# Making a library
lib: $(OBJDIR)/guard.o $(OBJDIR)/window.o $(OBJDIR)/image.o $(OBJDIR)/area.o
	$(AR) $(ARFLAGS) libps.a $^

# ================================================================ #

.PHONY: clean

clean:
	rm -rf $(OBJDIR) ./*.a ./*.o ./*.out

# ================================ #

$(shell mkdir -p $(OBJDIR))