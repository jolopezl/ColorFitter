CC         = clang++
CFLAGS     = -c -g -Wall `root-config --cflags`
LDFLAGS    = `root-config --libs` -lMinuit -lGSL -lMathMore
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