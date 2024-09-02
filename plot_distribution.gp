
# For MAXENCE:
mu1=0.051328
var1=0.013189

# For Test_NGS:
mu2=0.530135
var2=1.337220

# For RETINA-1:
mu3=0.145856
var3=0.026334

# For RETINA-2:
mu4=0.156569
var4=0.022092

f(x,mu,var) = 1.0/sqrt(2.0*pi*var)*exp(-(x-mu)**2.0/(2.0*var))
fcr(x,mu,var) = ((1.0/sqrt(2.0*pi*var)*exp(-(x-mu)**2.0/(2.0*var)))-mu)/var

# set log x
# set log y

set xrange [-3:4]
set ylabel "Gaussian function with\nmean and variance from data"

set output "datasets_error_probability_distribution.png"
set terminal pngcairo size 1000,748 enhanced font 'Verdana,12'

# plot fcr(x,mu1,var1) t 'MAXENCE'

plot f(x,mu1,var1) t 'MAXENCE', f(x,mu2,var2) t 'TEST-NGS', f(x,mu3,var3) t 'RETINA-1', f(x,mu4,var4) t 'RETINA-2'