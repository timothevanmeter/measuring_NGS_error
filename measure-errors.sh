#!/bin/bash

# data_folder="/data/DIRECTED_EVOLUTION_DATA/datasets/"
# folder=$1
# file=$2
# path=$folder$file
file=$1

# echo $path

# USAGE:
# ./measure-errors.sh T0_S1_R1_001_eeout-trimmed.fastq MAXENCE

# can be called in the following way:
# $ datasets=("" "dataset2")
# $ for i in $(echo ${datasets[*]}); do ./pipeline.sh $i;done


# # GENERATING the expected error from the fastq file
vsearch --fastq_filter $file --fastq_ascii 33 --eeout --fastqout ${file/.fastq/_eeout.fastq}

# EXTRACTING the value of the expected error directly from the header of the generated fastq file.
awk -F "=" 'NR%4==1{print $3}' ${file/.fastq/_eeout.fastq} > ${file/.fastq/.dat}
# awk -F "=" 'NR%4==1{print $3}' $file > ${file/.fastq/.dat}

# Getting the total number of lines in the dataset
# size=$(wc -l ${file/.fastq/_eeout.fastq} | awk '{print $1}')
size=$(wc -l $file | awk '{print $1}')
# Each sequence occupies 4 lines in a fastq file:
size=$(($size/4))

printf "\nTotal lines in dataset = %d\n" $size



# Sorting the errors in decreasing order
./sort_errors.o ${file/.fastq/.dat} ${file/.fastq/_sorted.dat}

# Inverting the sorting order
tac ${file/.fastq/_sorted.dat} > ${file/.fastq/_sorted_rev.dat}

# Counting the number of occurences for each value
uniq --count ${file/.fastq/_sorted_rev.dat} > ${file/.fastq/_sorted_rev_counts.dat}

# Getting the cumulative fraction of the dataset in
# the order of increasing values.
awk -v size="$size" '{sum+=$1; print $2" "((sum/size))}' ${file/.fastq/_sorted_rev_counts.dat} > ${file/.fastq/_cumulative_temp.dat}

# Removing the commas in decimals introduced by awk
awk '{gsub(",",".");print $0}' ${file/.fastq/_cumulative_temp.dat} > ${file/.fastq/_cumulative.dat}


# Avoiding to loop over the new fastq files
# when using the *.fastq regexp in bash
rm ${file/.fastq/_eeout.fastq}


# Plotting the results
# gnuplot plot_cumulative.gp
