#!/usr/bin/ksh
IFS=
[ "$#" == 1 ] || { echo "Error! Input user name"; exit 1; }
/usr/xpg4/bin/id -u $1 1>&- 2>&- || { echo "Error! Invalid user name"; exit 1; }
_uid=$1
_gids=`groups $1 2>&- | tr ' ' '\n' 2>&- || { echo "Error! Invalid user name"; exit 1; }`
echo "$_gids"
temp=$(echo "$_gids" | while read line
do
	_gid=`echo "$line"`
	ls -la | awk '{if ($3=="'$_uid'") print $0}' | grep "^-r" | awk '{ for (i=1;i<=8;i++) $i=""; print $0}' | sed 's/^ *//g'
	ls -la | awk '{if ($3!="'$_uid'") if ($4=="'$_gid'") print $0}' | grep "^-...r" | awk '{ for (i=1;i<=8;i++) $i=""; print $0}' | sed 's/^ *//g'
	ls -la | awk '{if ($3!="'$_uid'") if ($4!="'$_gid'") print $0}' | grep "^-......r" | awk '{ for (i=1;i<=8;i++) $i=""; print $0}' | sed 's/^ *//g' 
done)
echo "$temp" | sort -u


exit 0