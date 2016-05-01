LS = ls
RM = rm -f
CP = cp
SLASH = /

ifeq ($(shell uname),Linux)
	DSO_POSTFIX = so
else

ifeq ($(shell uname),Darwin)
	DSO_POSTFIX = dylib
else
	# May be Windows
	LS = dir /b
	RM = del /f
	CP = copy
	SLASH = \\
	DSO_POSTFIX = dll
endif

endif

ifdef DEBUG
	CC_DBG_FLAGS = -g -DDEBUG
else
	CC_DBG_FLAGS = -O2 -D__NO_INLINE__
endif

SOURCES := $(shell $(LS) *.cpp)
DEPS := $(SOURCES:.cpp=.d)
HEADERS := $(shell $(LS) *.h *.hpp)
OBJECTS := $(patsubst %.cpp, %.o, $(SOURCES))