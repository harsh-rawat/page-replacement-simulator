#!/bin/bash

# Harsh Rawat, harsh-rawat, hrawat2
# Sidharth Gurbani, gurbani, gurbani

# This will make the three executable files
make

export FIFO_EXEC=./537pfsim-fifo
export LRU_EXEC=./537pfsim-lru
export CLOCK_EXEC=./537pfsim-clock
export TIME=

######### Starting execution of FIFO algorithm #########

# Running 4 tracefiles
for tracefile in smallmix.addrtrace 4000.addrtrace bigmix.addrtrace 12million.addrtrace
do
	# Running 6 executables 
	# Outer loop with two p-values
	# Inner loop with three m-values
	for p_value in 512 4096
	do

		for m_value in 1 4 32
		do
			echo "Running $tracefile with p_value=$p_value and m_value=$m_value."$'\n'
			echo "---------------------------------------------------"
			echo "Running FIFO algorithm"
			echo "---------------------------------------------------"

			$TIME $FIFO_EXEC -p $p_value -m $m_value $tracefile

			echo $'\n'"---------------------------------------------------"
			echo "Running LRU algorithm"
			echo "---------------------------------------------------"
			$TIME $LRU_EXEC -p $p_value -m $m_value $tracefile

			echo $'\n'"---------------------------------------------------"
			echo "Running CLOCK algorithm"
			echo "---------------------------------------------------"
			$TIME $CLOCK_EXEC -p $p_value -m $m_value $tracefile
			echo $'\n'"---------------------------------------------------"$'\n'
		done
	done
done

