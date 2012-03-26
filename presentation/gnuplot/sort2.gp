#!/usr/bin/gnuplot

#input
set datafile separator ";"

#output
set key top left
set style data lines
set grid

set xlabel 'Number of threads'
set yrange [0:18]
set ylabel 'Executions time [s]'

set terminal png transparent nocrop medium size 800,400
set output 'sort2.png'

plot \
'-' using 1:($2) title 'Serial'         axes x1y1 lt rgb 'black' lw 2, \
'-' using 1:($2) title 'openMP'         axes x1y1 lt rgb 'red' lw 2, \
'-' using 1:($2) title 'intel TBB'      axes x1y1 lt rgb 'dark-blue' lw 2, \
'-' using 1:($2) title 'cusom openMP threashold' axes x1y1 lt rgb 'steelblue' lw 2, \
'-' using 1:($2) title 'cusom openMP deep'       axes x1y1 lt rgb 'olivedrab' lw 2, \
'-' using 1:($2) title 'custom QtConcurrent'     axes x1y1 lt rgb 'orangered' lw 2
1;0.29
2;0.29
3;0.29
4;0.29
5;0.29
6;0.29
7;0.29
8;0.29
9;0.29
10;0.29
e
1;0.29
2;0.16
3;0.11
4;0.82
5;0.7
6;0.59
7;0.66
8;0.6
9;0.56
10;0.51
e
1;0.29
2;0.18
3;0.13
4;0.69
5;0.94
6;0.87
7;0.83
8;0.8
9;0.84
10;0.82
e
1;14.32
2;11.67
3;6.61
4;5.69
5;5.64
6;4.24
7;3.71
8;3.56
9;3.76
10;3.18
e
1;17.62
2;8.64
3;5.92
4;4.45
5;4.07
6;3.18
7;3.12
8;3.11
9;3.05
10;3.1
e
1;17.39
2;8.91
3;7.93
4;5.74
5;4.64
6;4.19
7;3.97
8;4.68
9;4.85
10;4
e
