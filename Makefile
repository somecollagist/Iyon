OS := iyon

SRC := ./src
BIN := ./bin
ISO := ./iso
BINLOC := $(BIN)/kernel.elf

CC := gcc
ASMC := nasm
LD := ld

CFLG := -Wall					\
		-g						\
		-fpic					\
		-ffreestanding			\
		-fno-stack-protector	\
		-nostdinc				\
		-nostdlib				\
		-mno-red-zone			\
		-Ibootboot/dist			\
		-Isrc
CSRC := $(shell find $(SRC) -name "*.c")
CTAR := $(patsubst $(SRC)/%,$(BIN)/%,$(patsubst %.c,%.o,$(CSRC)))
CIDR := $(shell dirname $(shell echo $(CSRC) | tr ' ' '\n' | sort -u | xargs))
CINC := $(addprefix -I ,$(CIDR))

ASMFLG := -f elf64
ASMSRC := $(shell find $(SRC) -name "*.asm")
ASMTAR := $(patsubst $(SRC)/%,$(BIN)/%,$(patsubst %.asm,%.o,$(ASMSRC)))
ASMIDR := $(shell dirname $(shell echo $(ASMSRC) | tr ' ' '\n' | sort -u | xargs))
ASMINC := $(addprefix -i ,$(ASMIDR))

LDFLG :=	-nostdlib		\
			-n				\
			-T linker.ld

STRIPFLG :=	-s -K mmio -K fb -K bootboot -K environment -K initstack

all: prebuild build run clean

prebuild:
	@clear
	@echo " -- Prebuild -- "
	@echo "Wiping $(BIN) directory..."
	@rm -rf $(BIN)
	@mkdir $(BIN)
	@echo " -- Prebuild Complete -- "

build: $(ASMTAR) $(CTAR)
	@echo " -- Build -- "
	@echo "Linking object files to $(BINLOC)..."
	@$(LD) -r -b binary -o $(BIN)/font.o $(SRC)/font.psf
	@$(LD) $(LDFLG) $^ $(BIN)/font.o -o $(BINLOC)
	@echo "Linking complete"
	@echo "Generating disassembly..."
	# @strip $(STRIPFLG) $(BINLOC)
	@rm -rf disassembly.txt
	@readelf -hls $(BINLOC) >> disassembly.txt
	@objdump -d $(BINLOC) >> disassembly.txt
	@echo "Stripped and disassembled"
	@echo "Building disk image..."
	@mkdir -p $(ISO)/sys
	@cp $(BINLOC) $(ISO)/sys/core
	@./bootboot/mkbootimg/mkbootimg iyon.json iyon.img
	@echo "Disk image built"
	@echo " -- Build Complete -- "

$(BIN)/%.o: $(SRC)/%.asm
	@echo "Assembling $<..."
	@mkdir -p $(shell dirname $@)
	@$(ASMC) $(ASMFLG) $< -o $@ $(ASMINC)

$(BIN)/%.o: $(SRC)/%.c
	@echo "Compiling $<..."
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLG) -c $< -o $@ $(CINC)

run:
	@echo " -- Run -- "
	@bochs -q
	@echo " -- Run Complete -- "

clean:
	@echo " -- Clean --"
	@rm -rf $(BINLOC)
	@echo " -- Clean Complete -- "