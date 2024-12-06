for model in data/*; do 
	model_name=${model##*/}
	echo "Started $model_name."
	for task in $model/*; do
		task_name=${task##*/}
		echo "Started $task_name."
		file=$(find ./data/$model_name/$task_name -name '*.cpp')
		file_name=${file%.cpp}
		g++ -std=c++17 $file -o $file_name
	done
done
