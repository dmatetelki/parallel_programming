#!/usr/bin/gnuplot

#input
set datafile separator ";"

#output
set key top left
set style data lines
set grid

set xlabel 'Number of threads'
set yrange [0:6.5]
set ylabel 'Executions time [s]'

set terminal png transparent nocrop medium size 800,400
set output 'map.png'

plot \
'-' using 1:($2) title 'Serial'         axes x1y1 lt rgb 'black' lw 2, \
'-' using 1:($2) title 'openMP'         axes x1y1 lt rgb 'red' lw 2, \
'-' using 1:($2) title 'intel TBB'      axes x1y1 lt rgb 'dark-blue' lw 2, \
'-' using 1:($2) title 'QtConcurrent'   axes x1y1 lt rgb 'dark-green' lw 2
1;0.5
2;0.67
3;0.68
4;0.69
5;0.68
6;0.7
7;0.65
8;0.72
9;0.68
10;0.69
e
1;6.12
2;3.41
3;2.12
4;1.61
5;1.27
6;1.59
7;1.17
8;1.38
9;0.97
10;0.87
e
1;6.25
2;3.45
3;3.17
4;1.62
5;1.6
6;1.6
7;1.6
8;1.51
9;1.66
10;1.32
e
1;3.22
2;2.2
3;1.65
4;1.32
5;1.43
6;1.44
7;0.95
8;0.9
9;0.85
10;0.8
e

