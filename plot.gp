

set log y
# set log x
set xlab "Number of expected errors per sequence"
# set ylab "Number of sequences"
set ylab "Fraction of the dataset"
set arrow from 0.01,0.0 to 0.01,1.0 nohead lw 2 lc 'red'

set output "error_comparison_fraction.png"
set terminal pngcairo size 1000,748 enhanced font 'Verdana,12'

# RAW DATA
# plot "T0_S1_R1_001_errors.dat" u 1:3 t 'MAXENCE', "TO_PV_S4_ALL_R1_001_errors.dat" u 1:3 t 'RETINA T0PV1', "AAV2-7merT0-PV_S3_ALL_001_errors.dat" u 1:3 t 'RETINA T0PV2'

# PERCENTAGE DATA
plot "T0_S1_R1_001_errors_perct.dat" u 1:2 t 'MAXENCE', "TO_PV_S4_ALL_R1_001_errors_perct.dat" u 1:2 t 'RETINA T0PV1', "AAV2-7merT0-PV_S3_ALL_001_errors_perct.dat" u 1:2 t 'RETINA T0PV2'