CC        = clang++
CCFLAGS   = -c -g -Wall
# CCFLAGS += -fPIC -Wno-deprecated
CCFLAGS  += -O2
CCFLAGS  += `root-config --cflags`
CCFLAGS  += -I./include -I/usr/local/include/

LDFLAGS   = `root-config --libs` -lMinuit -lgsl -lMathMore
LDFLAGS  += -L/usr/local/lib

CCSRCS  = $(wildcard ./source/*.cc)
DEPS    = $(wildcard ./include/*.h)
EXE     = ./bin/ifitx.exe

CCOBJS    = $(CCSRCS:%.cc=%.o)

all: $(CCSRCS) $(DEPS) $(EXE)

$(EXE): $(CCOBJS)
	$(CXX) $(LDFLAGS) $(CCOBJS) -o $@

#.cc.o :
%.o: %.cc $(DEPS)
	@echo Compiling $@
	@$(CXX) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(EXE) $(CCOBJS)

print:
	@echo $(DEPS)

# $(CCOBJS): $(CCSRCS) $(DEPS)
# 	$(CXX) $(CFLAGS) $(CCSRCS)