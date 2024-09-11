# Compiler
CC := clang

# Directories
SRCDIR := src
INCDIR := src/headers
BUILDDIR := dist
DEBUGDIR := $(BUILDDIR)/debug
RELEASEDIR := $(BUILDDIR)/release

# Flags
CFLAGS := -Wall -Wextra -I $(INCDIR)
DEBUGFLAGS := -g -fsanitize=undefined
# DEBUGFLAGS := -g -fsanitize=address
# DEBUGFLAGS := -g -fsanitize=memory
# DEBUGFLAGS := -g -fsanitize=dataflow
# DEBUGFLAGS := -g -fsanitize=leak
RELEASEFLAGS := -O3
# Source files
SRCS := $(shell find $(SRCDIR) -name '*.c')

# Executable name
EXEC := mollybot

# Targets
.PHONY: all clean debug release

all: clean debug

debug-exe: clean debug execute

release-exe: clean release execute-release

execute:
	$(DEBUGDIR)/$(EXEC)

execute-release:
	$(RELEASEDIR)/$(EXEC)

debug: $(DEBUGDIR)/$(EXEC)

release: $(RELEASEDIR)/$(EXEC)

$(DEBUGDIR)/$(EXEC): $(SRCS)
	mkdir -p $(DEBUGDIR)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $^ -o $@

$(RELEASEDIR)/$(EXEC): $(SRCS)
	mkdir -p $(RELEASEDIR)
	$(CC) $(CFLAGS) $(RELEASEFLAGS) $^ -o $@

clean:
	rm -rf $(BUILDDIR)