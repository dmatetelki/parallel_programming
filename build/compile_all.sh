#!/bin/bash

CC="/usr/lib/colorgcc/bin/g++"
CC_OPTIONS="-Wall -Wextra -pedantic -Wshadow -Weffc++"
CC_OPTIMIZE_OPTIONS="-O3 -ffast-math -fwhole-program -fomit-frame-pointer -march=native -m64"
CC_LIBS="-lrt"
CC_OPENMP="-fopenmp"
CC_ITBB="-ltbb"
QT_PRO="qtconcurrent.pro"

echo "CC: $CC"
echo "CC options: $CC_OPTIONS"
echo "CC optimalization options: $CC_OPTIMIZE_OPTIONS"
echo "CC libs: $CC_LIBS"
echo "CC openMP options: $CC_OPENMP"
echo "CC intel TBB options: $CC_ITBB"

echo -e "\nSerial algorithms:" 
for serial in  $(ls serial*.cpp)
do
	echo "Compiling $serial ..."
	$CC $serial $CC_OPTION $CC_OPTIMIZE_OPTIONS $CC_LIBS -o ${serial%\.*}
done

echo -e "\nopenMP algorithms:"
for openMP in  $(ls openMp*.cpp)
do
	echo "Compiling $openMP ..."
	$CC $openMP $CC_OPTION $CC_OPTIMIZE_OPTIONS $CC_LIBS $CC_OPENMP -o ${openMP%\.*}
done

echo -e "\nintel TBB algorithms:"
for itbb in  $(ls itbb*.cpp)
do      
	echo "Compiling $itbb ..."
	$CC $itbb $CC_OPTION $CC_OPTIMIZE_OPTIONS $CC_LIBS $CC_ITBB -o ${itbb%\.*}
done

echo -e "\nQt Concurrent algorithms:"
echo "Generating qmake project file ..."

QT_PRO_CONTENT=$( cat <<EOF
config_map {
	TEMPLATE = app
	SOURCES = QT_map.cpp
	TARGET = QT_map
}
EOF
) 
echo $QT_PRO_CONTENT > $QT_PRO
