#!/bin/bash
if [ $1 ]; then
    SOURCE_FOLDER="../source"
    RENDU_PATH="../source/rendu2.x"

    cp "Makefile" $SOURCE_FOLDER
    make clean
    make -C $SOURCE_FOLDER depend
    make -C $SOURCE_FOLDER
    cp $RENDU_PATH "."
fi



if [ -f "rendu2.x" ];
then
    j=1
    while [ $j -le 3 ]
    do
        echo "Running I$j.txt!"
        "./"rendu2.x Integration "I$j.txt" >> "out_I$j.txt"
        let "j++"
        echo "Done!"
    done

else
    echo "File rendu2.x does not exists. Please compile with -c first"
fi