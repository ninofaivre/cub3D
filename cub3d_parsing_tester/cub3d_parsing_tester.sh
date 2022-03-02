#!/bin/bash

OK="\U2705"
KO="\U274C"
C_RESET="\e[0m"

function	calc_note
{
	if [ $1  -eq "1" ]; then
		echo "$(($(($2==0)) + $(($3==0))))"
	elif [ $1 -eq "0" ]; then
		echo "$(($(($2==1)) + $(($3==1))))"
	fi
}

function	print_first_line
{
	note="$(calc_note $2 $3 $4)"
	echo -n -e "${C_RESET}test $5 : [$1]   "
	if [ $note -eq "2" ]; then
		echo -e "\e[32mGood"
	elif [ $note -eq "1" ]; then
		echo -e "\e[34mOK"
	elif [ $note -eq "0" ]; then
		echo -e "\e[31mBAD"
	fi
}

function	print_details
{
	echo -e -n "${C_RESET}Exit Status "
	if ([ $1 -eq "1" ] && [ $2 -eq "0" ]) || ([ $1 -eq "0" ] && [ $2 -eq "1" ]); then 
		echo -e "$OK"
	else
		echo -e "$KO"
	fi
	echo -e -n "${C_RESET}Print Error "
	if ([ $1 -eq "1" ] && [ $3 -eq "0" ]) || ([ $1 -eq "0" ] && [ $3 -ne "0" ]); then
		echo -e "$OK"
	else
		echo -e "$KO"
	fi
}

test_file_list=$(/bin/ls -l test_file | tail -n +2 | awk '{ print $9 }')
test_id=0

for test_file in $test_file_list; do
	if [ $test_id -ne "0" ]; then
		echo
	fi
	test_id=$(($test_id + 1))
	result_execution=$(../cub3D test_map/$test_file 2>&1)
	exit_status=$?
	is_error_printed=$(echo $result_execution | grep -c "^Error")
	is_valid_test_file=$(echo $test_file | grep -c "^valid_")
	print_first_line $test_file $is_valid_test_file $exit_status $is_error_printed $test_id
	print_details $is_valid_test_file $exit_status $is_error_printed
done
