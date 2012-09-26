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
	    mv -v {genericCharacter,$1}.cc
	    mv -v {genericCharacter,$1}.h
	    mv -v genericCharacter/{genericCharacter,$1}.ch
	    mv -v {genericCharacter,$1}
	    git rm -r genericCharacter{.cc,.h,/} 
	    git add $1{.cc,.h,/} charlist.h CMakeLists.txt player.cc
          else
	    echo "Please make sure the character name is unique."
        fi
      else
        echo 	"This probably won't break anything if you use it from \
	       	the GUFG directory root on the alpha-generic branch."
    fi
fi
