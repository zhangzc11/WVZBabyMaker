# Simple makefile

EXE=processBaby

SOURCES=$(wildcard babymaker/*.cc) $(wildcard modules/*.cc) $(wildcard rooutil/rooutil.cc) $(wildcard coreutil/*.cc) $(wildcard CORE/*.cc) $(wildcard CORE/Tools/*.cc) $(wildcard CORE/Tools/MT2/*.cc) $(wildcard CORE/Tools/btagsf/*.cc) $(wildcard CORE/Tools/datasetinfo/*.cc) $(wildcard CORE/Tools/JetResolution/JetResolution.cxx) $(wildcard StopAnalysis/StopCORE/METCorr/*.cc)
TMPOBJECTS=$(SOURCES:.cc=.o)
OBJECTS=$(TMPOBJECTS:.cxx=.o)

CC          = g++
CXX         = g++
CXXFLAGS    = -g -O2 -Wall -fPIC -Wshadow -Woverloaded-virtual
LD          = g++
LDFLAGS     = -g -O2
SOFLAGS     = -g -shared
CXXFLAGS    = -g -O2 -Wall -fPIC -Wshadow -Woverloaded-virtual
LDFLAGS     = -g -O2
ROOTLIBS    = $(shell root-config --libs)
ROOTCFLAGS  = $(shell root-config --cflags)
CXXFLAGS   += $(ROOTCFLAGS)
CFLAGS      = $(ROOTCFLAGS) -Wall -Wno-unused-function -g -O2 -fPIC -fno-var-tracking
EXTRACFLAGS = $(shell rooutil-config) -Icoreutil/ -Imodules/ -ICORE/ -Ibabymaker/ -IStopAnalysis/StopCORE/METCorr/
EXTRAFLAGS  = -fPIC -ITMultiDrawTreePlayer -Wunused-variable -lTMVA -lEG -lGenVector -lXMLIO -lMLP -lTreePlayer

$(EXE): $(OBJECTS)
	$(LD) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) $(ROOTLIBS) $(EXTRAFLAGS) -o $@

%.o: %.cc
	$(CC) $(CFLAGS) $(EXTRACFLAGS) $< -c -o $@

%.o: %.cxx
	$(CC) $(CFLAGS) $(EXTRACFLAGS) $< -c -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(EXE)

