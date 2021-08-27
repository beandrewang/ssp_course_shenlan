make clean && make && rm -rf err.raw

./adapt_filt audio.raw err.raw

play -r 16000 -b 16 -c 1 -e signed-integer err.raw
