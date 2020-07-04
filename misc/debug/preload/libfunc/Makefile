#
# FILE		: Makefile
#
# Description	: A simple makefile to demonstrate the use of LD_PRELOAD
# 	          trick
#

RED   :=\033[0;31m
GRN   :=\033[0;32m
NCC   :=\033[0m

DIR   := ${CURDIR}
C_APP := $(wildcard app/*.c)
C_LIB := $(wildcard lib/*.c)
S_LIB := custom_lib.so
S_APP := test

all: build

build: $(S_LIB) $(S_APP)
	@echo "$(RED)\c"
	@echo "Build Complete!"
	@echo "$(NCC)\c"

$(S_LIB): $(C_LIB)
	@echo "$(RED)\c"
	gcc -shared -fPIC $< -o $@ -ldl
	@echo "$(NCC)\c"

$(S_APP): $(C_APP)
	@echo "$(RED)\c"
	gcc $< -o $@
	@echo "$(NCC)\c"

run: $(S_LIB) $(S_APP)
	@echo "$(GRN)\c"
	LD_PRELOAD=$(DIR)/$(S_LIB) ./$(S_APP)
	@echo "$(NCC)\c"

clean:
	@echo "$(RED)\c"
	rm -f $(S_LIB) $(S_APP)
	@echo "$(NCC)\c"
