#!/bin/bash

QT_PRO="parallel.pro"
SRC_DIR="../qtconcurrent"
CXX_FLAGS="-Wall -Wextra  -O3 -ffast-math -fwhole-program -fomit-frame-pointer -march=native"

echo "Generating qmake project file: $QT_PRO ..."

cat > $QT_PRO <<_EOF_
config_map {
  TEMPLATE      = app
  QT            = core
  QMAKE_CXX = /usr/lib/colorgcc/bin/g++
  QMAKE_CXXFLAGS      = $CXX_FLAGS
  TARGET        = qt_map
  SOURCES       = $SRC_DIR/qt_map.cpp
}

config_sort {
  TEMPLATE      = app
  QT            = core
QMAKE_CXX = /usr/lib/colorgcc/bin/g++
  QMAKE_CXXFLAGS      = $CXX_FLAGS
  TARGET        = qt_sort
  INCLUDEPATH  += $SRC_DIR
  SOURCES       = $SRC_DIR/qt_sort.cpp
}

config_reduce {
  TEMPLATE      = app
  QT            = core
  QMAKE_CXX = colorgcc
  QMAKE_CXXFLAGS      = $CXX_FLAGS
  TARGET        = qt_reduce
  SOURCES       = $SRC_DIR/qt_reduce.cpp
}

_EOF_


