#----------------------------------------------------------------------------
#
#  Copyright (c) 2010 Anton Gusev aka AHTOXA
#
#  Makefile modified by the author of this repository.
#
#  File:       makefile
#
#  Contents:   makefile to build ADuc706x ARM software with gcc
#
#----------------------------------------------------------------------------

SHELL       = /bin/bash

# program name
TARGET      = card-ecg
TOOL        = arm-none-eabi-

# compile options
MCU         = arm7tdmi
CHIP        = ADUC7060
OPTIMIZE    = -O2

# common part
BASE        = .
OUTDIR      = output
CC          = $(TOOL)gcc
LD          = $(TOOL)gcc
AS          = $(CC) -x assembler-with-cpp
OBJCOPY     = $(TOOL)objcopy
OBJDUMP     = $(TOOL)objdump
SIZE        = $(TOOL)size -d
RM          = rm -rf
MD          = mkdir -p -v

# dirs
SRCDIR      = $(BASE)/src
INCDIR      = $(BASE)/inc
COMDIR      = $(BASE)/common
TPARTYDIR   = $(BASE)/third-party
OBJDIR      = $(OUTDIR)/obj
LSTDIR      = $(OUTDIR)/lst
EXEDIR      = $(OUTDIR)/exe

# files
ELF         = $(EXEDIR)/$(TARGET).elf
MAP         = $(LSTDIR)/$(TARGET).map
HEX         = $(EXEDIR)/$(TARGET).hex
LSS         = $(LSTDIR)/$(TARGET).lss

# linker script
LD_SCRIPT   = $(COMDIR)/aduc706x_rom.ld

# files in directories
DIRS       := $(SRCDIR)
DIRS       += $(COMDIR)
DIRS       += $(TPARTYDIR)/printf
INCDIRS    := $(INCDIR)
INCDIRS    += $(COMDIR)
INCDIRS    += $(TPARTYDIR)
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

VPATH      := $(DIRS)

.PHONY: all dirs clean size

all: dirs $(ELF) $(HEX) $(LSS) size

size: $(ELF)
	@echo --- running size tool...
	$(SIZE) $(ELF)

$(LSS): $(ELF)
	@echo --- making asm-lst...
	$(OBJDUMP) -dC $(ELF) > $(LSS)

$(ELF):	$(OBJS)
	@echo --- linking...
	$(LD) $(OBJS) $(LD_FLAGS) -o $(ELF)

$(HEX): $(ELF)
	@echo --- creating hex...
	$(OBJCOPY) -O ihex $(ELF) $(HEX)

$(OBJDIR)/%.o: %.c
	@echo --- compiling $<...
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o: %.S
	@echo --- assembling $<...
	$(AS) -c $(AFLAGS) -o $@ $<

dirs:
	@echo --- creating directories...
	-@$(MD) "$(OUTDIR)"
	-@$(MD) "$(OBJDIR)"
	-@$(MD) "$(LSTDIR)"
	-@$(MD) "$(EXEDIR)"

clean:
	@echo --- cleaning up output files...
	-$(RM) $(OUTDIR)
