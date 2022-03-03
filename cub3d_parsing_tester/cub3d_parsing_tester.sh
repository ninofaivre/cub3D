#!/bin/bash

OK="\U2705"
KO="\U274C"

C_RESET="\e[0m"
C_PURPLE="\e[34m"
C_RED="\e[31m"
C_GREEN="\e[32m"

echo -n -e "${C_RESET}"

function	calc_note
{
	if [ $1  -eq "1" ]; then
		echo "$(($(($2==0)) + $(($3==0)) + $(($4==0))))"
	elif [ $1 -eq "0" ]; then
		echo "$(($(($2==1)) + $(($3==1)) + $(($4==0))))"
	fi
}

function	print_first_line
{
	note="$(calc_note $2 $3 $4 $5)"
	echo -n -e "test $6 : [$1]   "
	if [ $note -eq "3" ]; then
		echo -e "${C_GREEN}Good${C_RESET}"
	elif [ $note -eq "2" ]; then
		echo -e "${C_PURPLE}OK${C_RESET}"
	elif [ $note -eq "1" ]; then
		echo -e "${C_RED}BAD${C_RESET}"
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
	if [ $4 -eq "1" ]; then
		echo -e -n "${C_RESET}Valgrind Error "
	fi
	if ([ $4 -eq "1" ] && [ $5 -eq "0" ]); then
		echo -e "$OK"
	elif [ $4 -eq "1" ]; then
		echo -e "$KO"
	fi
}

test_file_list=$(/bin/ls -l test_file | tail -n +2 | awk '{ print $9 }')
test_id=0
if ([ $# -gt "0" ] && [ $1 = "-valgrind" ]); then
	is_valgrind_option=1
else
	is_valgrind_option=0
fi

for test_file in $test_file_list; do
	if [ $test_id -ne "0" ]; then
		echo
	fi
	test_id=$(($test_id + 1))
	result_execution=$(../cub3D ./test_file/$test_file 2>&1)
	../cub3D ./test_file/$test_file 2>/dev/null 1>/dev/null
	exit_status=$?
	if [ $is_valgrind_option -eq "1" ]; then
		valgrind_error=$(valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ../cub3D ./test_file/$test_file 2>&1 | awk 'END {print $4}')
	else
		valgrind_error=0
	fi
	is_error_printed=$(echo $result_execution | grep -c "^Error")
	is_valid_test_file=$(echo "$test_file" | grep -c "^valid_")
	print_first_line $test_file $is_valid_test_file $exit_status $is_error_printed $valgrind_error $test_id
	print_details $is_valid_test_file $exit_status $is_error_printed $is_valgrind_option $valgrind_error
done
