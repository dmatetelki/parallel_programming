#!/bin/bash

CC="/usr/lib/colorgcc/bin/g++"
CC_OPTIONS="-Wall -Wextra -pedantic -Wshadow -Weffc++"
CC_OPTIMIZE_OPTIONS="-O3 -ffast-math -fwhole-program -fomit-frame-pointer -march=native"
CC_LIBS="-lrt"
CC_OPENMP="-fopenmp"
CC_ITBB="-ltbb"

BUILD_DIR="../build"
SERIAL_SRC="../serial"
ITBB_SRC="../itbb"
OPENMP_SRC="../openMP"

echo "CC: $CC"
echo "CC options: $CC_OPTIONS"
echo "CC optimalization options: $CC_OPTIMIZE_OPTIONS"
echo "CC libs: $CC_LIBS"
echo "CC openMP options: $CC_OPENMP"
echo "CC intel TBB options: $CC_ITBB"

rm -rf $BUILD_DIR
mkdir $BUILD_DIR
cd $BUILD_DIR

echo -e "\nSerial algorithms..."
for serial in  $(ls $SERIAL_SRC/serial*.cpp)
do
  BASENAME=`basename $serial`
  echo "Compiling $BASENAME ..."
  $CC $serial $CC_OPTION $CC_OPTIMIZE_OPTIONS $CC_LIBS -o $BUILD_DIR/${BASENAME%\.*}
done

echo -e "\nopenMP algorithms..."
for openMP in  $(ls $OPENMP_SRC/openMp*.cpp)
do
  BASENAME=`basename $openMP`
  echo "Compiling $BASENAME ..."
  $CC $openMP $CC_OPTION $CC_OPTIMIZE_OPTIONS $CC_LIBS $CC_OPENMP -o $BUILD_DIR/${BASENAME%\.*}
done

echo -e "\nIntel Thrad Building Blocks algorithms..."
for itbb in  $(ls $ITBB_SRC/itbb*.cpp)
do
  BASENAME=`basename $itbb`
  echo "Compiling $BASENAME ..."
  $CC $itbb $CC_OPTION $CC_OPTIMIZE_OPTIONS $CC_LIBS $CC_ITBB -o $BUILD_DIR/${BASENAME%\.*}
done

echo -e "\nGenerating QT project file & compilin QT algorithms ..."
../scripts/gen_qt_pro.sh

#  NOTE does not work yet
qmake parallel.pro -config config_map
make
qmake parallel.pro -config config_sort
make
qmake parallel.pro -config config_reduce
make


