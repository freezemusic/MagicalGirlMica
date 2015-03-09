SRC_PATH=Classes
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
CPPFLAGS+=$(addprefix -isystem,$(COCOS_INC_PATHS)) $(addprefix -I,$(USER_INC_PATHS))
CPPFLAGS+=$(addprefix -D,$(USER_SYMBOLS))
CPPFLAGS+=-MMD

CXXFLAGS+=-fmessage-length=0
CXXFLAGS+=-fno-strict-aliasing -ffunction-sections -fdata-sections
CXXFLAGS+=-std=gnu++11
CXXFLAGS+=-Wall -Wextra -pedantic

ARFLAGS+=-r

LDFLAGS+=-Wl,--gc-sections
LDFLAGS+=$(addprefix -L,$(COCOS_LIB_PATH)) $(addprefix -L,$(USER_LIB_PATHS))
LDLIBS+=$(addprefix -l,$(COCOS_LIBS)) $(addprefix -l,$(USER_LIBS))


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


.PHONY: all clean dry

all: $(OUT_EXE_PATH)/$(OUT_EXE)$(BIN_SUFFIX)$(OUT_EXE_SUFFIX)

dry: $(OBJ_FILES)

.SECONDEXPANSION:

$(OUT_EXE_PATH)/$(OUT_EXE)$(BIN_SUFFIX)$(OUT_EXE_SUFFIX): $(OBJ_FILES)
	$(info Linking objects)
	@$(CXX) $(LDFLAGS) -o $@ $(OBJ_FILES) $(LDLIBS)

$(OUT_OBJ_PATH)/%.o: $$(subst $(BIN_SUFFIX),,$(SRC_PATH)/%.cpp)
	$(info Compiling $(<))
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	$(info Cleaning $(<))
	@rm -f $(OUT_EXE_PATH)/*.a
	@find $(OUT_OBJ_PATH) -type f \( -name *.o -o -name *.d \) -exec rm -f {} \;
