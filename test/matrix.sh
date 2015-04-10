#!/system/bin/sh

#########################################
# Matrix test script
#---------------------------------------- 
# by Michael Higham
# <mhigham1986@gmail.com>
#----------------------------------------
# Use this script as a test on looping
# the display
# 
# **Run it when Zygote is active then	
# press the power button and you will
# see why it is called Matrix :) 
#
#########################################


#########################################
# Busybox location
#########################################
busybox=/system/xbin/busybox


#########################################
# FBTrueType location
#########################################
fbtruetype=/system/xbin/fbtruetype


#########################################
# Screen size + Font size
#
# **Only change screen size unless you
# plan to calculate divisable number**
#
#########################################
screen_size_x=480
screen_size_y=800
font_size=10


#########################################
# Font divisable number for width, this
# is different for each font. You need to
# count manually the number of characters
# which can be displayed per line, with
# your selected font and font size.
#
# Once counted you need to calculate as
# follows:
#
# a = (screen_width - x_offset * 2)
# b = (a / characters per line)
#
# divisable_number = b
#
# This script is setup to use DroidSans
# at font size 10, if you are unsure,
# leave it as default
#########################################
font_width_divisable_number=6.052631579


#########################################
# Calculates number of characters per
# line, based on above divisable number
# and screen width.
#
# Calculates number of lines based on
# font size and screen height
#########################################
characters_per_line=$($busybox awk "BEGIN { print ( ($screen_size_x - 20) / ($font_width_divisable_number) ) }" | $busybox cut -d"." -f1)
number_of_lines=$($busybox awk "BEGIN { print ( ($screen_size_y - 20) / ($font_size) ) }" | $busybox cut -d"." -f1)


#########################################
# Echo message to virtual terminal
#########################################
echo "Starting the loop, to exit use: CTRL + C"


#########################################
# Set the y offset to begin from
# Set the character to print
#########################################
ypos=10
print_character=0


#########################################
# Start the inifinite page loop
#########################################
while true ;do

#########################################
# Begin the line loop
#########################################
line_no=1
while [ $line_no -le $number_of_lines ];do

	# Create the line string
	string=$($busybox awk "BEGIN {while (c++<$characters_per_line) printf $print_character}")
	# Print the line
	$fbtruetype -s $font_size -y $ypos -t 00FF00 "$string"
	# Increment the line number + y_offset
	ypos=$(($ypos+$font_size))
	line_no=$(($line_no+1))

done
#########################################
# End the line loop
#########################################


#########################################
# Change the character to print from
# 0 to 1, or 1 to 0, depending on it's
# current value
#########################################
if [ $print_character = 0 ];then
print_character=1
elif [ $print_character = 1 ];then
print_character=0
fi

#########################################
# Clear the display for next line loop
#########################################
$fbtruetype -z


#########################################
# Reset values for next line loop
#########################################
line_no=1
ypos=10

done
