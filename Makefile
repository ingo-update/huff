# Makefile for the huffman compression programs

CC = gcc -c
LD = gcc
RM = rm -rf
ECHO = echo
MKDIR = mkdir -p
CP = cp
DIFF = diff

CFLAGS = -Wall -Werror
LDFLAGS = -Wall -Werror
LDLIBS =

OPT_CFLAGS = -O4
DBG_CFLAGS = -g

CFLAGS_heap.c = -DHEAP_ORDER="<"

TARGET = pak unpak

TOPDIR = $(shell pwd)
SRC = $(TOPDIR)/src
BUILDDIR = $(TOPDIR)/build
OBJDIR = $(BUILDDIR)/objs

OBJFILES = $(sort $(patsubst $(SRC)/%.c,$(OBJDIR)/%.o,$(wildcard $(SRC)/*.c)))

PAK_OBJS = $(filter-out %/unpak.o %/decode.o,$(OBJFILES))
UNPAK_OBJS = $(filter-out %/pak.o %/encode.o,$(OBJFILES))

TESTFILE = $(BUILDDIR)/test/testfile

default: $(TARGET)
$(TARGET): $(addprefix $(BUILDDIR)/,$(TARGET))
	@$(CP) $^ $(TOPDIR)

OBJ_CMD = $(CC) -I$(SRC) $(CFLAGS) $(OPT_CFLAGS) $(DBG_CFLAGS) $(CFLAGS_$(notdir $<)) $< -o $@
$(OBJFILES):
	@$(MKDIR) $(dir $@)
	@$(ECHO) Compiling $(notdir $<)
	@$(ECHO) '$(OBJ_CMD)' > $@.cmdline
	@$(OBJ_CMD) 2> $@.log

TARGET_CMD = $(LD) -o $@ $(LDFLAGS) $^ $(LDLIBS)
$(addprefix $(BUILDDIR)/,$(TARGET)):
	@$(MKDIR) $(dir $@)
	@$(ECHO) Linking $(notdir $@)
	@$(ECHO) '$(TARGET_CMD)' > $@.cmdline
	@$(TARGET_CMD) 2> $@.log

clean:
	@$(RM) $(BUILDDIR) $(TARGET)

sweep: clean
	@$(RM) $(SRC)/*~ *~

test: $(TARGET)
	@$(MKDIR) $(dir $(TESTFILE))
	@$(CP) Makefile $(TESTFILE)
	@./pak $(TESTFILE)
	@./unpak $(TESTFILE).pak
	@$(DIFF) Makefile $(TESTFILE)

## Dependencies
$(BUILDDIR)/pak: $(PAK_OBJS)
$(BUILDDIR)/unpak: $(UNPAK_OBJS)

$(OBJDIR)/bitstring.o: $(SRC)/bitstring.c
$(OBJDIR)/decode.o: $(SRC)/decode.c
$(OBJDIR)/encode.o: $(SRC)/encode.c
$(OBJDIR)/heap.o: $(SRC)/heap.c
$(OBJDIR)/hist.o: $(SRC)/hist.c
$(OBJDIR)/hufftree.o: $(SRC)/hufftree.c
$(OBJDIR)/pak.o: $(SRC)/pak.c
$(OBJDIR)/unpak.o: $(SRC)/unpak.c
