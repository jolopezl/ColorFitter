CC        = g++
CCFLAGS   = -c -g -Wall
CCFLAGS  += -fPIC -Wno-deprecated
CCFLAGS  += -O2
CCFLAGS  += `root-config --cflags`
CCFLAGS  += -I./include -I/usr/local/include/

LDFLAGS   = `root-config --libs` -lMinuit -lMathMore
LDFLAGS  += -L/usr/local/lib

SOURCES  = $(wildcard ./source/*.cc)
DEPS    = $(wildcard ./include/*.h)
EXE     = ./bin/ifitx.exe

#CCOBJS    = $(SOURCES:%.cc=%.o)
CCOBJS    = $(patsubst ./source/%.cc,build/%.o,$(SOURCES))

OBJDIR = build
BINDIR = bin

all: $(SOURCES) $(DEPS) $(EXE)

$(EXE): $(CCOBJS) | $(BINDIR)
	$(CXX) $(LDFLAGS) $(CCOBJS) -o $@

#.cc.o :
build/%.o: source/%.cc $(DEPS) | $(OBJDIR)
	@echo Compiling $@
	@$(CXX) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(EXE) $(CCOBJS)

print:
	@echo $(DEPS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# $(CCOBJS): $(SOURCES) $(DEPS)
# 	$(CXX) $(CFLAGS) $(SOURCES)
