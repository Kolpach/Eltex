#!/bin/bash
directory=$1
maxFirstFolders=$2
maxSecondFolders=$3
maxFiles=$4
nameOfFolder=0
nameOfSecondFolder=0
nameOfFile=0

while [ $nameOfFolder -lt $maxFirstFolders ]
do
	mkdir $directory/$nameOfFolder
	while [ $nameOfSecondFolder -lt $maxSecondFolders ]
	do
		mkdir $directory/$nameOfFolder/$nameOfSecondFolder
		while [ $nameOfFile -lt $maxFiles ]
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

