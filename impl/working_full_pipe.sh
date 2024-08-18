SDIR='../src'

cat test_file.txt \
    | $SDIR/TX_PIPE_INTERFACE \
    | $SDIR/SYMBOL_MAPPER 8 bpsk \
    | $SDIR/FIR \
    | $SDIR/FIR_MF \
    | $SDIR/RX_PIPE_INTERFACE \
    | $SDIR/PSK_SYMBOL_DETECTOR 1 1 0 \
    | python3 $SDIR/utils/decode.py > pipe_out.txt

