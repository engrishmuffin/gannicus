#!/bin/bash

if [[ $1 == "" ]]
  then
    echo "Please supply a character name as an argument."
  else
    echo "New name will be \"$1\". Press enter to continue"
    read
    if [[ $(git symbolic-ref --short HEAD) == "alpha-generic" ]] 
      then	
        if git checkout -b alpha-$1;
          then
            for source in   src/charlist.h \
	          	    src/characters/genericCharacter.cc \
			    src/characters/genericCharacter.h \
			    genericCharacter/genericCharacter.ch \
			    src/engine/player.cc \
			    CMakeLists.txt
	      do sed -i {s#genericCharacter#$1#g} $source
	    done
	    capsName=$(tr 'a-z' 'A-Z' <<< $1) 
	    sed -i "s#GENERIC#$capsName#g" genericCharacter.h
	    git mv -v src/characters/{genericCharacter,$1}.cc
	    git mv -v src/characters/{genericCharacter,$1}.h
	    git mv -v genericCharacter/{genericCharacter,$1}.ch
	    git mv -v {genericCharacter,$1}
          else
	    echo "Please make sure the character name is unique."
        fi
      else
        echo 	"This probably won't break anything if you use it from \
	       	the GUFG directory root on the alpha-generic branch."
    fi
fi
