#!/usr/bin/ksh
if [ "$#" == 0 ]
then
        echo "Error! No arguments"
else
        gfind -lname "$1" -ls | sort -k8 -k9 -k10 -r | sed -n "s/.*[.]\/\(.*\) -> .*/\1/p" | sed 's/\\ / /g'
fi
exit 0