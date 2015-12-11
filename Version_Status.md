**Version 0.27 (2/Aug/11)** and the SVN version

Everything that the earlier edition (0.26) had and also support for sandy bridge(console version) and potentially also correctly recognize all known form of i7 processors. Tool can now also print the deeper C7 state present in Sandy Bridge. Note that the QT based QUI doesn't print the C7 state and is a bit lacking in features compared to the console version. Additionally this version has a bug fix for dual socket code for GUIs. Logging enabled for both single socket and dual socket machines. Fix for a long time error in the GUI where Ghz was shown instead of Mhz. GUI now also shows hostname in title bar.


**Version 0.26 (4/Oct/10)**

**known bug**

- For dual sockets, if socket0 is empty and socket1 is filled, or if the OS is reporting that physical id=1 is filled and physical id=0 is empty, then the tool fails. SVN version works though.

**features**

- Added in support for logging the values. Does it for only single-socket code for the timebeing. Done via _-w l_ (logging only the latest frequencies) and _-w a_ (logging the frequencies over time) when passed with the i7z command.

- Added support to display the core frequencies for both single and dual-sockets. Done by reading the msrs for max junction temperature (prochot) and the digital readout, and then temp of core = junction temperature - digital readout. Chapter 14 of this intel doc www.intel.com/Assets/ja\_JP/PDF/manual/253668.pdf

- Temperature display is a beta feature, as i might be calculating it all wrong. Do tell me (email at the bottom of this page or post an issue) if you find any errors or it doesn't match say the output of **sensors**. Note that discrete measurements are done to find the temperature so they might not match exactly and be off by a degree or so.

**Version 0.25 (20/May/10)**

- Special thanks to bug fixes by Dave Johnson and testing by knuckles, AnupCShan and Ian R.

- Single and Dual socket code.

- program doesn't crash if cores are disabled on the fly.

- conditional compilation should allow correct behavior of code for the console version and GUI version on 32-bit/64-bit machines.

**Version 0.21-4 (22/Feb/10)**

-code prettified. makedev, root checking and a better msr modprobing now done within the program.

**Version 0.21-3 (12/Feb/10)**

- Fixed a long standing bug that caused in bad values to get printed randomly for some variables, one of those `heisenbugs'. Realized never to put in asm code and optimization together :)

- Added in support for almost all nehalem based processors, past and future till westmere.

- Also allows for variable number of cores, in case you disable core via say `echo 0 > /sys/devices/system/cpu/cpuX/online`. Both console and GUI versions updated.

- Removed all remnant of Intel CPUID code. Everything is now GPL v2.

- i tested it on a 64-bit machine so no guarantee for the 32-bit binary

- if you are sure you have a nehalem and my programs exits saying it cannot detect one. Comment out the if block here http://code.google.com/p/i7z/source/browse/trunk/i7z.c#106
from line 106-109 in i7z.c

**Version 0.2 (Jan/10)**

Almost everything of the earlier version (below) applies here.

Changelog:

1. Now C0 + C1 + C3 + C6=100%

2. Now, have a fancy GUI using QT in the GUI directory (Old Console version is still there), it might be off by a second or so on reporting due to consolidation between the timers via TSC and timers in QT.

![http://img.techpowerup.org/100131/52percent.jpg](http://img.techpowerup.org/100131/52percent.jpg)

BTW, if you are wondering why your laptop never gets high multipliers, you might be suffering from a kernel bug http://bugzilla.kernel.org/show_bug.cgi?id=15064


**Version 0.1 (June/09)**

Here's a goody for Linux users. It is still a console-only mode. If GUI/MS-windows people are interested, i might give that a shot too. This should work with i7/i5 machines with minimal code edits. I do check within the code for a nehalem processor number which might have increased/changed for the newer processors, so do change it at line 321 in i7z.c http://code.google.com/p/i7z/source/browse/trunk/i7z.c#321