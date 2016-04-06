#!/usr/bin/ksh
if [ "$#" == 0 ]
then
        ls -tl | grep '\->  ' | awk '{print $9}'
else
        ls -tl | grep '\-> '$1'$' | awk '{print $9}'
fi
exit 0