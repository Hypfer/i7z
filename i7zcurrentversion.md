# Logging Functions #

Logging can be done via calling i7z with

**sudo ./i7z -w a**

appends the frequencies of the cores in a file.

**sudo ./i7z -w l**

overwrites the frequencies of the cores in a file. just the latest measurement


# Temperature #

Temperature is counted by observing the MSR for Tj (temperature junction) and the digital readout

Then, Temp =  Tj - digital readout

Chapter 14 of this intel doc www.intel.com/Assets/ja\_JP/PDF/manual/253668.pdf


# SVN version and >= ver 0.27 features #

Updated to support additional functions

Help menu via : `./i7z -h` OR `./i7z --help`

Append to a log file (freq is always logged when logging is enabled, no way to disable freq logging [yet](yet.md) ):  `./i7z --write a` OR `./i7z -w a`

Replacement instead of Append:  `./i7z --write l` OR `./i7z -w l`

(Enabling) Log the temperature (also needs the -w a or -w l option): `./i7z --logtemp` OR `./i7z -t`

(Enabling) Log the C-states (also needs the -w a or -w l option): `./i7z --logcstate` OR `./i7z -c`

LOGGING DEFAULTS:
(ENABLED by default when logging is enable) Default (freq) log file name is cpu\_freq\_log.txt (single socket) or cpu\_freq\_log\_dual_%d.txt (dual socket)_

(DISABLED by default) Default temp log file name is cpu\_temp\_log.txt (single socket) or cpu\_temp\_log\_dual_%d.txt (dual socket)_

(DISABLED by default) Default cstate log file name is cpu\_cstate\_log.txt (single socket) or cpu\_cstate\_log\_dual_%d.txt (dual socket)_

Specifying a different (freq) log file: `./i7z --logfile filename` OR `./i7z -l filename`

Specifying a different temperature log file: `./i7z --templogfile filename` [OR](OR.md) `./i7z -x filename`

Specifying a different cstate log file: `./i7z --cstatelogfile filename` [OR](OR.md) `./i7z -p filename`

Specifying a particular socket to print: `./i7z --socket0 X`  where X = 0, 1...

In order to print to a second socket use: `./i7z --socket1 X`  where X = 0, 1...

To turn the ncurses GUI off use: `./i7z --nogui`

Example: To print for two sockets and also change the log file `./i7z --socket0 0 --socket1 1 -logfile /tmp/logfilei7z -w l`