#!/usr/bin/ksh
[ "$#" == 1 ] || { echo "Error! No arguments"; exit 1; } 
if [ -f "$1" ]
then
	IFS=
	a=$(echo "$1" | nawk -F/ '{print $NF}' 2>&-)
	gfind "$PWD" -maxdepth 1 -samefile "$1"  ! -name "$a" -exec ls -t {} + 2>&-  | nawk -F/ '{print $NF}' 2>&- #также выводит жесткие ссылки 
	
else
	echo "File does not exist."
fi
exit 0