#!/bin/bash

g++ -Wall -Werror -std=c++17 -g *.cpp -o lab5

./lab5 ./inputFiles/in1.txt > ./outputFiles/out99.txt
#for i in {1..2}
#do
	#./lab5 ./inputFiles/in$i.txt > ./outputFiles/out$i.txt

	#printf "===============CHECK FOR $i TEST FILE================\n"

	#printf "==========INPUT FILE FOR $i FILE===========\n\n"
	#cat ./inputFiles/in1.txt
	#printf "\n"

	#printf "=====MY OUTPUT FILE=====\n\n"
	#cat ./outputFiles/out99.txt
	#printf "\n"

	#printf "=====ANSWER=====\n\n"
	#cat ./answers/out$i.txt
	#printf "\n"

	#*diff ./outputFiles/out$i.txt ./answers/out$i.txt

	#printf "\n\n"
#done
