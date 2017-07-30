CC			= g++
OBJDIR	= obj
CFLAGS  = -std=gnu++0x -Wall -Werror -pedantic
SRCDIR	= src
OUTDIR	= bin

OOBJ		= Parser.o Game.o

_DEPS		= Definitions.hpp Parser.hpp Game.hpp Location.hpp
DEPS    = $(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJ		= $(OOBJ) Main.o
OBJ			= $(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTDIR)/Patcher: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean check all

clean:
	rm -f $(OBJDIR)/*.o $(OUTDIR)/Patcher $(OUTDIR)/Test

check: $(OUTDIR)/Patcher $(OUTDIR)/Test
