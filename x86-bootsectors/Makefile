all:
	make build_mbr_tool
	make build_pit_calculator
	make bs_simple
	make bs_music
	make bs_random
	ls -l image*mbr bs*bin

bs_simple:
	nasm -f bin -o bs_simple.bin bs_simple.asm
	./build_mbr bs_simple.bin
bs_music:
	nasm -f bin -o bs_music.bin bs_music.asm
	./build_mbr bs_music.bin
bs_random:
	nasm -f bin -o bs_random.bin bs_random.asm
	./build_mbr bs_random.bin

build_mbr_tool:
	cc utils_buildmbr.c -o build_mbr -Wall -Werror
build_pit_calculator:
	cc utils_calc_pit_spk_freq.c -o pit_calculator -Wall -Werror
	
clean:
	rm -rfv *.bin a.out *.bin.mbr ./build_mbr ./pit_calculator
test:
	qemu-system-i386 -fda bs_random.bin.mbr -boot a -soundhw pcspk
