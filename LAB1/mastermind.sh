#!/bin/bash
# Created by Bowei Zhao
# Date: 10/6/2015
# ECE 2524 Intro to Unix 
# LAB1 Mastermind

clear
rand_fun()
{
	for ((i = 0 ; i < 4 ; i++ )); do
		vari=$(( $RANDOM % 6 ));
		if [ "$vari" == 0 ]; 
		then
			vari='#'
		elif [ "$vari" == 1 ];
		then
			vari='$'
		elif [ "$vari" == 2 ];
		then
			vari='%'
		elif [ "$vari" == 3 ];
		then
			vari='&'
		elif [ "$vari" == 4 ];
		then
			vari='*'
		elif [ "$vari" == 5 ];
		then
			vari='@'
		else
			vari='@'
		fi
		ARRAY[i]=$vari
		#echo -e "${ARRAY[i]}"
	done
}


start_game(){
	#set $(printf %x 65)
	#printf "\x$1"
	rand_fun
	echo -e "${ARRAY[*]}"

}
echo -e "Welcome to MASTERMIND: The Game! \n"
echo -e "This is a text based version of the game run through a Linux Terminal \n"
echo -e "Created by: Bowei Zhao ECE2524 Unix FALL 2015\r\n"
echo -e "Instructions: \n"
echo -e "****************** Ready Player One ****************** \n1.Select Start to start the Game \r\n"
echo -e "2.A secret code will be created from 4 symbols of 6 represented by # $ % & * @\r\n "
echo -e "3.Guess by typing those characters into your keyboard and pressing enter to finalize your answer \r\n"
echo -e "4.You have 10 guess to get it right or else it is game over\r\n"
echo -e "5.Clues will be given in the form of X and O where X represents a correct symbol in the correct location"
echo -e "  O represents a correct symbol given but in the wrong location.\r\n"
echo -e "6.Symbols may be repreated.\r\n"
echo -e "****************** INSERT COIN TO CONTINUE ******************** \r\n"

while true; do
    read -p "Insert Coin (y/n)?" yn
    case $yn in
        [Yy]* ) start_game; break;;
        [Nn]* ) exit;;
        * ) echo "Please answer yes or no.";;
    esac
done