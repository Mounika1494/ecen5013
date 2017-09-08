#! /usr/bin/python

import subprocess

returncode = subprocess.Popen(["uname","-s"],stdout = subprocess.PIPE,stderr = subprocess.PIPE)
out,err = returncode.communicate()
print "Operating System type is ", out
returncode = subprocess.Popen(["lsb_release","-a"],stdout = subprocess.PIPE,stderr = subprocess.PIPE)
out,err = returncode.communicate()
print "OS distribution is \n", out
returncode = subprocess.Popen(["uname","-r"],stdout = subprocess.PIPE,stderr = subprocess.PIPE)
out,err = returncode.communicate()
print "kerenl version is ", out
returncode = subprocess.Popen(["grep","gcc","/proc/version"],stdout = subprocess.PIPE,stderr = subprocess.PIPE)
out,err = returncode.communicate()
print "Gcc version is \n", out
returncode = subprocess.Popen(["lscpu"],stdout = subprocess.PIPE,stderr = subprocess.PIPE)
out,err = returncode.communicate()
print "System Information architecture is \n ", out
returncode = subprocess.Popen(["uname","-v"],stdout = subprocess.PIPE,stderr = subprocess.PIPE)
out,err = returncode.communicate()
print "Last kernel build was on ", out

