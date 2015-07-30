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