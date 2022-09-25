#+---------------------------------------------------------------------------
#
#  Copyright (c) 2010 Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
#
#  Modified by the author of this repository
#
#  File:       makefile
#
#  Contents:   makefile to build ADuc706x ARM software with gcc
#
#----------------------------------------------------------------------------

# program name
TARGET      = blinky-make
TOOL        = arm-none-eabi-

# compile options 
MCU         = arm7tdmi
CHIP        = ADUC7060
OPTIMIZE    = -O2

# common part
BASE        = .
OUTBASE     = output
CC          = $(TOOL)gcc
LD          = $(TOOL)g++
AS          = $(CC) -x assembler-with-cpp
OBJCOPY     = $(TOOL)objcopy
OBJDUMP     = $(TOOL)objdump
SIZE        = $(TOOL)size -d
RM          = rm -f
MD          = mkdir -p

# dirs
SRCDIR      = $(BASE)/src
INCDIR      = $(BASE)/inc
OBJDIR      = $(OUTBASE)/obj
LSTDIR      = $(OUTBASE)/lst
EXEDIR      = $(OUTBASE)/exe

# files
ELF         = $(EXEDIR)/$(TARGET).elf
MAP         = $(LSTDIR)/$(TARGET).map
HEX         = $(EXEDIR)/$(TARGET).hex
LSS         = $(LSTDIR)/$(TARGET).lss

# linker script
LD_SCRIPT   = $(SRCDIR)/ADUC706x-ROM.ld

# files in directories
DIRS       := $(SRCDIR)
INCDIRS    := $(INCDIR)
INCS       := $(patsubst %, -I "%", $(INCDIRS))
SRCS       := $(wildcard $(addsuffix /*.c, $(DIRS)) $(wildcard $(addsuffix /*.S, $(DIRS))))
OBJS       := $(notdir $(SRCS) )
OBJS       := $(OBJS:.c=.o)
OBJS       := $(OBJS:.S=.o)
OBJS       := $(OBJS:.s=.o)
OBJS       := $(patsubst %, $(OBJDIR)/%, $(OBJS))

# flags
FLAGS       = -mcpu=$(MCU)
FLAGS      += -g -gdwarf-2
FLAGS      += $(INCS)
FLAGS      += -MD
FLAGS      += -D$(CHIP)
FLAGS      += -Wa,-adhlns=$(addprefix $(LSTDIR)/, $(notdir $(addsuffix .lst, $(basename $<))))

AFLAGS      = $(FLAGS)

CFLAGS      = $(FLAGS)
CFLAGS     += $(OPTIMIZE)
CFLAGS     += -std=gnu99
CFLAGS     += -ffunction-sections -fdata-sections
CFLAGS     += -Wall -Wextra
CFLAGS     += -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls
CFLAGS     += -Wshadow -Wcast-qual -Wcast-align -Wnested-externs -pedantic

LD_FLAGS    = -mcpu=$(MCU)
LD_FLAGS   += -nostartfiles 
LD_FLAGS   += -Wl,-Map="$(MAP)",--cref
LD_FLAGS   += -fno-exceptions -fno-rtti	
LD_FLAGS   += -Wl,--gc-sections
LD_FLAGS   += -T$(LD_SCRIPT)
LD_FLAGS   += -specs=nosys.specs

.PHONY: all dirs clean size dump

all: dirs $(ELF) $(HEX) $(LSS) size

$(LSS): $(ELF) makefile
	@echo --- making asm-lst...
	$(OBJDUMP) -dC $(ELF) > $(LSS)

size: $(ELF)
	$(SIZE) $(ELF)
	@echo "Errors: none"

$(ELF):	$(OBJS) makefile
	@echo --- linking...
	$(LD) $(OBJS) $(LD_FLAGS) -o $(ELF)

$(HEX): $(ELF)
	@echo --- creating hex...
	$(OBJCOPY) -O ihex $(ELF) $(HEX)

VPATH := $(DIRS)

$(OBJDIR)/%.o: %.c makefile
	@echo --- compiling $<...
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o: %.S makefile
	@echo --- assembling $<...
	$(AS) -c $(AFLAGS) -o $@ $<

dirs: $(OBJDIR) $(LSTDIR) $(EXEDIR)

$(OBJDIR):
	-@$(MD) $(OBJDIR)

$(LSTDIR):
	-@$(MD) $(LSTDIR)

$(EXEDIR):
	-@$(MD) $(EXEDIR)

clean:
	@echo --- cleaning up...
	-@$(RM) -rf $(OUTBASE)
