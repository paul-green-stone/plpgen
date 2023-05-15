cc = gcc
OBJDIR = objects
CFLAGS = -c -Wall -O1 -fpic
AR = ar
ARFLAGS = -r -c

lib: $(OBJDIR)/plpgen.o
	$(AR) $(ARFLAGS) libplpgen.a $(OBJDIR)/plpgen.o $(OBJDIR)/guard.o

$(OBJDIR)/plpgen.o: plpgen.h plpgen.c $(OBJDIR)/guard.o
	$(cc) -g $(CFLAGS) -o $(OBJDIR)/plpgen.o plpgen.c

$(OBJDIR)/guard.o: guard/guard.h guard/guard.c
	$(cc) -g $(CFLAGS) -o $(OBJDIR)/guard.o guard/guard.c

test: $(OBJDIR)/main.o libplpgen.a
	$(cc) -o a.out $(OBJDIR)/main.o -L. -lplpgen

$(OBJDIR)/main.o: main.c
	$(cc) -g $(CFLAGS) -o $(OBJDIR)/main.o main.c

.PHONY: clean
clean:
	rm -rf $(OBJDIR) ./*.o *.a *.out

$(shell mkdir -p $(OBJDIR))