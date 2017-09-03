#! /usr/bin/python

import subprocess

returncode = subprocess.Popen(["uname","-r"],stdout = subprocess.PIPE,stderr = subprocess.PIPE)
out,err = returncode.communicate()
print "current kernel version is", out
out = out.strip('\n')
print out
subprocess.call(["cp","/boot/config-" + str(out),".config"])
print "modules selected according to previous configuration"
subprocess.call(["make","menuconfig"])
nocpu=subprocess.Popen(["nproc"],stdout = subprocess.PIPE,stderr = subprocess.PIPE)
cpu,err = nocpu.communicate()
cpu = cpu.strip('\n') 
print "no of cpu cores",cpu
subprocess.Popen(["make","-j",cpu])
subprocess.Popen(["make","modules_install","-j",cpu])
subprocess.Popen(["make","install","-j",cpu])

