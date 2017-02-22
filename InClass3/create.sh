#!/bin/bash
# Created by Bowei Zhao
# Date: 10/6/2015
# ECE 2524 Intro to Unix 
# In Class Assignment 3 
if [ $# -eq "1" ]; ## if you passed in an argument and only just one then. 
then
	echo -e "\nYou passed in argument: ./$1 \n"
	if [ ! -d $1 ]; # if the argument folder doesn't exist. Then run these commands
	then
		echo -e "\n./$1 Parent Dir doesn't exist, making Parent Directory NOW\n" # since arg folder doesn't exist make it
		mkdir $1 # making folder of argument 1
			if [ ! -d ./$1/src ]; # checks to see if there is a folder in arg1 called src
			then
				echo -e "./$1/src --- Dir doesn't exist, making Directory NOW --- "
				mkdir ./$1/src
			else
				echo -e "./$1/src Dir exists. No change"
			fi

			if [ ! -d ./$1/build ]; # checks to see if there is a folder in arg1 called build
			then
				echo -e "./$1/build --- Dir doesn't exist, making Directory NOW --- "
				mkdir ./$1/build
			else
				echo -e "./$1/build Dir exists. Doing nothing"
			fi

			if [ ! -d ./$1/test ]; # checks to see if there is a folder in arg1 called test
			then
				echo -e "./$1/test --- Dir doesn't exist, making Directory NOW --- "
				mkdir ./$1/test
			else
				echo -e "./$1/test Dir exists. Doing nothing"
			fi
	else
		echo -e "\n./$1 Parent Dir exists. Checking to see if subfolders exist now\n"
		if [ ! -d ./$1/src ]; # checks to see if there is a folder in arg1 called src
		then
			echo -e "./$1/src --- Dir doesn't exist, making Directory NOW --- "
			mkdir ./$1/src
		else
			echo -e "./$1/src Dir exists. Doing nothing"
		fi

		if [ ! -d ./$1/build ]; # checks to see if there is a folder in arg1 called build
		then
			echo -e "./$1/build --- Dir doesn't exist, making Directory NOW --- "
			mkdir ./$1/build
		else
			echo -e "./$1/build Dir exists. Doing nothing"
		fi

		if [ ! -d ./$1/test ]; # checks to see if there is a folder in arg1 called test
		then
			echo -e "./$1/test --- Dir doesn't exist, making Directory NOW --- "
			mkdir ./$1/test
		else
			echo -e "./$1/test Dir exists. Doing nothing"
		fi

	fi
else
	echo -e "\nYou passed in no arguments. Making folders in current directory\n"

	if [ ! -d ./src ]; # checks to see if there is a folder in arg1 called src
	then
		echo -e "./src --- Dir doesn't exist, making Directory NOW --- "
		mkdir ./src
	else
		echo -e "./src Dir exists. Doing nothing"
	fi

	if [ ! -d ./build ]; # checks to see if there is a folder in arg1 called build
	then
		echo -e "./build --- Dir doesn't exist, making Directory NOW --- "
		mkdir ./build
	else
		echo -e "./build Dir exists. Doing nothing"
	fi

	if [ ! -d ./test ]; # checks to see if there is a folder in arg1 called test
	then
		echo -e "./test --- Dir doesn't exist, making Directory NOW --- "
		mkdir ./test
	else
		echo -e "./test Dir exists. Doing nothing"
	fi

fi
