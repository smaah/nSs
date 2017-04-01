CC  = gcc
CXX = g++
FC  = gfortran
LINKER = $(CXX)

ANSI_CFLAGS  = -ansi
ANSI_CFLAGS += -std=c++0x
ANSI_CFLAGS += -pedantic
ANSI_CFLAGS += -Wextra

CFLAGS   = -O2 -g -Wno-format  -Wall $(ANSI_CFLAGS) 
CXXFLAGS = $(CFLAGS)
FCFLAGS  = 
LFLAGS   =  
DEFINES  = -D_GNU_SOURCE
INCLUDES =
LIBS     =

debug: CXXFLAGS += -DDEBUG
debug: $(TARGET)
