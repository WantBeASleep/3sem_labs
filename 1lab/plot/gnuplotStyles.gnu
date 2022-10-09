set terminal png size 1920,1080
set output 'plot/plot.png'
set title "Analyse time(count) of sorts"
set xlabel "count of elements(N)"
set xtics (2000, 4000, 6000, 8000, 10000, 12000, 14000, 16000, 18000, 20000)
set ylabel "time(sec)"
set key left top
set key box linestyle 1
set grid