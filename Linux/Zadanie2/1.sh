#!/bin/bash
# Primer while
directory=$1
nameOfFolder=0
nameOfSecondFolder=0
nameOfFile=0
while [ $nameOfFolder -lt 50 ]
do
	mkdir $directory/$nameOfFolder
	while [ $nameOfSecondFolder -lt 100 ]
	do
		mkdir $directory/$nameOfFolder/$nameOfSecondFolder
		while [ $nameOfFile -lt 200 ]
		do
			touch $directory/$nameOfFolder/$nameOfSecondFolder/$nameOfFile
			nameOfFile=$(( $nameOfFile+1 ))
		done
		nameOfFile=0
		nameOfSecondFolder=$(( $nameOfSecondFolder+1 ))
	done
nameOfSecondFolder=0
nameOfFolder=$(( $nameOfFolder+1 ))
done

