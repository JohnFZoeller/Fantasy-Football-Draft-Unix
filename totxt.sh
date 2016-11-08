#!/bin/bash

#
#
#

wget "http://www.espn.com/espn/print?id=16287927" -O johnz.html;
html2text johnz.html > johnz.txt 

awk '/^([1-9][0-9]*)|([0]+)$/{print $0;}' johnz.txt >> playas.txt