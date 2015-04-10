# fbtruetype-android
  --------------------------------------------------------------------------
  			FBTrueType for Android
  --------------------------------------------------------------------------

  What is it?
  -----------

  FBTrueType is a standalone native ARM program for ROOTED Android devices, 
  which renders TrueType text to the device display, using the kernel
  framebuffer and the freetype2 library.


  Building
  --------

  You must be able to cross compile for ARM, on Ubuntu 14.04 for example
  you will need to install the following:

	$ sudo apt-get install libc6-armel-cross libc6-dev-armel-cross
	$ sudo apt-get install libncurses5-dev
	$ sudo apt-get install binutils-arm-linux-gnueabi
	$ sudo apt-get install gcc-arm-linux-gnueabi

  Once you are setup to cross compile for ARM, to build the program run

	$ make

  If you need to rebuild run:

	$ make clean
	$ make


  Installation
  ------------

  Once compiled, you will need to push this file to your ROOTED device, it
  is probably a good idea to put it on the SDCARD:

	$ adb push fbtruetype /sdcard/

  Now you need to login the device with ADB, and remount the /system
  partition as Read/Write like this:

	$ adb shell
	$ su
	$ mount -o rw,remount /system

  Now still in the same ADB shell, you should copy the file to /system/xbin 
  and then enable executable permissions, before remounting
  the /system partition as Read-Only again:

	$ cp /sdcard/fbtruetype /system/xbin/
	$ chmod 755 /system/xbin/fbtruetype
	$ mount -o ro,remount /system

  That's it. Normally, in order to run the program you must be root in 
  the ADB shell, so you would login and then SU like this:

	$ adb shell
	$ su
	$ fbtruetype


  Usage
  -----

  Usage:
	fbtruetype [OPTION] [TEXT]

  Options:

	-x:			X coordinate pixel (default 10)
	-y:			Y coordinate pixel (default 10)
	-f, --font:		Font name (.ttf file)
	-t, --textcolor:	Text color (RGB hex, e.g. 0xffffff)
	-s, --size:		Font size (default 22)
	-a, --alpha:		Alpha channel (1-100)
	-v, --verbose:		Verbose mode
	-V, --version:		Show version
	-?, -h, --help:		Print this help.
	-S, --start-console:	Output on start console only.
	-c:			Start on specified console.
	-d, --zygote:		Zygote is running mode.
	-z, --clear		Clear the device display.


  Usage Notes
  -----------

  With Zygote
  -----------

  If you try to execute the program with Zygote running, then
  the framebuffer will still be locked by Zygote and text will 
  only be displayed for a brief second. To circumvent this
  there is an option --zygote which captures the display from
  Zygote when the display is off. Only when the display is off
  (i.e, device is in lock state and the screen is dimmed)
  will this mode work. To reset the display just lock, unlock
  the device or press the power button. Once the screen has
  been captured from Zygote, the program will work in normal
  mode.

  **Note: With Zygote running the display may be captured by
  Zygote when a screen change event happens such as when you
  receive a call, SMS etc...

  Without Zygote (Headless)
  -------------------------

  If you prefer to kill Zygote completely to use the program,
  it can be stopped by issueing the following commands:

	$ adb shell
	$ su
	$ stop

  The "stop" command will completely shutdown Zygote and all child
  processes. After doing this it is necessary to clear the device
  display using the -z or --clear command options:

	$ fbtruetype --clear

  The display is now ready for some text, to restart Zygote just
  issue the following as root in ADB:

	$ start

  **Note: Without Zygote running you will be unable to receive calls
  or SMS etc...


  Examples
  --------

  Send some text to the display:

	$ fbtruetype "TEST"


  Clear the display:

	$ fbtruetype -z
  or
	$ fbtruetype --clear


  Send text with Zygote enabled but screen dimmed/locked:

	$ fbtruetype -d "TEST"


  Use the font DroidSansMono (Android fonts are located in
  /system/fonts/):

	$ fbtruetype -f /system/fonts/DroidSansMono.ttf "TEST"


  Use the font DroidSansMono and set the font size to 36:

	$ fbtruetype -s 36 -f /system/fonts/DroidSansMono.ttf "TEST"


  Set the font color to green:

	$ fbtruetype -t 00FF00 "TEST"


  Test Script
  ------------

  In the test directory you will find a script called matrix.sh
  Copy this to the device and run it like this:
	
	$ adb push test/matrix.sh /sdcard/

  Then open a ADB shell, SU to root and then copy the script
  to the /data/ directory where it can be executed from.
  Then change permissions to executable:

	$ adb shell
	$ adb su
	$ cp /sdcard/matrix.sh /data/
	$ chmod 755 /data/matrix.sh

  Now run the script to enter the Matrix :)

	$ /data/matrix.sh

  **Note: You will need busybox installed at /system/xbin/busybox
  to run the script.

  Notes
  -----

  This program has only been tested on ARMv7l, I hold no liability
  for any damage or otherwise which you may cause to your device.


  Licensing
  ---------

  Please see the file called LICENSE.


  Credits
  -------

  Written by Michael Higham <mhigham1986@gmail.com>

  This program is ported from fbtruetype by Stefan Reinauer, <stepan@suse.de>

