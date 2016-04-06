#!/usr/bin/ksh
getent group | grep '^'$1'::' | awk -F: '{print $4}'
numb=`getent group | grep '^'$1'::' | awk -F: '{print $3}' | head -1`
getent passwd | grep ':'$numb':' | awk -F: '{print $1}'
exit 0