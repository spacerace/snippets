all:
	nasm -o b_prnstr.crossasm.com -f bin b_prnstr.asm

disasm:
	ndisasm -o 100h b_prnstr.com > b_prnstr.com.disassembly.asm-new
	ndisasm -o 100h b_prnstr.crossasm.com > b_prnstr.crossasm.com.disassembly.asm-new
	ndisasm -o 100h bioschar.com > bioschar.com.disassembly.asm-new
