#!/bin/bash

params="0.1 0.09 0.08 0.07 0.06 0.05 0.04 0.03 0.02 0.01"
paramsh="0.1 0.09 0.08 0.07 0.06 0.05"

for eps in $params; do
	./run Sphere ../dataset/ElNino.txt ./result/time_Sphere_ElNino.txt ./result/result_Sphere_ElNino_${eps}.txt 5 ${eps}
	./run Greedy ../dataset/ElNino.txt ./result/time_Greedy_ElNino.txt ./result/result_Greedy_ElNino_${eps}.txt 5 ${eps}
	./run HDRRMS ../dataset/ElNino.txt ./result/time_RRMS_ElNino.txt ./result/result_RRMS_ElNino_${eps}.txt 5 ${eps}
done

for eps in $params; do
	./run Sphere ../dataset/Weather.txt ./result/time_Sphere_Weather.txt ./result/result_Sphere_Weather_${eps}.txt 6 ${eps}
	./run Greedy ../dataset/Weather.txt ./result/time_Greedy_Weather.txt ./result/result_Greedy_Weather_${eps}.txt 6 ${eps}
	./run HDRRMS ../dataset/Weather.txt ./result/time_RRMS_Weather.txt ./result/result_RRMS_Weather_${eps}.txt 6 ${eps}
done

for eps in $params; do
	./run Sphere ../dataset/Household.txt ./result/time_Sphere_Household.txt ./result/result_Sphere_Household_${eps}.txt 7 ${eps}
	./run Greedy ../dataset/Household.txt ./result/time_Greedy_Household.txt ./result/result_Greedy_Household_${eps}.txt 7 ${eps}
	./run HDRRMS ../dataset/Household.txt ./result/time_RRMS_Household.txt ./result/result_RRMS_Household_${eps}.txt 7 ${eps}
done

for eps in $params; do
	./run Sphere ../dataset/SUSY.txt ./result/time_Sphere_SUSY.txt ./result/result_Sphere_SUSY_${eps}.txt 8 ${eps}
	./run Greedy ../dataset/SUSY.txt ./result/time_Greedy_SUSY.txt ./result/result_Greedy_SUSY_${eps}.txt 8 ${eps}
	./run HDRRMS ../dataset/SUSY.txt ./result/time_RRMS_SUSY.txt ./result/result_RRMS_SUSY_${eps}.txt 8 ${eps}
done

sizes="10k 50k 100k 500k 1m 5m 10m"
dims="3 4 5 6 7 8 9 10"

for size in $sizes; do
	for eps in $paramsh; do
		./run Sphere ../dataset/normal/normal_${size}.txt ./result/time_Sphere_normal_${size}.txt ./result/result_Sphere_normal_${size}_${eps}.txt 6 ${eps}
		./run Greedy ../dataset/normal/normal_${size}.txt ./result/time_Greedy_normal_${size}.txt ./result/result_Greedy_normal_${size}_${eps}.txt 6 ${eps}
		./run HDRRMS ../dataset/normal/normal_${size}.txt ./result/time_RRMS_normal_${size}.txt ./result/result_RRMS_normal_${size}_${eps}.txt 6 ${eps}
	done
done

for d in $dims; do
	for eps in $paramsh; do
		./run Sphere ../dataset/normal/normal_${d}d.txt ./result/time_Sphere_normal_${d}d.txt ./result/result_Sphere_normal_${d}d_${eps}.txt ${d} ${eps}
		./run Greedy ../dataset/normal/normal_${d}d.txt ./result/time_Greedy_normal_${d}d.txt ./result/result_Greedy_normal_${d}d_${eps}.txt ${d} ${eps}
		./run HDRRMS ../dataset/normal/normal_${d}d.txt ./result/time_RRMS_normal_${d}d.txt ./result/result_RRMS_normal_${d}d_${eps}.txt ${d} ${eps}
	done
done

for size in $sizes; do
	for eps in $paramsh; do
		./run Sphere ../dataset/uniform/uniform_${size}.txt ./result/time_Sphere_uniform_${size}.txt ./result/result_Sphere_uniform_${size}_${eps}.txt 6 ${eps}
		./run Greedy ../dataset/uniform/uniform_${size}.txt ./result/time_Greedy_uniform_${size}.txt ./result/result_Greedy_uniform_${size}_${eps}.txt 6 ${eps}
		./run HDRRMS ../dataset/uniform/uniform_${size}.txt ./result/time_RRMS_uniform_${size}.txt ./result/result_RRMS_uniform_${size}_${eps}.txt 6 ${eps}
	done
done

for d in $dims; do
	for eps in $paramsh; do
		./run Sphere ../dataset/uniform/uniform_${d}d.txt ./result/time_Sphere_uniform_${d}d.txt ./result/result_Sphere_uniform_${d}d_${eps}.txt ${d} ${eps}
		./run Greedy ../dataset/uniform/uniform_${d}d.txt ./result/time_Greedy_uniform_${d}d.txt ./result/result_Greedy_uniform_${d}d_${eps}.txt ${d} ${eps}
		./run HDRRMS ../dataset/uniform/uniform_${d}d.txt ./result/time_RRMS_uniform_${d}d.txt ./result/result_RRMS_uniform_${d}d_${eps}.txt ${d} ${eps}
	done
done
