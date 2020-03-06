#!/bin/bash
# Первый параметр - периодичность проверки
#Второй параметр - команда
PID=`ps aux | grep "$2" | grep -v grep | cut -d' ' -f3`
echo "pid =$PID"
TIME=$1

while true
do
	PID=`ps aux | grep "$2" | grep -v grep | cut -d' ' -f3`
	if [ -n "$PID" ]
	then
		sleep $TIME
	else
		$2 &
	fi
done
	
