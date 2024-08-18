#!/usr/bin/bash

SDIR='../../src'

echo 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz' \
    | $SDIR/BPSK_ADD_FRAME \
    | $SDIR/SYMBOL_MAPPER 8 bpsk \
    | $SDIR/FIR \
    | $SDIR/AGC \
    | $SDIR/AWGN 15 \
    | $SDIR/FIR_MF \
    | $SDIR/BPSK_FRAME_SYNC \
    | $SDIR/PSK_SYMBOL_DETECTOR 1 8 0 \
    | python3 $SDIR/utils/decode.py
    # | python3 constellation_plotter/constellation_plotter.py "Coherent AWGN Channel Output" \
    # | python3 signal_power/plot_time.py \
