RF433Sniff
==========

Raw recording and display of RF433 status switch timings.
Allows to display a 433 Mhz telecommand signal structure.


Installation
------------

No installation, it is a script not a library.


Schematic
---------

1. Arduino board. Tested with NANO and UNO.

2. Radio Frequence 433Mhz RECEIVER like MX-RM-5V.

By default the RECEIVER is to be plugged on D2 of the board, this can be easily
changed by setting the macro:

```
PIN_RFINPUT
```

to a different value.

See file schema.fzz (Fritzing format) or schema.png, for a circuit example with
receiver plugged on D2.


Usage
-----

Compile and upload it and when a signal is received, it'll be printed out.

