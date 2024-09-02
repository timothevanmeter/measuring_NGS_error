#!/usr/bin/gnuplot --persist


set style fill solid
set style data histograms
# set xtics border in scale 0,0 nomirror rotate by -45  autojustify
# set xtics norangelimit 
# set xtics ()
unset key
set margins 12,5,5,4

set title "Distribution of the expected error in the dataset"
set xlab "Sequence average expected error"
set ylab "Counts"

set log x
set log y


set terminal pngcairo enhanced font "arial,14" fontscale 1.0 size 1000,748

set output ARG2



plot ARG1 using 2:1 with boxes




# -----------------------------------------

# set log y

# set output "test.png"
# set terminal pngcairo size 1000,748 enhanced font 'Verdana,12'

# plot 'NGS_data/SRR30257158_eeout_sorted_rev_counts.dat' using 2:1 w p pt 21 t 'TEST-NGS'
# plot 'NGS_data/AAV2-7merT0-PV_S3_ALL_001_eeout-trimmed_sorted_rev_counts.dat' using 2:1 w p pt 21 t 'RETINA-1'
# plot 'NGS_data/T0_S1_R1_001_eeout-trimmed_sorted_rev_counts.dat' using 2:1 w p pt 21 t 'MAXENCE'
# plot 'NGS_data/TO_PV_S4_ALL_R1_001_eeout-trimmed_sorted_rev_counts.dat' using 2:1 w p pt 21 t 'RETINA-2'
