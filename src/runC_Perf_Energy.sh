for model in data/*; do
	model_name=${model##*/}
	echo "Started $model_name."
	mkdir -p measurements_powermetrics/C++/$model_name
	for task in $model/*; do
		task_name=${task##*/}
		mkdir -p measurements_powermetrics/C++/$model_name/$task_name
		echo "Started $task_name."
		for solution in $task/*; do
			if ["${solution###.}"="cpp"]
			then continue
			else
			for i in $(seq 1 10) 
				do
				sudo perf stat -e "power/energy-pkg" record $solution 2> measurements_perf/C++/$model_name/$task_name/$i.txt
				sleep 3
				done
			fi
		done
		sleep 5
		echo "Finished $task_name."
	done

done