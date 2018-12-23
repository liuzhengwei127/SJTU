#!/bin/bash

function print_usage() {
	echo -e "\033[1;37mHomework 15: Trie\033[0m"
	echo
	echo -e "\033[4;37mUsage:\033[0m"
	echo -e "  \033[32m./handin.sh -id {Your Student ID}\033[0m"
	echo
	echo -e "\033[4;37mExample:\033[0m"
	echo -e "  \033[34m./handin.sh -id 515030910477\033[0m"
}

case $1 in
-id)
	tar -zcvf hw15_$2.tar.gz hw15.cpp trie.h dict.h grade.sh
	echo -e "\033[34mhw15_$2.tar.gz created. Please submit to the course website.\033[0m"
	;;
--help | -h | *)
	print_usage
	exit
	;;
esac
