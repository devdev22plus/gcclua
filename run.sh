#!/bin/bash


if [ -z "$1" ]
then
	echo "please enter platform name";
	exit;
fi

./build.sh $1
./test

