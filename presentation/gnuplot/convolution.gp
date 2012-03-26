#!/usr/bin/gnuplot

#input
set datafile separator ";"

#output
set key top left
set style data lines
set grid

set xlabel 'Number of threads'
set yrange [0:0.53]
set ylabel 'Executions time [s]'

set terminal png transparent nocrop medium size 800,400
set output 'convolution.png'

plot \
'-' using 1:($2) title 'Serial'                axes x1y1 lt rgb 'black' lw 2, \
'-' using 1:($2) title 'Serial - optimized'    axes x1y1 lt rgb 'red' lw 2, \
'-' using 1:($2) title 'intel TBB'             axes x1y1 lt rgb 'dark-blue' lw 2, \
'-' using 1:($2) title 'intel TBB - optimized' axes x1y1 lt rgb 'dark-green' lw 2
1;0.33
2;0.33
3;0.33
4;0.33
5;0.33
6;0.33
7;0.33
8;0.33
9;0.33
10;0.33
e
1;0.25
2;0.25
3;0.25
4;0.25
5;0.25
6;0.25
7;0.25
8;0.25
9;0.25
10;0.25
e
1;0.52
2;0.26
3;0.27
4;0.14
5;0.14
6;0.13
7;0.13
8;0.12
9;0.13
10;0.12
e
1;0.25
2;0.125
3;0.13
4;0.067
5;0.067
6;0.063
7;0.063
8;0.0577
9;0.063
10;0.0577
e
