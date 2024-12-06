for model in data/*; do
	model_name=${model##*/}
	echo "Started $model_name."
	mkdir -p measurements_powermetrics/C++/$model_name
	for task in $model/*; do
		task_name=${task##*/}
		mkdir -p measurements_powermetrics/C++/$model_name/$task_name
		echo "Started $task_name."
		for solution in $task/*; do
			echo "$solution"
			[[ $solution == *.cpp ]] && continue
			[[ $solution == *.java ]] && continue
			[[ $solution == *.py ]] && continue
			for i in {1..10} 
				do
				powermetrics -o measurements_powermetrics/C++/$model_name/$task_name/$i.txt -i 100 -s cpu_power -a --hide-cpu-duty-cycle &
				pm_id=$(ps -A | grep "powermetrics" | grep -v "grep" | awk '{print $1}')
				$solution 
				sudo kill -9 $pm_id
				sleep 3
				done
		done
		sleep 5
		echo "Finished $task_name."
	done

done