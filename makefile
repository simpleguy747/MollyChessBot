# Compiler
CC := gcc

# Directories
SRCDIR := src
INCDIR := src/headers
BUILDDIR := dist
DEBUGDIR := $(BUILDDIR)/debug
RELEASEDIR := $(BUILDDIR)/release

# Flags
CFLAGS := -Wall -I$(INCDIR)
DEBUGFLAGS := -g
RELEASEFLAGS := -O2

# Source files
SRCS := $(wildcard $(SRCDIR)/*.c)

# Executable name
EXEC := hanselbot

# Targets
.PHONY: all clean

all: clean debug

debug-exe: clean debug execute

execute:
	$(DEBUGDIR)/$(EXEC)

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

