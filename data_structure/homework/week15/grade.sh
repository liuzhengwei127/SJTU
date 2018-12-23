#!/bin/bash

rm -f hw15

if [ -f hw15.cpp ]; then
	g++ hw15.cpp -std=c++17 -O2 -o hw15
else
	echo "hw15.cpp not found"
	echo -e "\033[1;37mHomework 15: Trie\033[0m score: 0 / 100"
	exit 1
fi

score=0
for trace in $(ls traces); do
	res=($(./hw15 <traces/$trace))
	ans=($(tail -1 traces/$trace))
	if [[ ${res[@]} == ${ans[@]} ]]; then
		score=$(($score + 10))
		echo -e "$trace......\033[32mPassed\033[0m"
	else
		echo "-------"
		echo "$trace"
		echo "Your answer: ${res[@]}"
		echo "Standard answer: ${ans[@]}"
		echo "-------"
		echo -e "$trace......\033[31mFailed\033[0m"
	fi
done

echo -e "\033[1;37mHomework 15: Trie\033[0m score: $score / 100"
