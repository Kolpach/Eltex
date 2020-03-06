#!/bin/bash
PID="0"
echo "aplay -N -q $2 > /dev/null 2> /dev/null & " | at $1 2> /dev/null
while true
do
	PID=`pidof "aplay"`
	if [ -n "$PID" ]
	then
		read -n 1 -s -r -p "Press any key to stop"
		echo
		break
	fi
done
kill $PID > /dev/null 2> /dev/null
wait $PID 2>/dev/null
