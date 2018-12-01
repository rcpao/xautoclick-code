#!/bin/bash -x

# build-deb.sh for Ubuntu 18.04.1 
# Thu Nov 29 21:11:53 PST 2018
# rcpao

# sudo apt-get install libgtk2.0-dev libxtst-dev 
./configure
make

# sudo apt-get install checkinstall
sudo checkinstall -D -y

# uninstall
sudo dpkg -r xautoclick
# install
sudo dpkg -i xautoclick_20181201-1_amd64.deb
# run
/usr/local/bin/gautoclick2
