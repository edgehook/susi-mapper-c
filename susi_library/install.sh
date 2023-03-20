#!/bin/bash

if [ $# = "0" ]; then
    echo "Description: choose ./install.sh 1 or ./install.sh 2"
    echo "Usage: $0 <mode> "
    echo "    <mode>: 1 or 2  1:install 2:uninstall"
    exit 1;
fi


case $1 in
	#For 247 acpi conflict
	#1) sed -i 's/.*GRUB_CMDLINE_LINUX=".*/GRUB_CMDLINE_LINUX="acpi_enforce_resources=no"/' /etc/default/grub
	#   update-grub
	#   modprobe nct6775
	#   cp nct6775.conf /etc/modules-load.d/
        1) rm -f /usr/lib/libjansson.so* /usr/lib/libSusiIoT.so*
  	   rm -rf /usr/lib/Advantech/iot
	   rm -f /usr/lib/libSUSI-4.00.so*
  	   ldconfig
  	   mkdir -p /usr/lib/Advantech/iot/modules/
  	   cp -ra *.so* /usr/lib/
  	   cp -ra modules/libSUSIDrv.so /usr/lib/Advantech/iot/modules/
  	   cp -ra modules/libDiskInfo.so /usr/lib/Advantech/iot/modules/
  	   ldconfig
  	   echo "install done"
	   ;;
	2) rm -f /usr/lib/libjansson.so* /usr/lib/libSusiIoT.so*
	   rm -rf /usr/lib/Advantech/iot
	   rm -f /usr/lib/libSUSI-4.00.so*
	   rm /etc/modules-load.d/nct6775.conf
	   sed -i 's/.*GRUB_CMDLINE_LINUX="acpi_enforce_resources=no*/GRUB_CMDLINE_LINUX=""/' /etc/default/grub
           update-grub
	   ldconfig
	   echo "uninstall done"
esac

