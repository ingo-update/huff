### Makefile for huff ###

PROJECT = huff
TARGET = pak unpak

ifndef MAKEDIR
  MAKEDIR = ../make
endif

SPEC = $(MAKEDIR)/spec.gmk
TESTOBJS = $(TESTDIR)/heap.o

include $(MAKEDIR)/main.gmk

CFLAGS_heap.o = -DCUSTOM_HEAP_ELEMENT -DOMIT_HEAP_SORT
CFLAGS_hufftree.o = -DCUSTOM_HEAP_ELEMENT

## Test

TESTFILE = $(BUILDDIR)/test/testfile
$(TESTFILE): $(SRCFILES)
	@$(ECHO) Creating test file $@
	@$(MKDIR) $(dir $@)
	@$(CAT) $^ > $@

test: $(TARGET) $(TESTFILE)
	@$(ECHO) Testing target $(TARGET)
	@$(CP) $(TESTFILE) $(TESTFILE).orig
	@./pak -b $(TESTFILE) > $(BUILDDIR)/test/pak.hist
	@./unpak $(TESTFILE).pak
	@$(DIFF) $(TESTFILE).orig $(TESTFILE) && $(ECHO) SUCCESS
	@$(DIFF) $(TESTFILE).orig $(TESTFILE) || $(ECHO) FAILURE

### Dependencies

## Link dependencies are all object files for the executable
$(BUILDDIR)/pak: $(filter-out %/unpak.o %/decode.o,$(OBJFILES))
$(BUILDDIR)/unpak: $(filter-out %/pak.o %/encode.o,$(OBJFILES))

## The first dependency for object files must be their source file
$(OBJDIR)/bitstring.o: $(SRC)/bitstring.c $(SRC)/bitstring.h
$(OBJDIR)/decode.o: $(SRC)/decode.c $(SRC)/decode.h $(SRC)/hufftree.h
$(OBJDIR)/encode.o: $(SRC)/encode.c $(SRC)/encode.h $(SRC)/hufftree.h $(SRC)/bitstring.h
$(OBJDIR)/heap.o: $(SRC)/heap.c $(SRC)/heap.h
$(OBJDIR)/hist.o: $(SRC)/hist.c $(SRC)/hist.h
$(OBJDIR)/hufftree.o: $(SRC)/hufftree.c $(SRC)/hufftree.h $(SRC)/bitstring.h $(SRC)/heap.h
$(OBJDIR)/pak.o: $(SRC)/pak.c $(SRC)/hist.h $(SRC)/encode.h
$(OBJDIR)/unpak.o: $(SRC)/unpak.c $(SRC)/hist.h $(SRC)/decode.h

$(TESTDIR)/test-bitstring.o: $(TOPDIR)/test/test-bitstring.c $(SRC)/bitstring.c $(SRC)/bitstring.h
$(TESTDIR)/test-heap.o: $(TOPDIR)/test/test-heap.c $(SRC)/heap.c $(SRC)/heap.h
$(TESTDIR)/test-hufftree.o: $(TOPDIR)/test/test-hufftree.c $(SRC)/hufftree.c $(SRC)/hufftree.h
$(TESTDIR)/test-hist.o: $(TOPDIR)/test/test-hist.c

$(TESTDIR)/heap.o: $(SRC)/heap.c $(SRC)/heap.h

$(TESTDIR)/test-bitstring: $(TESTDIR)/test-bitstring.o $(OBJDIR)/bitstring.o
$(TESTDIR)/test-heap: $(TESTDIR)/test-heap.o $(TESTDIR)/heap.o
$(TESTDIR)/test-hufftree: $(TESTDIR)/test-hufftree.o $(OBJDIR)/hufftree.o $(OBJDIR)/bitstring.o $(TESTDIR)/heap.o
$(TESTDIR)/test-hist: $(TESTDIR)/test-hist.o $(OBJDIR)/hist.o
