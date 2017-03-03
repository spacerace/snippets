# x86 serial - 8250 / 16450 / 16550 / 16750 / ...

This piece of code talks to your UART. It can be used in both, **real and
protected mode**, as it's **not using any BIOS or DOS interrupts**. It's 
just port io that even can be done under DOS, Linux, Windows, ...

It is very small and simple, the source files should be self-explaining.

(c) 2016 NS

