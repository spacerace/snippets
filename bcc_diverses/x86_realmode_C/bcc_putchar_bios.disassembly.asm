; created with ndisasm on linux
; $ ndisasm -o 100h bcc_pcb.com >> bcc_putchar_bios.disassembly.asm

00000100  55                push bp
00000101  89E5              mov bp,sp
00000103  57                push di
00000104  56                push si
00000105  83C4FC            add sp,byte -0x4
00000108  B006              mov al,0x6
0000010A  8846FB            mov [bp-0x5],al
0000010D  8A46FB            mov al,[bp-0x5]
00000110  30E4              xor ah,ah
00000112  053000            add ax,0x30
00000115  8846FB            mov [bp-0x5],al
00000118  8A46FB            mov al,[bp-0x5]
0000011B  30E4              xor ah,ah
0000011D  50                push ax
0000011E  E85800            call word 0x179
00000121  44                inc sp
00000122  44                inc sp
00000123  BBA001            mov bx,0x1a0
00000126  53                push bx
00000127  E82700            call word 0x151
0000012A  44                inc sp
0000012B  44                inc sp
0000012C  E81E00            call word 0x14d
0000012F  8946F8            mov [bp-0x8],ax
00000132  8B46F8            mov ax,[bp-0x8]
00000135  3D3412            cmp ax,0x1234
00000138  7509              jnz 0x143
0000013A  BB9001            mov bx,0x190
0000013D  53                push bx
0000013E  E81000            call word 0x151
00000141  44                inc sp
00000142  44                inc sp
00000143  E84200            call word 0x188
00000146  83C404            add sp,byte +0x4
00000149  5E                pop si
0000014A  5F                pop di
0000014B  5D                pop bp
0000014C  C3                ret
0000014D  B83412            mov ax,0x1234
00000150  C3                ret
00000151  55                push bp
00000152  89E5              mov bp,sp
00000154  57                push di
00000155  56                push si
00000156  EB14              jmp short 0x16c
00000158  8B5E04            mov bx,[bp+0x4]
0000015B  8A07              mov al,[bx]
0000015D  30E4              xor ah,ah
0000015F  50                push ax
00000160  E81600            call word 0x179
00000163  44                inc sp
00000164  44                inc sp
00000165  8B5E04            mov bx,[bp+0x4]
00000168  43                inc bx
00000169  895E04            mov [bp+0x4],bx
0000016C  8B5E04            mov bx,[bp+0x4]
0000016F  8A07              mov al,[bx]
00000171  84C0              test al,al
00000173  75E3              jnz 0x158
00000175  5E                pop si
00000176  5F                pop di
00000177  5D                pop bp
00000178  C3                ret
00000179  B40E              mov ah,0xe
0000017B  89E3              mov bx,sp
0000017D  8A4702            mov al,[bx+0x2]
00000180  B700              mov bh,0x0
00000182  B90100            mov cx,0x1
00000185  CD10              int 0x10
00000187  C3                ret
00000188  8A264C00          mov ah,[0x4c]
0000018C  CD21              int 0x21
0000018E  C3                ret
0000018F  007265            add [bp+si+0x65],dh
00000192  7475              jz 0x209
00000194  726E              jc 0x204
00000196  2D7465            sub ax,0x6574
00000199  7374              jnc 0x20f
0000019B  206F6B            and [bx+0x6b],ch
0000019E  2100              and [bx+si],ax
000001A0  0D0A00            or ax,0xa
000001A3  00                db 0x00
