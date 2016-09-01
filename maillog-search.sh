#!/bin/sh

if [ $# -lt 2 ]
then
	echo "\nError: Usage: $0 <email address> <logfile>\n"
	exit -1
fi

EMAIL_ADDR=$1
LOGFILE=$2

if [ ! -e $LOGFILE ]
then
	echo "No log file by that name!"
	exit -1
fi

# search for postfix (only smtp and qmgr) - discard queue removal line
grep $EMAIL_ADDR $LOGFILE | egrep "postfix/(smtp|qmgr)" | grep -v "removed" | uniq |
(
	while read -e LINE
	do
		ID=`echo $LINE | awk '{print $6}'`
		if [ "$ID" = "NOQUEUE:" ] ; then echo -e "$LINE\n----------------------------------------------------------------------------------------------------\n"

		else
			grep $ID $LOGFILE |egrep "postfix/(smtp\[|qmgr)" | grep -v "removed"

			echo -e "\n----------------------------------------------------------------------------------------------------\n"
		fi
	done
)
