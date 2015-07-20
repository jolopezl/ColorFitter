CC=g++
CFLAGS=-c -g -Wall `root-config --cflags` -m64
LDFLAGS=`root-config --libs` -lMinuit -lGSL -lMathMore -m64
SOURCES=main.cc ifit.cc model.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=ifitx.exe

all: $(SOURCES) $(EXECUTABLE)

$(OBJECTS):
	$(CC) $(CFLAGS) $(SOURCES)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
