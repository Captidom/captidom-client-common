LIB_IDIR=lib/include
EXAMPLE_IDIR=lib/include
SRC_DIR=lib/src
EXAMPLE_DIR=example
ARCH=$(shell ${CC} -dumpmachine)
BUILD=build/${ARCH}
OBJ_DIR=${BUILD}/obj
BINDIR=${BUILD}

ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))


.DEFAULT_GOAL := all

CC=$(CROSS_COMPILE)gcc
AR=$(CROSS_COMPILE)ar
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
HEADER_FILES := $(wildcard $(LIB_IDIR)/*/*.h)
HEADER_FILES := $(HEADER_FILES)$(wildcard $(LIB_IDIR)/*.h)
EXAMPLE_SRC_FILES := $(EXAMPLE_DIR)/main.cpp
OBJ_FILES := $(patsubst $(SRC_DIR)/%,${BUILD}/obj/%,$(CPP_FILES:.cpp=.o))
EXAMPLE_OBJ_FILES := $(patsubst $(EXAMPLE_DIR)/%.cpp,$(OBJ_DIR)/example/%.o,$(EXAMPLE_SRC_FILES))

TEST_CPP_FILES := $(wildcard test/src/*/*.cpp) 
TEST_CPP_FILES := $(TEST_CPP_FILES)$(wildcard test/src/*.cpp)
TEST_OBJ_FILES := $(patsubst test/%,${BUILD}/obj/test/%,$(TEST_CPP_FILES:.cpp=.o))
TEST_BIN_FILES := $(patsubst ${BUILD}/obj/test/%,${BUILD}/test/%,$(TEST_OBJ_FILES:.o=.bin))

${BUILD}/obj/%.o: $(SRC_DIR)/%.cpp $(HEADER_FILES)
	mkdir -p $(dir $@)
	CFLAGS="$(DEPENDENCY_CFLAGS)" \
	CXXFLAGS="$(DEPENDENCY_CXXFLAGS)" \
	$(CC) -c -o $@ $< $(LIB_CFLAGS)

$(OBJ_DIR)/example/%.o: $(EXAMPLE_DIR)/%.cpp  $(HEADER_FILES)
	mkdir -p $(dir $@)
	CFLAGS="$(DEPENDENCY_CFLAGS)" \
	CXXFLAGS="$(DEPENDENCY_CXXFLAGS)" \
	$(CC) -c -o $@ $< $(EXAMPLE_CFLAGS)


$(BINDIR)/libcaptidomclientcommon.a: $(OBJ_FILES)
	mkdir -p $(dir $@)
	CFLAGS="$(DEPENDENCY_CFLAGS)" \
	CXXFLAGS="$(DEPENDENCY_CXXFLAGS)" \
	$(AR) rcs $@ $(OBJ_FILES)


library: $(BINDIR)/libcaptidomclientcommon.a

$(BINDIR)/example: library $(EXAMPLE_OBJ_FILES)
	mkdir -p $(dir $@)
	CFLAGS="$(DEPENDENCY_CFLAGS)" \
	CXXFLAGS="$(DEPENDENCY_CXXFLAGS)" \
	$(CC) -o $@ $(EXAMPLE_OBJ_FILES) $(EXAMPLE_CFLAGS) $(LIBS) $(LDFLAGS) -L$(BINDIR) -l:lcaptidomclientcommon

example: $(BINDIR)/example

testlib: $(BINDIR)/googletest/lib/libgtest.a

$(BINDIR)/googletest/lib/libgtest.a:
	mkdir -p $(BINDIR)/googletest
	cd $(BINDIR)/googletest && cmake ../../../testlib/googletest
	cd $(BINDIR)/googletest && $(MAKE)

test: library testlib $(TEST_BIN_FILES)

${BUILD}/obj/test/%.o: test/%.cpp  $(HEADER_FILES)
	mkdir -p $(dir $@)
	CFLAGS="$(DEPENDENCY_CFLAGS)" \
	CXXFLAGS="$(DEPENDENCY_CXXFLAGS)" \
	$(CC) -c -o $@ $< $(LIB_CFLAGS) -I$(EXAMPLE_IDIR) -Itestlib/googletest/googletest/include -Itestlib/googletest/googlemock/include -Itest/include -std=c++11

${BUILD}/test/%.bin: ${BUILD}/obj/test/%.o testlib
	mkdir -p $(dir $@)
	CFLAGS="$(DEPENDENCY_CFLAGS)" \
	CXXFLAGS="$(DEPENDENCY_CXXFLAGS)" \
	$(CC) -o $@ $< $(BINDIR)/googletest/lib/libgtest.a $(BINDIR)/googletest/lib/libgtest_main.a $(BINDIR)/googletest/lib/libgmock.a $(EXAMPLE_CFLAGS) $(LIBS) $(LDFLAGS) -L$(BINDIR) -lpthread -lm  -lcaptidomclientcommon

runtest: test
	$(foreach path,$(TEST_BIN_FILES),LD_LIBRARY_PATH=$(BINDIR) ./$(path);)

all: library example test

.PHONY: clean

clean:
	rm -rf build


