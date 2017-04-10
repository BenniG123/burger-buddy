include Makefile.config

PROJECT := burger-buddy
SRCS    := $(wildcard *.cpp)
OBJS    := $(SRCS:.cpp=.o)

include Makefile.rules
