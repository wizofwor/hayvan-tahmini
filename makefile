
CC 	= cl65
AS  = ca65
CFLAGS  = -Oirs -t $(CC65_TARGET) --create-dep 
LDFLAGS = -Oirs -t $(CC65_TARGET) -m $(PROGRAM).map

VICE = /Applications/Vice


#######################################

CC65_TARGET = c64
SOURCES = main.c functions.c
PROGRAM = compiled.prg

.PHONY: clean run-compiled
.SUFFIXES:

all: $(PROGRAM) run-compiled	

$(PROGRAM): $(SOURCES:.c=.o)
	$(CC) $(LDFLAGS) -o $@ $^
	@echo ...compiled \n

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

run-compiled:
ifneq (,$(wildcard disk.d64))
	# D64 file found
	@$(VICE)/tools/c1541 disk.d64 -delete program -write $(PROGRAM) program \
		&& echo  ...disk image updated || echo  ...disk image update failed
else
	# D64 file not found
	@$(VICE)/tools/c1541 -format disk,8 d64 disk.d64 -write $(PROGRAM) program \
		&& echo  ...disk image created || echo  ...disk image creation failed
endif
	@open $(VICE)/x64.app disk.d64 && echo  ...done || echo  ...failed

clean:
	$(RM) $(SOURCES:.c=.o) $(SOURCES:<.c=.d) $(PROGRAM) $(PROGRAM).map
