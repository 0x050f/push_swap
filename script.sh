#!/bin/bash
testing() {
	result_push_swap=$(./push_swap $str);
	nb_char=$(printf "$result_push_swap" | wc -m);
	if [ $nb_char -ne 0 ]; then
		result_checker=$(printf "$result_push_swap\n" | ./checker $str);
	else
		result_checker=$(printf "$result_push_swap" | ./checker $str);
	fi
	if [ "$result_push_swap" != "" ]; then
		nb_instr=$(printf "$result_push_swap\n" | wc -l | xargs);
	else
		nb_instr=0;
	fi
	if [ "$result_push_swap" = "Error" ] || [ "$result_push_swap" = "" ]; then
		printf "\e[33mpush_swap output\e[0m: \"$result_push_swap\" ❔";
	else
		printf "\e[33mnb_instr\e[0m: $nb_instr ✅";
	fi
	printf "\n"
	printf "\e[33mchecker output\e[0m: \"$result_checker\" ";
	if [ "$result_checker" = "OK" ]; then
		printf "✅";
	elif [ "$result_checker" = "KO" ]; then
		printf "❌";
	else
		printf "❔";
	fi
	printf "\n";
}

create_string() {
	str="${array[0]}";
	for ((i=1 ; $i < $1 ; i++)); do
		str="${str} ${array[$i]}"
	done
}

shuffle() {
	local i tmp size max rand;

	# $RANDOM % (i+1) is biased because of the limited range of $RANDOM
	# Compensate by using a range which is a multiple of the array size.
	size=${#array[*]};
	if [ "$1" -gt 0 ]; then
		max=$(( 32768 / size * size ));
	fi

	for ((i=size-1; i>0; i--)); do
		while (( (rand=$RANDOM) >= max )); do :; done
			rand=$(( rand % (i+1) ));
			tmp=${array[i]} array[i]=${array[rand]} array[rand]=$tmp;
	done
}

fill_array() {
	for ((i=0; $i < $1; i++)); do
		array[$i]=$i;
	done
}

check_parameters() {
	re='^[0-9]+$'
	if ! [[ $1 =~ $re ]]; then
		echo "size_array must be positive number" >&2; exit 1;
	elif ! [[ $2 =~ $re ]]; then
		echo "nb_test must be positive number" >&2; exit 1;
	fi
}

check_nb_parameters() {
	if [ "$1" -ne 1 ] && [ "$1" -ne 2 ]; then
		printf "$0 size_array [nb_test]\n";
		exit 1;
	fi
}

check_programs() {
	if ! command -v ./push_swap &> /dev/null; then
	    echo "./push_swap could not be found" >&2; exit 1;
	elif ! command -v ./checker &> /dev/null; then
	    echo "./checker could not be found" >&2; exit 1;
	fi
}

main() {
	local n nb;

	check_programs;
	check_nb_parameters $#;
	if [ "$#" -eq 1 ]; then
		nb=1;
	else
		nb=$2;
	fi
	check_parameters $1 $nb;

	declare -a array
	fill_array $1;

	for ((n=0; n<nb; n++)); do
		shuffle $1
		create_string $1

		printf "\e[33mparameters\e[0m: $str\n";
		testing
		printf "\e[34m====================\e[0m\n"
	done
}

main $1 $2;
