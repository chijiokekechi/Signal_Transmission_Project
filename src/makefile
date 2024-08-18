## Force the use of Bash ##
## Set appropriate error traceback piping for debug ##
## Delete all generated intermediate files automatically on fail ##
SHELL := bash
.ONESHELL:
.SHELLFLAGS := -eu -o pipefail -c
.DELETE_ON_ERROR:

## MAKEFLAGS are called as command line arguments when running make  ##
#
MAKEFLAGS += --warn-undefined-variables
# Force make to only do explicit things and not make assumptions about what you want
MAKEFLAGS += --no-builtin-rules

## Set tabs requirement to '>' instead for the purposes of sanity ##
ifeq ($(origin .RECIPEPREFIX), undefined)
  $(error This Make does not support .RECIPEPREFIX. Please use GNU Make 4.0 or later)
endif
.RECIPEPREFIX = >

## Set Default Target ##
.DEFAULT_GOAL := default



##################################################

CXX = g++
CFLAGS = 
CPPFLAGS = -Wall

##################################################

CHECK_SYNTAX = -fsyntax-only
LIMIT_ERROS = -fmax-errors=5
SUPRESS_WARNINGS = -w
WARN_TO_ERROR = -Werror
BASIC_ISO_STANDARD = -Wpedantic

##################################################
# Debug Sets
BASIC_DEBUG_FLAGS = -g -Wall -Wextra -Wunused -O0 

DEBUG_MACROS = -Wundef -Wexpansion-to-defined -Wunused-macros
DEBUG_LOGICAL = -Wlogical-not-parentheses
DEBUG_ARRAY = -Wchar-subscripts -Wmemset-elt-size
DEBUG_MATH = -Wdouble-promotion -Wsign-compare 
DEBUG_DECLARATION = -Wuninitialized -W-implicit-int -W-implicit-function-declaration -Wmissing-braces -Wno-invalid-memory-model
DEBUG_STRUCTURE = -Wmisleading-indentation -Wcomments
DEBUG_TYPES = -Wconversion -Wsign-conversion

REMOVE_REDUNDANT = -Wunused-variable -Wunused-but-set-variable -Wunused-const-variable -Wunused-value -Wunused-function -Wunused-local-typedefs -Wunused-parameter -Wunused-result -Wunused-label
DEBUG_C = -Wpointer-sign -Wmissing-prototypes
DEBUG_CPP = -Wmissing-declarations
DEBUG_UNLIKELY = -Wwrite-strings -Wclobbered

DEBUG_FLAGS = $(BASIC_DEBUG_FLAGS) $(DEBUG_DECLARATION)
##################################################
# Compile Set
COMPILE_FLAGS = -fsyntax-only

##################################################
# Live Set
LIVE_FLAGS = -w -O3
##################################################
# Flags to build with
CXXFLAGS = $(LIVE_FLAGS)



####################################################################################################
### Targets and Rules ###

# Default target for unspecified call
default : all

ALL_TARGETS = TX_PIPE_INTERFACE RX_PIPE_INTERFACE AWGN BPSK PSK_SYMBOL_DETECTOR AGC Driver InputGeneration SCALER_1 SCALER_2 PLL FIR CLARK SYMBOL_MAPPER FIR_MF BPSK_ADD_FRAME BPSK_FRAME_SYNC

all : TX_PIPE_INTERFACE RX_PIPE_INTERFACE AWGN BPSK PSK_SYMBOL_DETECTOR AGC SCALER_1 SCALER_2 PLL FIR CLARK SYMBOL_MAPPER FIR_MF BPSK_ADD_FRAME BPSK_FRAME_SYNC
# Driver  ##Probably not needed by anyone
# InputGeneration ##Code is borked
# TX_RRC_FILTER ##Code is borked


##################################################
## For simle build rules involving a single file, use a single rule target
#name_of_executable:object_source.cpp
#> $(CXX) $(CXXFLAGS) $^ -o $@
##################################################

DRIVER_PATH = -I/_path_/_to_/_drivers_
Driver : driver/BasicStream.cpp
> $(CXX) $(CXXFLAGS) $(DRIVER_PATH) $^ -o $@

BPSK_ADD_FRAME: bpsk_syncword/bpsk_add_frame.cpp
> $(CXX) $(CXXFLAGS) $^ -o $@

BPSK_FRAME_SYNC: bpsk_syncword/bpsk_frame_synchronization.cpp
> $(CXX) $(CXXFLAGS) $^ -o $@

RX_RRC_FILTER : rx_rrc_filter/rx_rrc_filter.cpp
> $(CXX) $(CXXFLAGS) $^ -o $@

InputGeneration : tx_rrc_filter/input_generation.cpp
> $(CXX) $(CXXFLAGS) $^ -o $@

TX_RRC_FILTER : tx_rrc_filter/tx_rrc_filter.cpp
> $(CXX) $(CXXFLAGS) $^ -o $@

BPSK : bpsk/BPSKTRY.cpp
> $(CXX) $(CXXFLAGS) $^ -o $@

FIR : fir/fir.cpp
> $(CXX) $(CXXFLAGS) $^ -o $@

FIR_MF : fir/fir_matched_filter.cpp
> $(CXX) $(CXXFLAGS) $^ -o $@

PLL : sync/pll.cpp
> $(CXX) $(CXXFLAGS) $^ -o $@

AWGN : awgn/awgn_channel.cpp
> $(CXX) $(CXXFLAGS) $^ -o $@

PSK_SYMBOL_DETECTOR : psk_symbol_detector/psk_symbol_detector.cpp
> $(CXX) $(CXXFLAGS) $^ -o $@

AGC : agc/agc.cpp
> $(CXX) $(CXXFLAGS) $^ -o $@

SCALER_1 : scalers/scaler_1.cpp
> $(CXX) $(CXXFLAGS) $^ -o $@

SCALER_2 : scalers/scaler_2.cpp
> $(CXX) $(CXXFLAGS) $^ -o $@

CLARK : channel_model/Clark.cpp
> $(CXX) $(CXXFLAGS) $^ -o $@

TX_PIPE_INTERFACE : pipe_interface/tx_pipe_interface.cpp
> $(CXX) $(CXXFLAGS) $^ -o $@

RX_PIPE_INTERFACE : pipe_interface/rx_pipe_interface.cpp
> $(CXX) $(CXXFLAGS) $^ -o $@

##################################################
## For more complex build rules involving header files, a two part structure is required
#name_of_executable: name_of_object.o
#> $(CXX) $(LDFLAGS) $< -o $@
#
#name_of_object.o : object_source.cpp object_header.cpp
#> $(CXX) -c $(CPPFLAGS) $(CFLAGS) $< -o $@
##################################################

SYMBOL_MAPPER : symbol_mapper/symbol_mapper.cpp
> $(CXX) -I../include -L../lib $< -o $@ -lsdr

#Symbol_Mapper : symbol_mapper.o
#> $(CXX) $(CXXFLAGS) $< -o $@
#> rm -f symbol_mapper.o

#symbol_mapper.o : symbol_mapper/symbol_mapper.cpp symbol_mapper/byte.hpp
#> $(CXX) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

##################################################
## Cleaners ##
.PHONY : cleanall cleanexe cleanobj
# Clean everything
cleanall : cleanapps cleanobj
# Only clean executable files
cleanapps :
> rm -f $(ALL_TARGETS)
# Only clean object files
cleanobj :
> rm -f $(shell find -name '*.o')
####################################################################################################
