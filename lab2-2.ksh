#!/usr/bin/ksh
if [ "$#" == 0 ]
then
        echo "Error! No arguments"
else
        getent group | grep '^'$1'::' | awk -F: '{print $4}' | tr , '\n' >> temp.txt
        numb=`getent group | grep '^'$1'::' | awk -F: '{print $3}' | head -1`
        getent passwd | grep ':'$numb':' | awk -F: '{print $1}' | tr , '\n' >> temp.txt
fi
sort -k1 -u temp.txt
rm -f temp.txt 2>$-
exit 0