CC         =  g++
CFLAGS     = -c -g -Wall -O2 `root-config --cflags`
CFLAGS    += -I/usr/local/boost/1_57_0/include
LDFLAGS    = `root-config --libs` -lMinuit -lgsl -lMathMore
LDFLAGS   += -L/usr/local/boost/1_57_0/lib
SOURCES    = $(wildcard *.cc)
DEPS       = $(wildcard *.h)
OBJECTS    = $(SOURCES:.cc=.o)
EXECUTABLE = ifitx.exe

all: $(SOURCES) $(DEPS) $(EXECUTABLE)

$(OBJECTS): $(SOURCES) $(DEPS)
	$(CC) $(CFLAGS) $(SOURCES)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

#.cc.o :
%.o: %.cc $(DEPS)
	@echo Compiling $@
	@$(CXX) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

print:
	@echo $(DEPS)


# #
# # TODO: Move `libmongoclient.a` to /usr/local/lib so this can work on production servers
# #
 
# CC := g++ # This is the main compiler
# # CC := clang --analyze # and comment out the linker last line for sanity
# SRCDIR := src
# BUILDDIR := build
# TARGET := bin/runner
 
# SRCEXT := cpp
# SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
# OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
# CFLAGS := -g # -Wall
# LIB := -pthread -lmongoclient -L lib -lboost_thread-mt -lboost_filesystem-mt -lboost_system-mt
# INC := -I include

# $(TARGET): $(OBJECTS)
#   @echo " Linking..."
#   @echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

# $(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
#   @mkdir -p $(BUILDDIR)
#   @echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

# clean:
#   @echo " Cleaning..."; 
#   @echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# # Tests
# tester:
#   $(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# # Spikes
# ticket:
#   $(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

# .PHONY: clean