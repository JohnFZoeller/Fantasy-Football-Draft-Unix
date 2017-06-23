#!/bin/bash

wget -q "http://www.espn.com/espn/print?id=19463166" -O johnz.html;
html2text johnz.html > johnz.txt

cat johnz.txt |
awk '
/^([1-9][0-9]*)|([0]+)$/{
	if($6 == "300") {
		next;
	}

	split($0, chars, "")							#split all chars
	for(i=1; i <= length($0); i++){					#loop all chars
		if(chars[i] !~ "" && chars[i] !~ "_")		#kill bad chars
			printf chars[i];						#print all 
	}
	print "";
}' | awk '{ print $1, $(NF-1), $2, $3, $4}' > players.txt;

