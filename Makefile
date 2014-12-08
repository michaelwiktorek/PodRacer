ANGEL_DISABLE_FMOD := $(shell sed -rn 's/^[[:space:]]*\#define[[:space:]]+ANGEL_DISABLE_FMOD[[:space:]]+([[:digit:]])[[:space:]]*$$/\1/p' ./lib/Angel/AngelConfig.h)
ANGEL_DISABLE_DEVIL := $(shell sed -rn 's/^[[:space:]]*\#define[[:space:]]+ANGEL_DISABLE_DEVIL[[:space:]]+([[:digit:]])[[:space:]]*$$/\1/p' ./lib/Angel/AngelConfig.h)

COMPILER = g++ -std=c++11
TARGET = PodRacer
ANGEL_FLAGS = -D ANGEL_RELEASE
ARCH := $(shell uname -m)
ALLEGRO_LIBS := $(shell allegro-config --libs 2>/dev/null)
CWD := $(shell pwd)
CODE_DIR := $(shell readlink -f lib)
LIBANGEL = ./lib/Angel/libangel.a
LUA = ./lib/Angel/Libraries/angel-lua-build/lua
WRAPPER = ./lib/Angel/Scripting/Interfaces/AngelLuaWrapping.cpp

INCLUDE = \
	-I./lib/Angel \
	-I./lib/Angel/Libraries/glfw-3.0.3/include \
	-I./lib/Angel/Libraries/Box2D-2.2.1 \
	-I./lib/Angel/Libraries/FTGL/include \
	-I./lib/Angel/Libraries/lua-5.2.1/src \
	-I./src \
	-I/usr/include/freetype2
ifneq ($(ANGEL_DISABLE_FMOD), 1)
	INCLUDE += -I./lib/Angel/Libraries/FMOD/inc
endif

LIBS = \
	$(LIBANGEL) \
	./lib/Angel/Libraries/glfw-3.0.3/src/libglfw3.a \
	./lib/Angel/Libraries/Box2D-2.2.1/Build/Box2D/libBox2D.a \
	./lib/Angel/Libraries/FTGL/unix/src/.libs/libftgl.a \
	./lib/Angel/Libraries/gwen/lib/linux/gmake/libgwen_static.a \
	./lib/Angel/Libraries/angel-lua-build/liblua.a

ifneq ($(ANGEL_DISABLE_FMOD), 1)
	ifeq ($(ARCH),x86_64)
		LIBS += ./lib/Angel/Libraries/FMOD/lib/libfmodex64.so
	else
		LIBS += ./lib/Angel/Libraries/FMOD/lib/libfmodex.so
	endif
endif

SHLIBS = -lGL -lGLU -ldl -lfreetype -lXrandr -lX11 -lpthread -lrt -lXxf86vm -lXi
SHLIBS += $(ALLEGRO_LIBS)
ifeq ($(ANGEL_DISABLE_FMOD), 1)
	SHLIBS += -lopenal -lvorbisfile
endif
ifneq ($(ANGEL_DISABLE_DEVIL),1)
	SHLIBS += -lIL -lILU -lILUT
else
	SHLIBS += -lpng
endif

SYSSOURCES = \
	$(WRAPPER)

# LIST OUR SOURCES HERE
SOURCES := $(shell find src -type f -name *.cpp)

SYS_OBJECTS = $(patsubst %.cpp,%.o,$(SYSSOURCES))
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))

.PHONY: clean all SWIG-Wrapper

%.o: %.cpp
	$(COMPILER) -c $(INCLUDE) -Wno-write-strings -Wno-deprecated -o $@ $^

all: $(TARGET)

publish: $(TARGET)
	$(LUA) ./lib/Tools/BuildScripts/publish_linux.lua -i $(CWD) -e $(TARGET)

SWIG-Wrapper:
	$(LUA) ./lib/Tools/BuildScripts/swig_wrap.lua -p "$(CODE_DIR)"

$(WRAPPER): SWIG-Wrapper

$(TARGET): $(LIBANGEL) $(OBJECTS) $(SYS_OBJECTS) $(WRAPPER)
	$(COMPILER) -o $@ $(OBJECTS) $(SYS_OBJECTS) $(LIBS) $(SHLIBS) $(ANGEL_FLAGS)
	cp -p ./lib/Angel/Scripting/EngineScripts/*.lua Resources/Scripts

clean:
	rm -f $(OBJECTS) $(SYS_OBJECTS) $(TARGET) $(WRAPPER)

$(LIBANGEL):
	cd ./lib/Angel && make
