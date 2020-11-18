#!/bin/bash

params="0.1 0.05 0.01 0.005 0.001"
paramsh="0.09 0.08 0.07 0.06 0.04 0.03 0.02 0.01"
sizes="10k 50k 100k 500k 1m 5m 10m"
dims="3 4 5 6 7 8 9 10"

for eps in $params; do
    ./coreset/coreset ${eps} 2 ../dataset/normal/normal_2d.txt ../dataset/q/q_2d.txt ../dataset/normal/normal_2d_valid.txt ../result/ann_normal_2d.txt
    ./hs/hs ${eps} 2 ../dataset/normal/normal_2d.txt ../dataset/q/q_2d.txt ../dataset/normal/normal_2d_valid.txt ../result/hs_normal_2d.txt
done

for eps in $params; do
    ./coreset/coreset ${eps} 2 ../dataset/NBA.txt ../dataset/q/q_2d.txt ../dataset/NBA_valid.txt ../result/ann_NBA.txt
    ./hs/hs ${eps} 2 ../dataset/NBA.txt ../dataset/q/q_2d.txt ../dataset/NBA_valid.txt ../result/hs_NBA.txt
done

for eps in $params; do
    ./coreset/coreset ${eps} 2 ../dataset/Airline.txt ../dataset/q/q_2d.txt ../dataset/Airline_valid.txt ../result/ann_Airline.txt
    ./hs/hs ${eps} 2 ../dataset/Airline.txt ../dataset/q/q_2d.txt ../dataset/Airline_valid.txt ../result/hs_Airline.txt
done

for size in $sizes; do
    for eps in $params; do
        ./coreset/coreset ${eps} 2 ../dataset/normal/normal_2d_${size}.txt ../dataset/q/q_2d.txt ../dataset/normal/normal_2d_${size}_valid.txt ../result/ann_normal_2d_${size}.txt
        ./hs/hs ${eps} 2 ../dataset/normal/normal_2d_${size}.txt ../dataset/q/q_2d.txt ../dataset/normal/normal_2d_${size}_valid.txt ../result/hs_normal_2d_${size}.txt
    done
done

./coreset/coreset 0.1 5 ../dataset/ElNino.txt ../dataset/q/q_5d.txt ../dataset/ElNino_valid.txt ../result/ann_ElNino.txt
./coreset/coreset 0.1 6 ../dataset/Weather.txt ../dataset/q/q_6d.txt ../dataset/Weather_valid.txt ../result/ann_Weather.txt
./coreset/coreset 0.1 7 ../dataset/Household.txt ../dataset/q/q_7d.txt ../dataset/Household_valid.txt ../result/ann_Household.txt
./coreset/coreset 0.1 8 ../dataset/SUSY.txt ../dataset/q/q_8d.txt ../dataset/SUSY_valid.txt ../result/ann_SUSY.txt

for size in $sizes; do
	timeout 24h ./coreset/coreset 0.1 6 ../dataset/normal/normal_${size}.txt ../dataset/q/q_6d.txt ../dataset/normal/normal_${size}_valid.txt ../result/ann_normal_${size}.txt
	timeout 24h ./coreset/coreset 0.1 6 ../dataset/uniform/uniform_${size}.txt ../dataset/q/q_6d.txt ../dataset/uniform/uniform_${size}_valid.txt ../result/ann_uniform_${size}.txt
done

for d in $dims; do
	timeout 24h ./coreset/coreset 0.1 ${d} ../dataset/normal/normal_${d}d.txt ../dataset/q/q_${d}d.txt ../dataset/normal/normal_${d}d_valid.txt ../result/ann_normal_${d}d.txt
	timeout 24h ./coreset/coreset 0.1 ${d} ../dataset/uniform/uniform_${d}d.txt ../dataset/q/q_${d}d.txt ../dataset/uniform/uniform_${d}d_valid.txt ../result/ann_uniform_${d}d.txt
done

for eps in $paramsh; do
	timeout 24h ./coreset/coreset ${eps} 5 ../dataset/ElNino.txt ../dataset/q/q_5d.txt ../dataset/ElNino_valid.txt ../result/ann_ElNino.txt
	timeout 24h ./coreset/coreset ${eps} 6 ../dataset/Weather.txt ../dataset/q/q_6d.txt ../dataset/Weather_valid.txt ../result/ann_Weather.txt
	timeout 24h ./coreset/coreset ${eps} 7 ../dataset/Household.txt ../dataset/q/q_7d.txt ../dataset/Household_valid.txt ../result/ann_Household.txt
	timeout 24h ./coreset/coreset ${eps} 8 ../dataset/SUSY.txt ../dataset/q/q_8d.txt ../dataset/SUSY_valid.txt ../result/ann_SUSY.txt
done

./hs/hs 0.1 5 ../dataset/ElNino.txt ../dataset/q/q_5d.txt ../dataset/ElNino_valid.txt ../result/hs_ElNino.txt
./hs/hs 0.1 6 ../dataset/Weather.txt ../dataset/q/q_6d.txt ../dataset/Weather_valid.txt ../result/hs_Weather.txt
./hs/hs 0.1 7 ../dataset/Household.txt ../dataset/q/q_7d.txt ../dataset/Household_valid.txt ../result/hs_Household.txt
./hs/hs 0.1 8 ../dataset/SUSY.txt ../dataset/q/q_8d.txt ../dataset/SUSY_valid.txt ../result/hs_SUSY.txt

for size in $sizes; do
	timeout 24h ./hs/hs 0.1 6 ../dataset/normal/normal_${size}.txt ../dataset/q/q_6d.txt ../dataset/normal/normal_${size}_valid.txt ../result/hs_normal_${size}.txt
	timeout 24h ./hs/hs 0.1 6 ../dataset/uniform/uniform_${size}.txt ../dataset/q/q_6d.txt ../dataset/uniform/uniform_${size}_valid.txt ../result/hs_uniform_${size}.txt
done

for d in $dims; do
	timeout 24h ./hs/hs 0.1 ${d} ../dataset/normal/normal_${d}d.txt ../dataset/q/q_${d}d.txt ../dataset/normal/normal_${d}d_valid.txt ../result/hs_normal_${d}d.txt
	timeout 24h ./hs/hs 0.1 ${d} ../dataset/uniform/uniform_${d}d.txt ../dataset/q/q_${d}d.txt ../dataset/uniform/uniform_${d}d_valid.txt ../result/hs_uniform_${d}d.txt
done

for eps in $paramsh; do
	timeout 24h ./hs/hs ${eps} 5 ../dataset/ElNino.txt ../dataset/q/q_5d.txt ../dataset/ElNino_valid.txt ../result/hs_ElNino.txt
	timeout 24h ./hs/hs ${eps} 6 ../dataset/Weather.txt ../dataset/q/q_6d.txt ../dataset/Weather_valid.txt ../result/hs_Weather.txt
	timeout 24h ./hs/hs ${eps} 7 ../dataset/Household.txt ../dataset/q/q_7d.txt ../dataset/Household_valid.txt ../result/hs_Household.txt
	timeout 24h ./hs/hs ${eps} 8 ../dataset/SUSY.txt ../dataset/q/q_8d.txt ../dataset/SUSY_valid.txt ../result/hs_SUSY.txt
done
