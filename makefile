# Compiler
CC := clang

# Directories
SRCDIR := src
INCDIR := $(SRCDIR)/headers
BUILDDIR := dist
DEBUGDIR := $(BUILDDIR)/debug
RELEASEDIR := $(BUILDDIR)/release

# Flags
CFLAGS := -Wall -Wextra -WPedantic -I$(INCDIR)
DEBUGFLAGS := -g -fsanitize=undefined
RELEASEFLAGS := -O3

# Sanitizers (choose one)
# DEBUGFLAGS += -fsanitize=address
# DEBUGFLAGS += -fsanitize=memory
# DEBUGFLAGS += -fsanitize=dataflow
# DEBUGFLAGS += -fsanitize=leak

# Source files
SRCS := $(shell find $(SRCDIR) -name '*.c')

# Object files
OBJS := $(SRCS:.c=.o)

# Executable name
EXEC := mollybot

# Targets
.PHONY: all clean debug release clang-tidy

all: clean debug

debug-exe: clean debug

release-exe: clean release execute-release

execute:
	$(DEBUGDIR)/$(EXEC)

execute-release:
	$(RELEASEDIR)/$(EXEC)

debug: $(DEBUGDIR)/$(EXEC)

release: $(RELEASEDIR)/$(EXEC)

$(DEBUGDIR)/$(EXEC): $(OBJS)
	mkdir -p $(DEBUGDIR)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $^ -o $@

$(RELEASEDIR)/$(EXEC): $(OBJS)
	mkdir -p $(RELEASEDIR)
	$(CC) $(CFLAGS) $(RELEASEFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clang-tidy:
	bear make
	clang-tidy $(SRCS) --checks=-*,clang-analyzer-*,cert-* --header-filter=$(INCDIR)

clean:
	rm -rf $(BUILDDIR)

lint: clang-tidy