#/bin/bash

MOAB_PATH=$HOME/opt/new_moab/
MOAB_LIBRARY=$MOAB_PATH"/lib"
MOAB_INCLUDE=$MOAB_PATH"/include"

echo $MOAB_LIBRARY

g++ convert.cpp -std=c++11 -I$MOAB_INCLUDE -L$MOAB_LIBRARY -lMOAB -o convert
