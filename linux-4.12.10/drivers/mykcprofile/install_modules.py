#! /usr/bin/python 

import os

os.system("sudo insmod /home/mounika/ecen5013/linux-4.12.10/drivers/mytaskinfo/mytaskinfo.ko");
os.system("sudo cp -r /home/mounika/ecen5013/linux-4.12.10/drivers/mytaskinfo /lib/modules/4.12.10/kernel/drivers/")
os.system("cd /home/mounika/ecen5013/linux-4.12.10/drivers/mytaskinfo/ && sudo depmod -a")
os.system("modinfo mytaskinfo")
print "lsmod of mytaskinfo"
os.system("lsmod | grep mytaskinfo")
