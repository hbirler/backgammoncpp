# TODO: 
#
CC := g++ # This is the main compiler
EMCC := emcc
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
TARGETDIR := bin
TARGET := $(TARGETDIR)/tavla
EMTARGET := $(TARGETDIR)/tavla.html
INCDIR := include

WDIR := C:\git\tavlacpp

REQDIRS := output
 
SRCEXT := cpp
INCEXT := h
SOURCES := $(wildcard $(SRCDIR)/*.$(SRCEXT))
HEADERS := $(wildcard $(INCDIR)/*.$(INCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
EMOBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.bc))
CFLAGS := -std=c++11 -g -O2 # -Wall
EMCFLAGS := -std=c++11 -O2
LIB := # 
INC := -I include




all: $(TARGET) directories test

emscripten: override CC := $(EMCC)
emscripten: override CFLAGS := $(EMCFLAGS)
emscripten: override TARGET := bin/tavla.htm
emscripten: override OBJECTS := $(EMOBJECTS)
emscripten: $(EMTARGET)
	
$(EMTARGET): $(EMOBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.bc: $(SRCDIR)/%.$(SRCEXT) $(HEADERS)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(TARGETDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<


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
	#@echo " $(RM) -r $(REQDIRS)"; $(RM) -r $(REQDIRS)
	#@mkdir -p $(REQDIRS)

# Tests

test: $(TARGET)
	$(TARGET) test

#tester:
#	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
#ticket:
#	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean directories