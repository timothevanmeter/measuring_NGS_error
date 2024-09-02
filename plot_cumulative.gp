

set log x
set xlab "Number of expected errors per sequence"
set ylab "Cumulative fraction of the trimmed dataset (30bp)"
set title "Error threshold for the trimmed datasets"
# set key at 1.0,0.3
set key bottom right

# Graphical representation of the fraction of datasets kept:
# set label at 0.1,0.4690 "0.4690" point pointtype 7 pointsize 2 offset -8,0
# set label at 0.1,0.3889 "0.3889" point pointtype 7 pointsize 2 offset 1.5,-0.5
# set label at 0.1,0.7820 "0.7820" point pointtype 7 pointsize 2 offset 1.5,-1


# Graphical representation of the threshold value:
# set arrow from 0.1,0.0 to 0.1,0.9 nohead lw 2 dt 2 lc 'red'


set output "error_cumulative_NGS-simulation.png"
set terminal pngcairo size 1000,748 enhanced font 'Verdana,12'


list=system('ls -1B *_cumulative.dat')

# plot for [file in list] file u 1:2 w lp pt 21 t substr(file,1,3).'-'.substr(file,13,15)

plot for [file in list] file u 1:2 w lp pt 21 t 'NGS error simulation'

