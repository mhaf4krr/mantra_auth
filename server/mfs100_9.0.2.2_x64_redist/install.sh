#!/bin/sh
clear
echo "Welcome to Mantra MFS100 V9022 SDK Installation"
echo "This software is provided with a license agreement - please read carefully"
cat license.txt
echo "Do you want to accept the license agreement?"
read line
accepted=0;
  case $line in
   y|Y|yes|YES)
	accepted=1;
	;;
  n|N|NO|no)
	accepted=0;
	;;
  esac

if [ $accepted -eq 0 ]; then
echo "exiting without installing"
exit 1;
fi
sudo tar -xzf MFS100_Lib_x64_V9022_Redist.tgz -C /

echo "installed the package succefully"
echo "please check /usr/include/MFS100V11.h for api information"
echo "please check /usr/Src for sample source information"







