#!/bin/bash

if [ $1 ]; then
    SOURCE_FOLDER="../source"
    RENDU_PATH="../source/rendu1.x"

    cp "Makefile" $SOURCE_FOLDER
    make clean
    make -C $SOURCE_FOLDER depend
    make -C $SOURCE_FOLDER
    cp $RENDU_PATH "."

fi

if [ -f "rendu1.x" ];
then

    i=1
    while [ $i -le 6 ]
    do
        echo "Running E$i.txt!"
        "./"rendu1.x Error "E$i.txt" >> "out_E$i.txt"
        let "i++"
        echo "Done!"
    done

    j=1
    while [ $j -le 3 ]
    do
        echo "Running F$j.txt!"
        "./"rendu1.x Force "F$j.txt" >> "out_F$j.txt"
        let "j++"
        echo "Done!"
    done


else
    echo "File rendu1.x does not exists. Please compile with -c first"
fi



