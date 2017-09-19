#! /usr/bin/python 

import os

os.system("sudo insmod /home/mounika/ecen5013/linux-4.12.10/drivers/mytime/mytime.ko");
os.system("sudo cp -r /home/mounika/ecen5013/linux-4.12.10/drivers/mytime /lib/modules/4.12.10/kernel/drivers/")
os.system("cd /home/mounika/ecen5013/linux-4.12.10/drivers/mytime/ && sudo depmod -a")
os.system("modinfo mytime")
print "lsmod of mytime"
os.system("lsmod | grep mytime")
