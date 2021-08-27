make clean && make && rm -rf dst.raw

./add_rir audio.raw dst.raw

play -r 16000 -b 16 -c 1 -e signed-integer dst.raw
