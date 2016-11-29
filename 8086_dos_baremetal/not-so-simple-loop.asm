        xor cx,cx   ; cx = 0
loop1   nop
        inc cx
        cmp cx,32   ; is cx at loop-iterations-limit?
        jle loop1   ; loop while <=
