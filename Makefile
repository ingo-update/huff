# Makefile for the huffman compression programs

### Definitions

## Common tools to be used
CC = gcc -c
LD = gcc
RM = rm -rf
ECHO = echo
MKDIR = mkdir -p
CP = cp
DIFF = diff

## General flags and libs
CFLAGS = -Wall -Werror
LDFLAGS = -Wall -Werror
LDLIBS =

## Flags for optimization and debugging
OPT_CFLAGS = -O4
DBG_CFLAGS = -g

## Special compile flags for special source files
CFLAGS_heap.c = -DHEAP_ORDER="<"

## Build commands
COMPILE_CMD = $(CC) -I$(SRC) $(CFLAGS) $(OPT_CFLAGS) $(DBG_CFLAGS) $(CFLAGS_$(notdir $<)) $< -o $@
LINK_CMD = $(LD) -o $@ $(LDFLAGS) $^ $(LDLIBS)

## Directories
TOPDIR = $(shell pwd)
SRC = $(TOPDIR)/src
BUILDDIR = $(TOPDIR)/build
OBJDIR = $(BUILDDIR)/objs

## Object files
OBJFILES = $(sort $(patsubst $(SRC)/%.c,$(OBJDIR)/%.o,$(wildcard $(SRC)/*.c)))

## Default target(s)
TARGET = pak unpak

TESTFILE = $(BUILDDIR)/test/testfile

PAK_OBJS = $(filter-out %/unpak.o %/decode.o,$(OBJFILES))
UNPAK_OBJS = $(filter-out %/pak.o %/encode.o,$(OBJFILES))

### Rules

default: $(TARGET)

## Build the target and copy it to where it is expected
$(TARGET): $(addprefix $(BUILDDIR)/,$(TARGET))
	@$(CP) $^ $(TOPDIR)

## Compile object files
$(OBJFILES):
	@$(MKDIR) $(dir $@)
	@$(ECHO) Compiling $(notdir $<)
	@$(ECHO) '$(COMPILE_CMD)' > $@.cmdline
	@$(COMPILE_CMD) 2> $@.log
	@[ -s $@.log ] || $(RM) $@.log

## Link target(s)
$(addprefix $(BUILDDIR)/,$(TARGET)):
	@$(MKDIR) $(dir $@)
	@$(ECHO) Linking $(notdir $@)
	@$(ECHO) '$(LINK_CMD)' > $@.cmdline
	@$(LINK_CMD) 2> $@.log
	@[ -s $@.log ] || $(RM) $@.log

## Remove artifacts
clean:
	@$(RM) $(BUILDDIR) $(TARGET)

## Also remove editor backup files
sweep: clean
	@$(RM) $(SRC)/*~ *~

## Test
test: $(TARGET)
	@$(MKDIR) $(dir $(TESTFILE))
	@$(CP) Makefile $(TESTFILE)
	@./pak $(TESTFILE)
	@./unpak $(TESTFILE).pak
	@$(DIFF) Makefile $(TESTFILE) && $(ECHO) SUCCESS

### Dependencies

## Link dependencies are all object files for the executable
$(BUILDDIR)/pak: $(PAK_OBJS)
$(BUILDDIR)/unpak: $(UNPAK_OBJS)

## The first dependency for object files must be their source file
$(OBJDIR)/bitstring.o: $(SRC)/bitstring.c
$(OBJDIR)/decode.o: $(SRC)/decode.c
$(OBJDIR)/encode.o: $(SRC)/encode.c
$(OBJDIR)/heap.o: $(SRC)/heap.c
$(OBJDIR)/hist.o: $(SRC)/hist.c
$(OBJDIR)/hufftree.o: $(SRC)/hufftree.c
$(OBJDIR)/pak.o: $(SRC)/pak.c
$(OBJDIR)/unpak.o: $(SRC)/unpak.c
