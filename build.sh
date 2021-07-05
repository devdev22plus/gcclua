#!/bin/bash

# gcc -o test main.cpp -I./lua52/include/ -L./lua52/ ./lua52/liblua.a
# gcc -o test main.cpp -I./lua52/include/ -L./lua52/ -l:./lua52/liblua52.a
# gcc -o test main.cpp -I./lua54/include/ -L./lua54/ -l./lua54/liblua.a
# g++ -o test main.cpp -lstdc++ -std=c++11 -I./lua54/include/ -L./lua54/ -llua -lm

if [ -z "$1" ]
then
	echo "please enter platform name";
	exit;
fi

if [[ "$1" == 'macosx' ]];
then
	# work on macosx
	gcc -o test main.cpp -lstdc++ -std=c++11 -I./lua54/include/ -L./lua54/ -llua -lm -I./redisclient/src -L./redisclient/lib/mac/
	# gcc -o test main.cpp -lstdc++ -std=c++11 -I./lua54/include/ -L./lua54/ -llua -lm -I./redisclient/src -L./redisclient/lib/mac/ -lhiredis
elif [[ "$1" == 'linux' ]];
then
	# work on linux
	gcc -o test main.cpp -lstdc++ -std=c++11 -I./lua54/include/ -L./lua54/ -llua -lm -Wl,-E -ldl -lreadline 
elif [[ "$1" == 'windows' ]];
then
	echo 'windows soon';
else
	echo "unknow platform support";
fi


