#!/bin/bash

assertParametrized() {
	: "${!1:? "No new character name given, aborting."}"
}

assertParametrized 1
echo "New name will be \"$1\". Press enter to continue"
read

if [[ -e genericCharacter/genericCharacter.ch ]] 
then	
	for source in   charlist.h \
			genericCharacter.cc \
			genericCharacter.h \
			genericCharacter/genericCharacter.ch \
			player.cc \
			CMakeLists.txt
		do sed -i {s#genericCharacter#$1#g} $source
	done
	capsName=$(tr 'a-z' 'A-Z' <<< $1) 
	sed -i "s#GENERIC#$capsName#g" genericCharacter.h
	git mv -v {genericCharacter,$1}.cc
        git mv -v {genericCharacter,$1}.h
	git mv -v genericCharacter/{genericCharacter,$1}.ch
	git mv -v {genericCharacter,$1}	
else
t 	echo "This probably won't break anything if you use it from the GUFG directory root."
	
fi
