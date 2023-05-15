cc = gcc
OBJDIR = objects
CFLAGS = -c -Wall -O1 -fpic
AR = ar
ARFLAGS = -r -c

lib: $(OBJDIR)/plpgen.o
	$(AR) $(ARFLAGS) libplpgen.a $(OBJDIR)/plpgen.o guard/$(OBJDIR)/guard.o

$(OBJDIR)/plpgen.o: plpgen.h plpgen.c guard/$(OBJDIR)/guard.o
	$(cc) -g $(CFLAGS) -o $(OBJDIR)/plpgen.o plpgen.c

guard/$(OBJDIR)/guard.o:
	$(MAKE) -C guard

test: $(OBJDIR)/main.o libplpgen.a
	$(cc) -o a.out $(OBJDIR)/main.o -L. -lplpgen

$(OBJDIR)/main.o: main.c
	$(cc) -g $(CFLAGS) -o $(OBJDIR)/main.o main.c

.PHONY: clean
clean:
	rm -rf $(OBJDIR) ./*.o *.a *.out
	rm -rf guard/$(OBJDIR) guard/*.o guard/*.a

$(shell mkdir -p $(OBJDIR))