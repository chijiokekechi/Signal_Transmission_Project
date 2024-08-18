#!/usr/bin/bash

SDIR='../../src'

cat 'in_file.txt' \
    | $SDIR/BPSK_ADD_FRAME \
    | $SDIR/SYMBOL_MAPPER 8 bpsk \
    | $SDIR/FIR \
    | $SDIR/AGC \
    # | $SDIR/tx_sdr  # Transmit OTA
