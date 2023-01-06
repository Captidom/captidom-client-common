IDIR=include
SRC_DIR=src
EXAMPLE_DIR=example
LDIR=../lib
OBJ_DIR=build/obj
BINDIR=build

ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))


.DEFAULT_GOAL := all

APPNAME=test

CC=$(CROSS_COMPILE)gcc
DEPENDENCY_CFLAGS=
DEPENDENCY_CXXFLAGS=
CFLAGS=$(GLOBAL_CFLAGS) -I$(IDIR) -std=c++11
STATIC_LIBS = -lstdc++
SHARED_LIBS = 
LIBS = -Wl,-Bstatic $(STATIC_LIBS) -Wl,-Bdynamic $(SHARED_LIBS)
LDFLAGS=

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
EXAMPLE_SRC_FILES := $(EXAMPLE_DIR)/main.cpp
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES)) $(patsubst $(EXAMPLE_DIR)/%.cpp,$(OBJ_DIR)/example/%.o,$(EXAMPLE_SRC_FILES))

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


$(BINDIR)/$(APPNAME): $(OBJ_FILES)
	CFLAGS="$(DEPENDENCY_CFLAGS)" \
	CXXFLAGS="$(DEPENDENCY_CXXFLAGS)" \
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(LDFLAGS)

linux_x64_86: $(BINDIR)/$(APPNAME)

all: linux_x64_86

.PHONY: clean

clean:
	rm -f $(OBJ_FILES)
	rm -f $(BINDIR)/$(APPNAME)


