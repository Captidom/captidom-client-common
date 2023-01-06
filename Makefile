IDIR=captidom-channel-common/include
SRC_DIR=captidom-channel-common/src
EXAMPLE_DIR=example
OBJ_DIR=build/obj
BINDIR=build

ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))


.DEFAULT_GOAL := all

CC=$(CROSS_COMPILE)gcc
DEPENDENCY_CFLAGS=
DEPENDENCY_CXXFLAGS=
CFLAGS=$(GLOBAL_CFLAGS) -I$(IDIR) -std=c++11 -fPIC
STATIC_LIBS = -lstdc++
SHARED_LIBS = 
LIBS = -Wl,-Bstatic $(STATIC_LIBS) -Wl,-Bdynamic $(SHARED_LIBS)
LDFLAGS=

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
EXAMPLE_SRC_FILES := $(EXAMPLE_DIR)/main.cpp
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
EXAMPLE_OBJ_FILES := $(patsubst $(EXAMPLE_DIR)/%.cpp,$(OBJ_DIR)/example/%.o,$(EXAMPLE_SRC_FILES))

ARCH=
ARCH_ARMHF=arm-linux-gnueabihf
ARCH_AARCH64=aarch64-linux-gnu

CMAKE_TOOLCHAIN=
CONFIGURE_ARCH=

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	CFLAGS="$(DEPENDENCY_CFLAGS)" \
	CXXFLAGS="$(DEPENDENCY_CXXFLAGS)" \
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR)/example/%.o: $(EXAMPLE_DIR)/%.cpp
	CFLAGS="$(DEPENDENCY_CFLAGS)" \
	CXXFLAGS="$(DEPENDENCY_CXXFLAGS)" \
	$(CC) -c -o $@ $< $(CFLAGS)


captidom-channel-common.so: $(OBJ_FILES)
	CFLAGS="$(DEPENDENCY_CFLAGS)" \
	CXXFLAGS="$(DEPENDENCY_CXXFLAGS)" \
	$(CC) -shared -o $(BINDIR)/$@ $^ $(CFLAGS) $(LIBS) $(LDFLAGS)


library: captidom-channel-common.so

$(BINDIR)/example: library $(EXAMPLE_OBJ_FILES)
	CFLAGS="$(DEPENDENCY_CFLAGS)" \
	CXXFLAGS="$(DEPENDENCY_CXXFLAGS)" \
	$(CC) -o $@ $(EXAMPLE_OBJ_FILES) $(CFLAGS) $(LIBS) $(LDFLAGS) -L$(BINDIR) -l:captidom-channel-common.so

example: $(BINDIR)/example

all: library example

.PHONY: clean

clean:
	rm -f $(OBJ_FILES) ${EXAMPLE_OBJ_FILES}
	rm -f $(BINDIR)/captidom-channel-common.so
	rm -f $(BINDIR)/example


