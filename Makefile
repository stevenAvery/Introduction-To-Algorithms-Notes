
CC           = clang++
CFLAGS       = -std=c++11
SOURCE_DIR   = src
SOURCES      = $(wildcard $(SOURCE_DIR)/*.cpp)
OUTDIR       = build
OBJECTS      = $(addprefix $(OUTDIR)/,$(notdir $(SOURCES:.cpp=.out)))
SORTING      = sorting
MAX_SUBARRAY = maximumSubarray

.PHONY: all clean maximumSubarray sorting

# make sure the output directory is built before the objects
$(OBJECTS): | $(OUTDIR)

$(OUTDIR):
	@mkdir -p $(OUTDIR)

# compile objects
$(OUTDIR)/%.out: $(SOURCE_DIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ $<

# compile everything
all: $(OBJECTS)

# remove all objects
clean:
	$(RM) $(OBJECTS)

# run maximum subarray algorithms
maximumSubarray: | $(OUTDIR)
	$(CC) $(CFLAGS) -o $(OUTDIR)/$(MAX_SUBARRAY).out $(SOURCE_DIR)/$(MAX_SUBARRAY).cpp
	./$(OUTDIR)/$(MAX_SUBARRAY).out

# run sorting algorithms
sorting: | $(OUTDIR)
	$(CC) $(CFLAGS) -o $(OUTDIR)/$(SORTING).out $(SOURCE_DIR)/$(SORTING).cpp
	./$(OUTDIR)/$(SORTING).out
