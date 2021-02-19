# Include the nanopb provided Makefile rules
include nanopb.mk

NANOPB_DIR = ../../nanopb

PROTOFILE = simple

# Compiler flags to enable all warnings & debug info
CFLAGS = -Wall -Werror -g -O0
CFLAGS += "-I$(NANOPB_DIR)"

# C source code files that are required
CSRC  = $(PROTOFILE).c                   # The main program
CSRC += $(PROTOFILE).pb.c                # The compiled protocol definition
CSRC += $(NANOPB_DIR)/pb_encode.c  # The nanopb encoder
CSRC += $(NANOPB_DIR)/pb_decode.c  # The nanopb decoder
CSRC += $(NANOPB_DIR)/pb_common.c  # The nanopb common parts

# Build rule for the protocol
simple.pb.c: simple.proto
	$(PROTOC) $(PROTOC_OPTS) --nanopb_out=. $(PROTOFILE).proto
	mv $(PROTOFILE).pb.h ../../include/serial_pb/

../../include/serial_pb/$(PROTOFILE).pb.h: $(PROTOFILE.pb.c)