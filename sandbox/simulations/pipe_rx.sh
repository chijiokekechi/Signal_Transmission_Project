#!/usr/bin/bash

SDIR='../../src'

# TODO: Add sdr receive script
# $SDIR/sdr_rx | 
$SDIR/AGC \
    | $SDIR/FIR_MF \
    | $SDIR/BPSK_FRAME_SYNC \
    | $SDIR/PSK_SYMBOL_DETECTOR 1 8 0 \
    | python3 $SDIR/utils/decode.py > out_file.txt
    # | python3 constellation_plotter/constellation_plotter.py "Coherent AWGN Channel Output" \
    # | python3 signal_power/plot_time.py \
