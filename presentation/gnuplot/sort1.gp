#!/usr/bin/gnuplot

#input
set datafile separator ";"

#output
set key top left
set style data lines
set grid

set xlabel 'Number of threads'
set yrange [0:3.5]
set ylabel 'Executions time [s]'

set terminal png transparent nocrop medium size 800,400
set output 'sort1.png'

plot \
'-' using 1:($2) title 'Serial'         axes x1y1 lt rgb 'black' lw 2, \
'-' using 1:($2) title 'openMP'         axes x1y1 lt rgb 'red' lw 2, \
'-' using 1:($2) title 'intel TBB'      axes x1y1 lt rgb 'dark-blue' lw 2
1;2.33
2;3.39
3;3.05
4;3.19
5;2.98
6;2.99
7;3.15
8;3.24
9;3.09
10;2.99
e
1;3.04
2;1.6
3;1.66
4;0.84
5;0.71
6;0.65
7;0.7
8;0.61
9;0.56
10;0.51
e
1;3.33
2;1.81
3;1.32
4;1.7
5;1.26
6;0.89
7;0.87
8;0.83
9;0.81
10;0.82
e