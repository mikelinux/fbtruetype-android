  --------------------------------------------------------------------------
  			FBTrueType for Android
  --------------------------------------------------------------------------

  -----------
  What is it?
  -----------

  FBTrueType is a standalone native ARM program for ROOTED Android devices, 
  which renders TrueType text to the device display, using the kernel
  framebuffer and the freetype2 library.


  --------
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


  ------------
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


  -----
  Usage
  -----

  Usage:
	fbtruetype [OPTION] [TEXT]

  Options:

	-?, -h, --help:		Print this help.
	-V, --version:		Show version.
	-i, --info:		Print device display information.

	-z, --zygote:		Zygote mode.
	-p, --power:		Send power key event.
	-c, --clear		Clear the device display.

	-x:			X coordinate pixel [default 10]
	-y:			Y coordinate pixel [default 10]
	-b, --brightness:	Set display brightness [0-255] [default 170]
	-w, --boxwidth:		Text box column size [default 65]
	-f, --font:		Font name [.ttf file]
        -s, --size:		Font size [default 12]
	-t, --textcolor:	Font color [RGB Hex: FFFFFF]
	-a, --alpha:		Alpha channel [1-100]


  -----------
  Usage Notes
  -----------

  With Zygote
  -----------

  If you try to execute the program with Zygote running, then
  the framebuffer will still be locked by Zygote and text will 
  only be displayed for a brief second. To circumvent this
  there is an option --zygote which captures the display from
  Zygote when the display is in sleep mode. Only when the 
  display is off (i.e, device is in lock state and the screen 
  is dimmed) will this mode work. To reset the display just 
  issue the --power option or press the power button on the
  device. Once the framebuffer has been captured from Zygote,
  the program will work in normal mode.

  **Note: With Zygote running the display may be written to by
  Zygote when a screen change event happens such as when you
  receive a call, SMS, clock widgets etc...

  -------------------------
  Without Zygote (Headless)
  -------------------------

  If you prefer to kill Zygote or you experience corrpution on
  the display using Zygote more then you should stop the Zygote
  process completely by issuing the following commands:

	$ adb shell
	$ su
	$ stop

  The "stop" command will completely shutdown Zygote and all child
  processes. After doing this it is necessary to clear the device
  display using the -c or --clear command options:

	$ fbtruetype --clear

  The display is now ready for some text, to restart Zygote just
  issue the following as root in ADB:

	$ start

  **Note: Without Zygote running you will be unable to use android
  functions like receiving calls or SMS etc...


  --------
  Examples
  --------

  Send some text to the display:

	$ fbtruetype "TEST"


  Clear the display:

	$ fbtruetype -c

  or use:

	$ fbtruetype --clear


  Change the text box column width to 30:

	$ fbtruetype -w 30 "The quick brown fox jumps over the lazy dog. The quick brown fox jumps over the lazy dog."


  Send text with Zygote still running:

	$ fbtruetype -z "TEST"


  Use the font DroidSans (Android fonts are located in
  /system/fonts/):

	$ fbtruetype -f /system/fonts/DroidSans.ttf "TEST"


  Use the font DroidSans and set the font size to 36:

	$ fbtruetype -s 36 -f /system/fonts/DroidSans.ttf "TEST"


  Set the font color to green:

	$ fbtruetype -t 00FF00 "TEST"


  Set the display brightness to 150:

	$ fbtruetype -b 150 "TEST"


  Set the text position to X=50 and Y=100:

	$ fbtruetype -x 50 -y 100 "TEST"


  Simulate the power button (turn display ON/OFF):

	$ fbtruetype -p


  ------------
  Test Script
  ------------

  In the test directory you will find a script called devinfo.sh
  Copy this to the device and run it like this:
	
	$ adb push test/devinfo.sh /sdcard/

  Then open a ADB shell, SU to root and then copy the script
  to the /data/ directory where it can be executed from.
  Then change permissions to executable:

	$ adb shell
	$ adb su
	$ cp /sdcard/devinfo.sh /data/
	$ chmod 755 /data/devinfo.sh

  Now run the script to view basic device information on the
  display of the device.

	$ /data/devinfo.sh

  -----
  Notes
  -----

  This program has only been tested on an old HTC ARMv7l, therefore
  it might be incompatible or even damage your device. I hold no
  liability for any damage or otherwise which you may cause to
  your device by using this program.


  ---------
  Licensing
  ---------

  Please see the file called LICENSE.


  -------
  Credits
  -------

  (c) 2015 by Michael Higham, <mhigham1986@gmail.com>
 
  This program is based on fbtruetype, written and (C) by
  (c) 2001-2002 by Stefan Reinauer, <stepan@suse.de>

  This program my be redistributed under the terms of the
  GNU General Public Licence, version 2, or at your preference,
  any later version.

