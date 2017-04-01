#!/bin/bash

clear
txtgrn=$(tput setaf 2) # Green
txtrst=$(tput sgr0) # Text reset

if [ -n "$1" ] 
then
	echo "......................................."
	echo "..........Cleaning on progress........."
	echo "......................................."
else
	echo "......................................."
	echo "...........Building on progess........."
	echo "......................................."
fi

make -f GCCdebug $1

	echo "########################################"
	echo "########################################"
	echo "########################################"

if [ ! -n "$1" ]
then
echo "${txtgrn} Enter the name of input parameter file: ${txtrst}"
read FILE
#echo "${txtgrn} Enter the number of problem:  ${txtrst}" 
#read PROB

        echo "########################################"
	echo "###  Preparing to run the executable ###"
	echo "########################################"
	echo ".......Executing Nusifsolver-GCC........"
	echo "########################################"

rm -rf *.txt *.dat results/ streakline/
 
mkdir results
mkdir streakline

#valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./NusifSolver-GCC $FILE #>info.txt
./NusifSolver-GCC $FILE #>info.txt  

#matlab -nosplash -nodesktop -r plotparticle 



else
	echo "########################################"
fi
 


 

