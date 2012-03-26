#!/usr/bin/gnuplot

#input
set datafile separator ";"

#output
set key top left
# set style data lines
set grid

set xlabel 'X'
set yrange [0:0.383]

set ylabel 'Y'
set xrange [-4:4]

set terminal png transparent nocrop medium size 200,200
set output '1d_gauss.png'

plot \
'-' using 1:($2) title '1D discrete gaussian filter' axes x1y1 lt rgb 'blue' lw 2
-4;0
-3;0.006
-2;0.061
-1;0.242
0;0.383
1;0.242
2;0.061
3;0.006
4;0
e