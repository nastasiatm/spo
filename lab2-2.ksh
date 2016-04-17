#!/usr/bin/ksh
if [ "$#" == 0 ]
then 
	echo "Error! No arguments"	
else
	name=`/usr/xpg4/bin/id -G "$1" 2>&-`
	if [ "$?" == 0 ]
	then
		a=`getent group | grep '^'$1'::' | awk -F: '{print $4}' | tr , '\n' `
		numb=`getent group | grep '^'$1'::' | awk -F: '{print $3}' | head -1 `
		b=`getent passwd | grep ':'$numb':' | awk -F: '{print $1}' | tr , '\n'`
		echo "$a\n$b" | sort -u -k1
	else
		echo "Group does not exist."
	fi	
fi
exit 0