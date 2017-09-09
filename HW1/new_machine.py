#! /usr/bin/python 

import os

os.system("sudo apt-get update");
os.system("sudo apt-get install git fakeroot build-essential ncurses-dev xz-utils libssl-dev bc")
os.system("cd /usr/src")
os.system("cd /usr/src && sudo wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.13.tar.xz")
os.system("sudo tar xf /usr/src/linux-4.13.tar.xz")
os.system("cd linux-4.13")
os.system("git clone https://github.com/Mounika1494/ecen5013.git")
os.system("cd linux-4.13")

