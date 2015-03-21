INC_PATHS=src
SRC_PATH=src
OUT_EXE=mgirl-mica
OUT_EXE_SUFFIX=
OUT_EXE_PATH=bin
OUT_OBJ_PATH=obj

TOOLCHAIN_PREFIX=
CXX=$(TOOLCHAIN_PREFIX)g++
AR=$(TOOLCHAIN_PREFIX)gcc-ar

# cocos2d
COCOS_DIR?=cocos2d-x
COCOS_INC_PATHS=$(COCOS_DIR)/cocos $(COCOS_DIR)/cocos/editor-support $(COCOS_DIR)/external
COCOS_LIB_PATH=$(COCOS_DIR)/build/linux-build/lib
COCOS_LIBS=cocos2d glfw GLEW GL X11 pthread tinyxml2 freetype jpeg png tiff webp box2d xxhash unzip z fontconfig

# External libs
EXT_INC_PATHS?=external/libutils/inc
EXT_LIB_PATHS?=external/libutils/lib
EXT_LIBS?=utils-r

EXT_LIBUTILS_FLAGS=LU_BUILD=RELEASE USE_JPEG=0 USE_PNG=0

# Additional stuff
USER_INC_PATHS?=
USER_LIB_PATHS?=
USER_LIBS?=
USER_SYMBOLS?=

$(info Running makefile for Linux GCC...)

ifneq ($(firstword $(sort $(MAKE_VERSION) 3.81)),3.81)
$(error Require GNU Make 3.81 or newer)

else
$(info Make version = $(MAKE_VERSION))

endif

$(info CC = $(shell $(CC) --version | (read -r line; echo $$line)))

$(info User include paths = $(USER_INC_PATHS))
$(info User lib paths = $(USER_LIB_PATHS))
$(info User libs = $(USER_LIBS))
$(info User symbols = $(USER_SYMBOLS))


.DEFAULT_GOAL:=all

CPPFLAGS=
CXXFLAGS=
ARFLAGS=
LDFLAGS=
LDLIBS=
BIN_SUFFIX=

# Warnings are all over cocos2d's headers, hide them
CPPFLAGS+=$(addprefix -I,$(INC_PATHS)) $(addprefix -I,$(USER_INC_PATHS)) $(addprefix -I,$(EXT_INC_PATHS)) $(addprefix -isystem,$(COCOS_INC_PATHS))
CPPFLAGS+=$(addprefix -D,$(USER_SYMBOLS))
GCH_CPPFLAGS:=$(CPPFLAGS)
CPPFLAGS+=-MMD

CXXFLAGS+=-fmessage-length=0
CXXFLAGS+=-fno-strict-aliasing -ffunction-sections -fdata-sections
CXXFLAGS+=-std=gnu++1y
CXXFLAGS+=-Wall -Wextra -pedantic

ARFLAGS+=-r

LDFLAGS+=-Wl,--gc-sections
LDFLAGS+=$(addprefix -L,$(USER_LIB_PATHS)) $(addprefix -L,$(EXT_LIB_PATHS)) $(addprefix -L,$(COCOS_LIB_PATH))
LDLIBS+=$(addprefix -l,$(USER_LIBS)) $(addprefix -l,$(EXT_LIBS)) $(addprefix -l,$(COCOS_LIBS))


ifeq ($(PROJ_BUILD),DEBUG)
BIN_SUFFIX:=$(BIN_SUFFIX)-d
CPPFLAGS+=-DDEBUG=1
CPPFLAGS+=-O0 -g3
$(info Build = DEBUG)

else ifeq ($(PROJ_BUILD),RELEASE)
BIN_SUFFIX:=$(BIN_SUFFIX)-r
CPPFLAGS+=-DRELEASE=1 -DNDEBUG
CPPFLAGS+=-O2 -g0
$(info Build = RELEASE)

else
$(warning Unknown build type, defaulting to DEBUG (set PROJ_BUILD))
BIN_SUFFIX:=$(BIN_SUFFIX)-d
CPPFLAGS+=-DDEBUG=1
CPPFLAGS+=-O0 -g3
$(info Build = DEBUG)

endif


ifeq ($(MAKECMDGOALS),dry)
CPPFLAGS+=-fsyntax-only
$(info Performing dry run (no binary))
endif

# End setting flags

$(info Building $(OUT_EXE)$(BIN_SUFFIX)$(OUT_EXE_SUFFIX))

SRC_FILES:=$(shell find $(SRC_PATH) -type f -name *.cpp)

OBJ_FILES:=$(SRC_FILES:$(SRC_PATH)/%.cpp=$(OUT_OBJ_PATH)/%.o)
OBJ_FILES:=$(OBJ_FILES:%.o=%$(BIN_SUFFIX).o)

DEPENDS:=$(OBJ_FILES:.o=.d)
-include $(DEPENDS)

# Create all the DIRs
OUT_DIRS:=$(sort $(dir $(OBJ_FILES)))
$(shell mkdir -p $(OUT_DIRS) $(OUT_EXE_PATH))


.PHONY: all clean self-clean dry

all: $(OUT_EXE_PATH)/$(OUT_EXE)$(BIN_SUFFIX)$(OUT_EXE_SUFFIX)

dry: $(OBJ_FILES)

.SECONDEXPANSION:

$(OUT_EXE_PATH)/$(OUT_EXE)$(BIN_SUFFIX)$(OUT_EXE_SUFFIX): external/libutils/lib/libutils-r.a $(SRC_PATH)/cocos2d_wrapper.h.gch $(OBJ_FILES)
	$(info Linking objects)
	@$(CXX) $(LDFLAGS) -o $@ $(OBJ_FILES) $(LDLIBS)

external/libutils/lib/libutils-r.a:
	$(MAKE) -C external/libutils $(EXT_LIBUTILS_FLAGS) all

$(SRC_PATH)/cocos2d_wrapper.h.gch: $(SRC_PATH)/cocos2d_wrapper.h
	$(info Precompiling cocos2d-x header)
	@$(CXX) $(GCH_CPPFLAGS) $(CXXFLAGS) -x c++-header $(SRC_PATH)/cocos2d_wrapper.h

$(OUT_OBJ_PATH)/%.o: $$(subst $(BIN_SUFFIX),,$(SRC_PATH)/%.cpp)
	$(info Compiling $(<))
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean: self-clean
	$(info Cleaning external libs $(<))
	$(MAKE) -C external/libutils $(EXT_LIBUTILS_FLAGS) clean

self-clean:
	$(info Cleaning $(<))
	@rm -f $(OUT_EXE_PATH)/*
	@find $(OUT_OBJ_PATH) -type f \( -name *.o -o -name *.d \) -exec rm -f {} \;
