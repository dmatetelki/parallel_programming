#!/usr/bin/gnuplot

#input
set datafile separator ";"

#output
set key top left
set style data lines
set grid

set xlabel 'Number of threads'
set yrange [0:0.8]
set ylabel 'Executions time [s]'

set terminal png transparent nocrop medium size 800,400
set output 'reduce.png'

plot \
'-' using 1:($2) title 'Serial'         axes x1y1 lt rgb 'black' lw 2, \
'-' using 1:($2) title 'openMP'         axes x1y1 lt rgb 'red' lw 2, \
'-' using 1:($2) title 'intel TBB'      axes x1y1 lt rgb 'dark-blue' lw 2, \
'-' using 1:($2) title 'QtConcurrent'   axes x1y1 lt rgb 'dark-green' lw 2
1;0.67
2;0.67
3;0.61
4;0.68
5;0.59
6;0.7
7;0.67
8;0.7
9;0.65
10;0.68
e
1;0.52
2;0.27
3;0.19
4;0.15
5;0.15
6;0.15
7;0.22
8;0.2
9;0.17
10;0.16
e
1;0.68
2;0.35
3;0.35
4;0.18
5;0.18
6;0.18
7;0.19
8;0.18
9;0.18
10;0.15
e
1;0.25
2;0.18
3;0.15
4;0.15
5;0.15
6;0.17
7;0.17
8;0.16
9;0.17
10;0.17
e

