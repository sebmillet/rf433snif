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


Note about interrupts
---------------------

rf433snif does **NOT** rely on interrupts, therefore the DATA of the RECEIVER
can be plugged on any digital PIN of the board.


Usage
-----

Compile and upload it and when a signal is received, it'll be printed out.


About plot.py
-------------

This python script (of alex-eri, https://github.com/alex-eri) takes the output
of rf433snif and renders it as a graph.

The timings output by rf433snif are to be copy/pasted to the top of `plot.py`.

To execute it on my 'Linux Debian 11' I had to run:

```shell
# Do this one once, to install script' pre-req
pip3 install matplotlib

python3 plot.py
```

