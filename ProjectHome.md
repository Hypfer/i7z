Summary says all: A better i7 (and now i3, i5) reporting tool for Linux. Source and makefiles inside the download OR sync in the Source Tab OR sync @ http://github.com/ajaiantilal/i7z (git://github.com/ajaiantilal/i7z.git)

# How to Use #
You can either Compile or use precompiled binaries (see below).
## Compile and Use ##
Get the latest source from either the downloads or svn source (both are somewhat synced currently).
then

1. cd i7z   _(or whatever directory it is extracted to and also make sure that a file named Makefile is there in the directory before continuing with next step)_

2. make     _(in case this step doesnot succeed and there is some error about ncurses.h, install libncurses5-dev, for debian/ubuntu this can be done via **sudo apt-get install libncurses5-dev**)_

3 sudo ./i7z

To compile QT based GUI: Navigate to the GUI subdirectory, Note that the QT GUI has somewhat fallen on the wayside and doesn't have all features as the console version. **For sandybridge and ivybridge, it incorrectly adds C7 state values to the C0 state, so it does report things incorrectly; use the console version as its upto date.**

1. cd i7z/GUI

2. qmake _(if qt is correctly install, this command will set the qt-paths in the Makefile)_

3. make clean; make _(to generate the i7z\_GUI executable)_

4. sudo ./i7z\_GUI

## Precompiled Binaries ##

Just download the statically linked file (download the right file for your machine depending on whether your machine is 32 bit or 64 bit)

**32 Bit**

http://i7z.googlecode.com/svn/trunk/i7z_32bit (md5sum = 77d3fe483a6435d2863e8d45b32254ed, size is about 800kb)

**64 Bit**

http://i7z.googlecode.com/svn/trunk/i7z_64bit (md5sum = f91a58e3236471cc0890bbd6def93b3b, size is about 1 megabyte)


then do

1. **chmod +x i7z\_XXbit** (where XX=32 or 64 depending on OS type)

2. **sudo ./i7z\_XXbit** (where XX=32 or 64 depending on OS type)


## Additional Script to read / write to registers ##
The svn contains a script to read/write to registers on Nehalems and Sandy Bridges machine to change multipliers, turbo mode, check power and clock modulation in Linux. Do give it a try and please post if you encounter any issues.

Script : http://code.google.com/p/i7z/source/browse/trunk/i7z_rw_registers.rb

Download from this link: http://i7z.googlecode.com/svn/trunk/i7z_rw_registers.rb

Script can be run (needs ruby installed) as:  **sudo ruby i7z\_rw\_registers.rb**

msr-tools need to be installed. In Debian/Ubuntu its **sudo apt-get install msr-tools** and probably **sudo modprobe msr** before running the script

## Latest version 0.27.1 ##
Latest source also has the ability to print information about multi-sockets machine.

**sudo ./i7z --socket0 0 --socket0 1**

send the socket numbers as arguments and the information about those sockets will be printed. Note that there is not enough space to print all the information so there might be some overlapping of stuff going on. Also, newer E7 based processors dont seem to have multiplier information anywhere (register has been removed) and in that case multiplier information will be printed as 0x/0x/

Also, 0.27.1 version updated to support additional functions

Help menu via : ./i7z -h OR ./i7z --help

Append to a log file: ./i7z --write a OR ./i7z -w a

Replacement instead of Append: ./i7z --write l OR ./i7z -w l

Default log file name is cpu\_freq\_log.txt (single socket) or cpu\_freq\_log\_dual%d.txt (dual socket)

Specifying a different log file: ./i7z --logfile filename OR ./i7z -l filename

Specifying a particular socket to print: ./i7z --socket0 X where X = 0, 1...

In order to print to a second socket use: ./i7z --socket1 X where X = 0, 1...

To turn the ncurses GUI off use: ./i7z --nogui

Example: To print for two sockets and also change the log file ./i7z --socket0 0 --socket1 1 -logfile /tmp/logfilei7z -w l

## Current (0.27 and svn source) Version Information ##
Everything that the earlier edition (0.26) had and also support for sandy bridge(console version) and potentially also correctly recognize all known form of i7 processors. Tool can now also print the deeper C7 state present in Sandy Bridge. Note that the QT based QUI doesn't print the C7 state and is a bit lacking in features compared to the console version. Additionally this version has a bug fix for dual socket code for GUIs. Logging enabled for both single socket and dual socket machines. Fix for a long time error in the GUI where Ghz was shown instead of Mhz. GUI now also shows hostname in title bar.

### features ###
- Added in support for logging the values of C states. Done only for single-socket code. Done via _-w l_ (logging only the latest frequencies) and _-w a_ (logging the frequencies over time) when passed with the i7z command. e.g. sudo ./i7z -w l or sudo ./i7z -w a

- Added support to display the core temperature for both single and dual-sockets (last column in the console version, no support yet in GUI version). Done by reading the msrs for max junction temperature (prochot) and the digital readout, and then temp of core = junction temperature - digital readout. Chapter 14 of this intel doc www.intel.com/Assets/ja\_JP/PDF/manual/253668.pdf

- Temperature display is a beta feature. Note that discrete measurements are done to find the temperature so they might not match exactly and be off by a degree or so.

- Single and Dual socket support including Nehalems and Sandy Bridge machines. I dont print information for > 2 sockets as there is not enough space in terminal.

- Also allows for variable number of cores, in case you disable core via say `echo 0 > /sys/devices/system/cpu/cpuX/online`. Console program doesn't crash if cores are disabled on the fly. GUI program still has this issue.

- Now C0 + C1 + C3 + C6 + C7 = 100%. C7 only present in Sandy Bridge and not Nehalem.

- have a fancy GUI using QT in the GUI directory (Old Console version is still there), it might be off by a second or so on reporting due to consolidation between the timers via TSC and timers in QT.

![http://img.techpowerup.org/100131/52percent.jpg](http://img.techpowerup.org/100131/52percent.jpg)


## History and Some Usage ##
There was no standard way (june/09) to report on CPU information for i7 within Linux, so i coded a small program that has capabilities of reporting on the stock and overclocked i7. This tool will work only on linux (i tested 64-bit but 32-bit should would too) and on an i7 (tested it on 920). Readme, and Code provided in attachment.

It knows about Turbo mode, Multipliers, Number of CPUs and more (including correct frequency and C-states, especially the C-states). I don't know of a utility that directly gives details of what C-state the cpu ran(in the past some times). Edit: Turbostat in pmtools also gives this information.

**POWER Saving**
If you want to save power, enable C6 state in bios. I did some experiments with how much saving of power C6 vs. only having C0-C1 will give. My readings are as follows, for my idle system the power readout when enabling only C0-C1 states is 206 Watts and the same environment when using C6 state was 183 Watts. Thus, one can save upto 23 watts at idle by just putting your CPU in a C6 states. Note: these results were done on an i7 920 with lots and lots of fans (all set to a specific value), HDDs and other components were made sure to always run within limits and averaged over multiple runs, thus explaining the high idle wattage (one more reason is my PSU is usually most efficient at 85% around >150 Watts). Also, over multiple runs, these values don't budge a bit, in case if you are wondering :)

Yet another results i obtained was the fact that USB devices are bad for power saving features. Install powertop (should be in the repositories) and note down what devices are causing most of the interrupts. Note, some devices like Wattsup-pro that use usb have a tendency to make CPU always run in C0-C1 state even if C6 is enabled, so be wary if you are concerned about saving power when using these devices. Avg. loss due to these devices is in the vicinity of 8 Watts.

A tickless, or kernel configured with 100Hz interrupts will go a long way in saving a bit more of power.

**Note that the below figures are with 0.01 version of the code and the latest version may look a little different**

**20x-fullspeed (Non turbo)**
This screenshot shows that Turbo is disabled, but as prime is running, one can get to the max multiplier of 20. The cpuinfo says its running at 2.66Ghz but it's actually running at 20x175 = 3.5Ghz

![http://img.techpowerup.org/090615/turbo_off_20x_prime.png](http://img.techpowerup.org/090615/turbo_off_20x_prime.png)

**C-states**
By default i7 and almost all processors go in a halted cycle mode if there is no load. There are 4 columns for each of the code that shows what C state the cpu is in. They are in %.

C0+C1 = 100%

C3 and C6 column are also in %. For example for processor 0, C1% (halted is 100%) out of which C6 state contribution is 10.3% (**thus C6, C3 is included in C1**).

The below way i do calculation for C states

C0 = unhalted cycles

C1 = total halted cycles

C3 = halted cycles in C3

C6 = halted cycles in C6

and dividing by the total number of TSC cycles gives the percentage.


Below pic is on console (seems that when even running minimalistic GUI, there is almost 0 probability of ending in C6)
![http://img.techpowerup.org/090615/C6590.jpg](http://img.techpowerup.org/090615/C6590.jpg)


**19x-Halted (Non turbo)**
As seen below that the CPU goes into C1 mode most of the time(Cores active but halted cycles on CPU). I think Intel refers it to C1 or C1E state (correct me if i am not).

![http://img.techpowerup.org/090615/turbo_off_19x_halted.png](http://img.techpowerup.org/090615/turbo_off_19x_halted.png)

**21x-Halted (Turbo)**
detected Turbo, but do note that the cpu has stepped down.

![http://img.techpowerup.org/090615/turbo_21x_halted.png](http://img.techpowerup.org/090615/turbo_21x_halted.png)

**21x-fullspeed (Turbo)**
Finally, CPU is really running at 21x in linux at full load:)

![http://img.techpowerup.org/090615/turbo_21x_prime.png](http://img.techpowerup.org/090615/turbo_21x_prime.png)

**Linux doesn't need cpufreq util.**
Cpu managing software is so last to last year. Seems that CPU throttles down to lower freq if there is no load, even when there is no cpufreqd or acpi-cpufreq module is installed!

![http://img.techpowerup.org/090615/running_at_low_freq_NO_ACPICPUFREQ900.jpg](http://img.techpowerup.org/090615/running_at_low_freq_NO_ACPICPUFREQ900.jpg)

BTW, this code will work on any x58 (no bios routines used). Also, if i get the bios info (from somewhere ;) ) that eleet (EVGA x58 overclocking tool) uses to increase QPI, i probably write an overclocking tool for Linux.

**Algorithm** i use to calculate everything is as follows:

1. Show the user the freq. reported by /proc/cpuinfo and imply that it might be incorrect. :)

2. use linux's cpu khz code that estimates the Mhz, picked from http://www.cs.helsinki.fi/linux/linux-kernel/2001-37/0256.html

3. find the current multiplier set, from the CPU MSR. BLCK Freq without accounting Turbo is freq give by cpu\_khz / Multipler

4. Now try to see if Turbo is enabled/disabled from the CPU MSR. If enabled the max freq is basically (Base\_multiplier + 1/2/3/4..) X BLCK Freq. For 920 that can ramp from 20 multiplier to 22 or 21 multiplier, the base multiplier is 20 and the extra multiplier is 1 or 2. Socket 1156 i7 can ramp the turbo multiplier upto 5 i think.

5. From 3-4, update the screen about BLCK, TURBO etc.

6. Using TSC, every 1 sec estimate the number of cycles elapsed for each of the C0, C1, C3, C6 state by reading every processor and divide that by the counter in TSC. This will give a ratio of how much time was spent in each of the C-states. Now if HT is enabled/disabled then read from cores 1-4. I found out that when HT is enabled reading from 5-8 cores give the same results as reading from 1-4, So i guess that the logical (threaded) processors also mimic the readings of their companion processors.



References for the MSRs is from the Intel Software development manual 3B, Appendix B.
http://www.intel.com/products/processor/manuals/

Algorithm to calculate for turbo mode is listed by Intel here http://download.intel.com/design/processor/applnots/320354.pdf?iid=tech_tb+paper

Dont do this: Run multiple instances at once or use some other tool that also uses TSC. Well there are just 1 per processor, so if there are multiple tools using the TSC, you might get incorrect results.


If you find this tool useful i will love to have comments on making it better. Also if you encounter any bugs (there might be a bit of them as i coded this in under a day) please let me know.
Enjoy!

Abhishek Jaiantilal (abhishek.jaiantilal (@@) colorado.edu)