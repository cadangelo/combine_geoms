#/bin/bash

MOAB_PATH=$HOME/opt_n/moab/
MOAB_LIBRARY=$MOAB_PATH"/lib"
MOAB_INCLUDE=$MOAB_PATH"/include"

echo $MOAB_LIBRARY

g++ combine.cpp -std=c++11 -I$MOAB_INCLUDE -L$MOAB_LIBRARY -lMOAB -o combine

