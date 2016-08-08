# TODO: 
#
 
CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
TARGETDIR := bin
TARGET := $(TARGETDIR)/tavla
INCDIR := include

REQDIRS := output
 
SRCEXT := cpp
INCEXT := h
SOURCES := $(wildcard $(SRCDIR)/*.$(SRCEXT))
HEADERS := $(wildcard $(INCDIR)/*.$(INCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -std=c++11 -g -O2 # -Wall
LIB := # 
INC := -I include

all: $(TARGET) directories test

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(HEADERS)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(TARGETDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

directories: $(REQDIRS)

$(REQDIRS):
	@mkdir -p $(REQDIRS)

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

cleanout:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(REQDIRS)"; $(RM) -r $(REQDIRS)
	@mkdir -p $(REQDIRS)

# Tests

test: $(TARGET)
	$(TARGET) test

#tester:
#	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
#ticket:
#	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean directories