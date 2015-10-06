CC        = clang++
CCFLAGS   = -c -g -Wall
# CCFLAGS += -fPIC -Wno-deprecated
CCFLAGS  += -O2
CCFLAGS  += `root-config --cflags`
CCFLAGS  += -I./include -I/usr/local/include/

LDFLAGS   = `root-config --libs` -lMinuit -lgsl -lMathMore
LDFLAGS  += -L/usr/local/lib

SOURCES  = $(wildcard ./source/*.cc)
DEPS    = $(wildcard ./include/*.h)
EXE     = ./bin/ifitx.exe

BIN_DIR = bin

#CCOBJS    = $(SOURCES:%.cc=%.o)
CCOBJS    = $(patsubst ./source/%.cc,build/%.o,$(SOURCES))

all: $(SOURCES) $(DEPS) $(EXE)

$(EXE): $(CCOBJS)
	mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $(CCOBJS) -o $@

#.cc.o :
build/%.o: source/%.cc $(DEPS)
	@echo Compiling $@
	@$(CXX) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(EXE) $(CCOBJS)

print:
	@echo $(DEPS)

# $(CCOBJS): $(SOURCES) $(DEPS)
# 	$(CXX) $(CFLAGS) $(SOURCES)