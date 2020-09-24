CCSRCDIR = ./
SRC_CC   = $(notdir dddsigma_QsqNuZh.C)
CC_SRC   = $(addprefix $(CCSRCDIR),$(SRC_CC))

LD_FLAGS:=$(shell root-config --ldflags)
CXX_FLAGS:= -I. $(shell root-config --cflags) -I/Users/lopez/cernbox/phd/ColorFitter/analysis-HERMES/pythia/esteban/LHAPDF/include/ -O2

LIBS:= -L. $(shell root-config --glibs) -lRooFitCore -lRooFit -lSpectrum -lMathMore -L/Users/lopez/cernbox/phd/ColorFitter/analysis-HERMES/pythia/esteban/LHAPDF/lib -lLHAPDF
CC:=g++
CXX:=g++
LD:=g++

OBJDIR   = ./build/
OBJ_CC   = $(SRC_CC:.C=.o)
CC_OBJ   = $(addprefix $(OBJDIR),$(OBJ_CC))

dddsigma_QsqNuZh: $(OBJDIR) $(CC_OBJ)
	@echo
	@echo making executable $@
	$(LD) $(LD_FLAGS) $(LIBS) -o $@ $(CC_OBJ)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o : $(CCSRCDIR)%.C
	@echo
	@echo Compiling $@
	$(CXX) $(CXX_FLAGS) -c $< -o $@
