#!/bin/bash

wget -q "http://www.espn.com/espn/print?id=16287927" -O johnz.html;
html2text johnz.html > johnz.txt

cat johnz.txt | 
awk '
/^([1-9][0-9]*)|([0]+)$/{
	if($6 == "300") {
		next;
	}

	split($0, chars, "")
	for(i=1; i <= length($0); i++){
		if(chars[i] !~ "" && chars[i] !~ "_")
			printf chars[i];
	}
	print "";
}' | awk '{ print $1, $(NF-2), $(NF-3), $2, $3 }' > players.txt;

