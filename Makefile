IDIR =./include
CC=g++
CFLAGS= -std=c++11 -O2 -I$(IDIR)

ODIR=obj
LDIR =./lib

LIBS=-lm

_MODS = main learn myrandom network serialize tavla test

_DEPS = $(patsubst %,%.h,$(_MODS)) globals.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = $(patsubst %,%.o,$(_MODS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
OUT_DIR = obj include nets

MKDIR_P = mkdir -p
.PHONY: directories

all: directories tavla

directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

tavla: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean: