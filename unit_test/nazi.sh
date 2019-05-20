#!/bin/sh

function retCheck() {
	if [ ! $? -eq 0 ]
	then
		echo "\033[38;5;118m--- 𝔤𝔬𝔬𝔡 𝔤𝔢𝔯𝔪𝔞𝔫 ---\033[0m"
	else
		echo "\033[38;5;196m--- 𝖓𝖊𝖎𝖓 ---\033[0m"
	fi
	echo
}

function grepStuff() {
	export IFS=$'\n'
	val=1
	for file in $(find . -type f -name '*.c')
	do
		if [ ! $(grep -l $1 $file) = "" ]
		then
			echo "\033[38;5;69mPossible norme error in: $(grep -l $1 $file)\033[0m"
			echo "Ligne $(grep -n $1 $file)"
			val=0
		fi
	done
	return $val
}

function grepStuff2() {
	export IFS=$'\n'
	val=1
	for file in $(find . -type f -name '*.c')
	do
		if [ ! $(grep $1 $file | grep -v include) = "" ]
		then
			echo "\033[38;5;69mPossible norme error in: $(grep -ln $1 $file)\033[0m"
			echo "Ligne $(grep -n $1 $file | grep -v include)"
			val=0
		fi
	done
	return $val
}

echo "\033[38;5;196m=====\033[0m 卐 卐 SUPER NAZI SCRIPT V39.45 卐 卐 \033[38;5;196m=====\033[0m"
echo "=== Assignation ==="
grepStuff "\=$"; retCheck
echo "+++ Addition +++"
grepStuff "\+$"; retCheck
echo "*** Multiplication ***"
grepStuff "\*$"; retCheck
echo "--- Soustraction ---"
grepStuff "\-$"; retCheck
echo "::: Division :::"
grepStuff "\ \/$"; retCheck
echo "&&& Et binaire &&&"
grepStuff "\&$"; retCheck
echo "||| Ou binaire |||"
grepStuff "\|$"; retCheck
echo "%%% Modulo %%%"
grepStuff "\%$"; retCheck
echo "??? Ternaire ???"
grepStuff "\?$"; retCheck
echo "::: Ternaire :::"
grepStuff "\:$"; retCheck
echo "<<< Comparisons <<<"
grepStuff "\<$"; retCheck
echo ">>> Comparisons >>>"
grepStuff2 '>$'; retCheck
echo '!!! Comparisons !!!'
grepStuff '\!$'; retCheck