LIB_IDIR=lib/include/captidom-client-common
EXAMPLE_IDIR=lib/include
SRC_DIR=lib/src
EXAMPLE_DIR=example
OBJ_DIR=build/obj
BINDIR=build

ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))


.DEFAULT_GOAL := all

CC=$(CROSS_COMPILE)gcc
DEPENDENCY_CFLAGS=
DEPENDENCY_CXXFLAGS=
LIB_CFLAGS=$(GLOBAL_CFLAGS) -I$(LIB_IDIR) -std=c++11 -fPIC
EXAMPLE_CFLAGS=$(GLOBAL_CFLAGS) -I$(EXAMPLE_IDIR) -I$(LIB_IDIR) -std=c++11
STATIC_LIBS = -lstdc++
SHARED_LIBS = 
LIBS = -Wl,-Bstatic $(STATIC_LIBS) -Wl,-Bdynamic $(SHARED_LIBS)
LDFLAGS=

CPP_FILES := $(wildcard $(SRC_DIR)/*/*.cpp) 
CPP_FILES := $(CPP_FILES)$(wildcard $(SRC_DIR)/*.cpp)
EXAMPLE_SRC_FILES := $(EXAMPLE_DIR)/main.cpp
OBJ_FILES := $(patsubst $(SRC_DIR)/%,build/obj/%,$(CPP_FILES:.cpp=.o))
EXAMPLE_OBJ_FILES := $(patsubst $(EXAMPLE_DIR)/%.cpp,$(OBJ_DIR)/example/%.o,$(EXAMPLE_SRC_FILES))

ARCH=
ARCH_ARMHF=arm-linux-gnueabihf
ARCH_AARCH64=aarch64-linux-gnu

CMAKE_TOOLCHAIN=
CONFIGURE_ARCH=

build/obj/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	CFLAGS="$(DEPENDENCY_CFLAGS)" \
	CXXFLAGS="$(DEPENDENCY_CXXFLAGS)" \
	$(CC) -c -o $@ $< $(LIB_CFLAGS)

$(OBJ_DIR)/example/%.o: $(EXAMPLE_DIR)/%.cpp
	CFLAGS="$(DEPENDENCY_CFLAGS)" \
	CXXFLAGS="$(DEPENDENCY_CXXFLAGS)" \
	$(CC) -c -o $@ $< $(EXAMPLE_CFLAGS)


captidom-client-common.so: $(OBJ_FILES)
	CFLAGS="$(DEPENDENCY_CFLAGS)" \
	CXXFLAGS="$(DEPENDENCY_CXXFLAGS)" \
	$(CC) -shared -o $(BINDIR)/$@ $^ $(LIB_CFLAGS) $(LIBS) $(LDFLAGS)


library: captidom-client-common.so

$(BINDIR)/example: library $(EXAMPLE_OBJ_FILES)
	CFLAGS="$(DEPENDENCY_CFLAGS)" \
	CXXFLAGS="$(DEPENDENCY_CXXFLAGS)" \
	$(CC) -o $@ $(EXAMPLE_OBJ_FILES) $(EXAMPLE_CFLAGS) $(LIBS) $(LDFLAGS) -L$(BINDIR) -l:captidom-client-common.so

example: $(BINDIR)/example

all: library example

.PHONY: clean

clean:
	rm -f $(OBJ_FILES) ${EXAMPLE_OBJ_FILES}
	rm -f $(BINDIR)/captidom-client-common.so
	rm -f $(BINDIR)/example


