include Makefile.arch

#
# stuff to make
#
#SOURCES=$(wildcard *.C)
SOURCES=$(wildcard fakeratelooper.C)
OBJECTS=$(SOURCES:.C=.o)
#LIB=libCMS3NtupleMacrosCORE.so
LIB=fakeratelooper.so

#
# how to make it
#

$(LIB): $(OBJECTS) 
	$(LD) $(LDFLAGS) $(SOFLAGS) $(OBJECTS) $(ROOTLIBS) -lTMVA -lXMLIO -lMLP -lTreePlayer -o $@

%.o:	%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

#
# target to build
# likelihood id library
#

all: $(LIB) 
clean:
	rm -f *.o \
	rm -f *.d \
	rm -f *.so
