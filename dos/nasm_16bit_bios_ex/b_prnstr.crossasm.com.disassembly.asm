; for a commented version of this file see "b_prnstr.com.disassembly.asm"

00000100  E84B00            call word 0x14e
00000103  B33F              mov bl,0x3f
00000105  BE0E01            mov si,0x10e
00000108  E82200            call word 0x12d
0000010B  E85A00            call word 0x168
0000010E  68656C            push word 0x6c65
00000111  6C                insb
00000112  6F                outsw
00000113  2031              and [bx+di],dh
00000115  36626974          bound bp,[ss:bx+di+0x74]
00000119  20776F            and [bx+0x6f],dh
0000011C  726C              jc 0x18a
0000011E  642100            and [fs:bx+si],ax
00000121  B403              mov ah,0x3
00000123  CD10              int 0x10
00000125  FEC6              inc dh
00000127  30D2              xor dl,dl
00000129  E83700            call word 0x163
0000012C  C3                ret
0000012D  FC                cld
0000012E  AC                lodsb
0000012F  84C0              test al,al
00000131  7405              jz 0x138
00000133  E80300            call word 0x139
00000136  EBF5              jmp short 0x12d
00000138  C3                ret
00000139  B90100            mov cx,0x1
0000013C  B409              mov ah,0x9
0000013E  CD10              int 0x10
00000140  E80100            call word 0x144
00000143  C3                ret
00000144  B403              mov ah,0x3
00000146  CD10              int 0x10
00000148  FEC2              inc dl
0000014A  E81600            call word 0x163
0000014D  C3                ret
0000014E  B600              mov dh,0x0
00000150  B200              mov dl,0x0
00000152  E80E00            call word 0x163
00000155  B409              mov ah,0x9
00000157  B020              mov al,0x20
00000159  B700              mov bh,0x0
0000015B  B9D007            mov cx,0x7d0
0000015E  B307              mov bl,0x7
00000160  CD10              int 0x10
00000162  C3                ret
00000163  B402              mov ah,0x2
00000165  CD10              int 0x10
00000167  C3                ret
00000168  B44C              mov ah,0x4c
0000016A  CD21              int 0x21
