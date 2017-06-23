#!/bin/bash

wget -q "http://www.espn.com/espn/print?id=19463166" -O playerList.html;
html2text playerList.html > playerList.txt

cat playerList.txt |
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
}' | awk '{ print $1, $(NF-8), $(NF-9), $2, $3}' > players.txt;

