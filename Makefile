TARGET = pak unpak

include make/build.gmk

CFLAGS_heap.c = -DHEAP_ORDER="<"

## Test
TESTFILE = $(BUILDDIR)/test/testfile
$(TESTFILE): $(SRCFILES)
	@$(MKDIR) $(dir $@)
	@$(CAT) $^ > $@

test: $(TARGET) $(TESTFILE)
	@$(CP) $(TESTFILE) $(TESTFILE).orig
	@./pak $(TESTFILE)
	@./unpak $(TESTFILE).pak
	@$(DIFF) $(TESTFILE).orig $(TESTFILE) && $(ECHO) SUCCESS

### Dependencies

## Link dependencies are all object files for the executable
$(BUILDDIR)/pak: $(filter-out %/unpak.o %/decode.o,$(OBJFILES))
$(BUILDDIR)/unpak: $(filter-out %/pak.o %/encode.o,$(OBJFILES))

## The first dependency for object files must be their source file
#TODO: Add dependencies for included .h files
$(OBJDIR)/bitstring.o: $(SRC)/bitstring.c
$(OBJDIR)/decode.o: $(SRC)/decode.c
$(OBJDIR)/encode.o: $(SRC)/encode.c
$(OBJDIR)/heap.o: $(SRC)/heap.c
$(OBJDIR)/hist.o: $(SRC)/hist.c
$(OBJDIR)/hufftree.o: $(SRC)/hufftree.c
$(OBJDIR)/pak.o: $(SRC)/pak.c
$(OBJDIR)/unpak.o: $(SRC)/unpak.c
