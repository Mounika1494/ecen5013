#! /usr/bin/python

import subprocess

returncode = subprocess.run(["uname","-r"],stdout = subprocess.PIPE)
print("current kernel version is", returncode.stdout.decode('utf-8'))
subprocess.call(["cp","/boot/config-" + str(returncode.stdout.decode('utf-8')),".config"])


