# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := mantra
DEFS_Debug := \
	'-DNODE_GYP_MODULE_NAME=mantra' \
	'-DUSING_UV_SHARED=1' \
	'-DUSING_V8_SHARED=1' \
	'-DV8_DEPRECATION_WARNINGS=1' \
	'-DV8_DEPRECATION_WARNINGS' \
	'-DV8_IMMINENT_DEPRECATION_WARNINGS' \
	'-D_GLIBCXX_USE_CXX11_ABI=1' \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-D__STDC_FORMAT_MACROS' \
	'-DOPENSSL_NO_PINSHARED' \
	'-DOPENSSL_THREADS' \
	'-DBUILDING_NODE_EXTENSION' \
	'-DDEBUG' \
	'-D_DEBUG' \
	'-DV8_ENABLE_CHECKS'

# Flags passed to all source files.
CFLAGS_Debug := \
	-fPIC \
	-pthread \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-m64 \
	-g \
	-O0

# Flags passed to only C files.
CFLAGS_C_Debug :=

# Flags passed to only C++ files.
CFLAGS_CC_Debug := \
	-fno-rtti \
	-std=gnu++17

INCS_Debug := \
	-I/root/.cache/node-gyp/20.10.0/include/node \
	-I/root/.cache/node-gyp/20.10.0/src \
	-I/root/.cache/node-gyp/20.10.0/deps/openssl/config \
	-I/root/.cache/node-gyp/20.10.0/deps/openssl/openssl/include \
	-I/root/.cache/node-gyp/20.10.0/deps/uv/include \
	-I/root/.cache/node-gyp/20.10.0/deps/zlib \
	-I/root/.cache/node-gyp/20.10.0/deps/v8/include \
	-I/app/node_modules/node-addon-api

DEFS_Release := \
	'-DNODE_GYP_MODULE_NAME=mantra' \
	'-DUSING_UV_SHARED=1' \
	'-DUSING_V8_SHARED=1' \
	'-DV8_DEPRECATION_WARNINGS=1' \
	'-DV8_DEPRECATION_WARNINGS' \
	'-DV8_IMMINENT_DEPRECATION_WARNINGS' \
	'-D_GLIBCXX_USE_CXX11_ABI=1' \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-D__STDC_FORMAT_MACROS' \
	'-DOPENSSL_NO_PINSHARED' \
	'-DOPENSSL_THREADS' \
	'-DBUILDING_NODE_EXTENSION'

# Flags passed to all source files.
CFLAGS_Release := \
	-fPIC \
	-pthread \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-m64 \
	-O3 \
	-fno-omit-frame-pointer

# Flags passed to only C files.
CFLAGS_C_Release :=

# Flags passed to only C++ files.
CFLAGS_CC_Release := \
	-fno-rtti \
	-std=gnu++17

INCS_Release := \
	-I/root/.cache/node-gyp/20.10.0/include/node \
	-I/root/.cache/node-gyp/20.10.0/src \
	-I/root/.cache/node-gyp/20.10.0/deps/openssl/config \
	-I/root/.cache/node-gyp/20.10.0/deps/openssl/openssl/include \
	-I/root/.cache/node-gyp/20.10.0/deps/uv/include \
	-I/root/.cache/node-gyp/20.10.0/deps/zlib \
	-I/root/.cache/node-gyp/20.10.0/deps/v8/include \
	-I/app/node_modules/node-addon-api

OBJS := \
	$(obj).target/$(TARGET)/mantra.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# Make sure our dependencies are built before any of us.
$(OBJS): | $(builddir)/nothing.a $(obj).target/node_modules/node-addon-api/nothing.a

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# End of this set of suffix rules
### Rules for final target.
LDFLAGS_Debug := \
	-pthread \
	-rdynamic \
	-m64

LDFLAGS_Release := \
	-pthread \
	-rdynamic \
	-m64

LIBS := \
	-liengine_ansi_iso \
	-lMFS100V9022

$(obj).target/mantra.node: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(obj).target/mantra.node: LIBS := $(LIBS)
$(obj).target/mantra.node: TOOLSET := $(TOOLSET)
$(obj).target/mantra.node: $(OBJS) $(obj).target/node_modules/node-addon-api/nothing.a FORCE_DO_CMD
	$(call do_cmd,solink_module)

all_deps += $(obj).target/mantra.node
# Add target alias
.PHONY: mantra
mantra: $(builddir)/mantra.node

# Copy this to the executable output path.
$(builddir)/mantra.node: TOOLSET := $(TOOLSET)
$(builddir)/mantra.node: $(obj).target/mantra.node FORCE_DO_CMD
	$(call do_cmd,copy)

all_deps += $(builddir)/mantra.node
# Short alias for building this executable.
.PHONY: mantra.node
mantra.node: $(obj).target/mantra.node $(builddir)/mantra.node

# Add executable to "all" target.
.PHONY: all
all: $(builddir)/mantra.node
