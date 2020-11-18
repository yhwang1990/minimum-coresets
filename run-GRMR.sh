#!/bin/bash

sizes="10k 50k 100k 500k 1m 5m 10m"
dims="3 4 5 6 7 8 9 10"

./build/ExactGRMR ../dataset/NBA.txt ../result/ExactGRMR_NBA.txt
./build/HeurGRMR 2 ../dataset/NBA_ex.txt na ../dataset/q/q_2d.txt ../dataset/NBA_valid.txt ../result/HeurGRMR_NBA.txt 2
./build/ExactGRMR ../dataset/Airline.txt ../result/ExactGRMR_Airline.txt
./build/HeurGRMR 2 ../dataset/Airline_ex.txt na ../dataset/q/q_2d.txt ../dataset/Airline_valid.txt ../result/HeurGRMR_Airline.txt 2

for size in $sizes; do
    ./build/ExactGRMR ../dataset/normal/normal_2d_${size}.txt ../result/ExactGRMR_normal_2d_${size}.txt
	./build/HeurGRMR 2 ../dataset/normal/normal_2d_${size}_ex.txt na ../dataset/q/q_2d.txt ../dataset/normal/normal_2d_${size}_valid.txt ../result/HeurGRMR_normal_2d_${size}.txt 2
done

./build/HeurGRMR 5 ../dataset/ElNino_ex.txt ../dataset/ElNino_top4.txt ../dataset/q/q_5d.txt ../dataset/ElNino_valid.txt ../result/HeurGRMR_ElNino_4.txt 1
./build/HeurGRMR 5 ../dataset/ElNino_ex.txt ../dataset/ElNino_top8.txt ../dataset/q/q_5d.txt ../dataset/ElNino_valid.txt ../result/HeurGRMR_ElNino_8.txt 1
./build/HeurGRMR 5 ../dataset/ElNino_ex.txt ../dataset/ElNino_top16.txt ../dataset/q/q_5d.txt ../dataset/ElNino_valid.txt ../result/HeurGRMR_ElNino_16.txt 1
./build/HeurGRMR 5 ../dataset/ElNino_ex.txt ../dataset/ElNino_top32.txt ../dataset/q/q_5d.txt ../dataset/ElNino_valid.txt ../result/HeurGRMR_ElNino_32.txt 1

./build/HeurGRMR 6 ../dataset/Weather_ex.txt ../dataset/Weather_top4.txt ../dataset/q/q_6d.txt ../dataset/Weather_valid.txt ../result/HeurGRMR_Weather_4.txt 1
./build/HeurGRMR 6 ../dataset/Weather_ex.txt ../dataset/Weather_top8.txt ../dataset/q/q_6d.txt ../dataset/Weather_valid.txt ../result/HeurGRMR_Weather_8.txt 1
./build/HeurGRMR 6 ../dataset/Weather_ex.txt ../dataset/Weather_top16.txt ../dataset/q/q_6d.txt ../dataset/Weather_valid.txt ../result/HeurGRMR_Weather_16.txt 1
./build/HeurGRMR 6 ../dataset/Weather_ex.txt ../dataset/Weather_top32.txt ../dataset/q/q_6d.txt ../dataset/Weather_valid.txt ../result/HeurGRMR_Weather_32.txt 1

./build/HeurGRMR 7 ../dataset/Household_ex.txt ../dataset/Household_top4.txt ../dataset/q/q_7d.txt ../dataset/Household_valid.txt ../result/HeurGRMR_Household_4.txt 1
./build/HeurGRMR 7 ../dataset/Household_ex.txt ../dataset/Household_top8.txt ../dataset/q/q_7d.txt ../dataset/Household_valid.txt ../result/HeurGRMR_Household_8.txt 1
./build/HeurGRMR 7 ../dataset/Household_ex.txt ../dataset/Household_top16.txt ../dataset/q/q_7d.txt ../dataset/Household_valid.txt ../result/HeurGRMR_Household_16.txt 1
./build/HeurGRMR 7 ../dataset/Household_ex.txt ../dataset/Household_top32.txt ../dataset/q/q_7d.txt ../dataset/Household_valid.txt ../result/HeurGRMR_Household_32.txt 1

./build/HeurGRMR 8 ../dataset/SUSY_ex.txt ../dataset/SUSY_top4.txt ../dataset/q/q_8d.txt ../dataset/SUSY_valid.txt ../result/HeurGRMR_SUSY_4.txt 1
./build/HeurGRMR 8 ../dataset/SUSY_ex.txt ../dataset/SUSY_top8.txt ../dataset/q/q_8d.txt ../dataset/SUSY_valid.txt ../result/HeurGRMR_SUSY_8.txt 1
./build/HeurGRMR 8 ../dataset/SUSY_ex.txt ../dataset/SUSY_top16.txt ../dataset/q/q_8d.txt ../dataset/SUSY_valid.txt ../result/HeurGRMR_SUSY_16.txt 1
./build/HeurGRMR 8 ../dataset/SUSY_ex.txt ../dataset/SUSY_top32.txt ../dataset/q/q_8d.txt ../dataset/SUSY_valid.txt ../result/HeurGRMR_SUSY_32.txt 1

for d in $dims; do
	./build/HeurGRMR ${d} ../dataset/normal/normal_${d}d_ex.txt ../dataset/normal/normal_${d}d_top4.txt ../dataset/q/q_${d}d.txt ../dataset/normal/normal_${d}d_valid.txt ../result/HeurGRMR_normal_${d}d_4.txt 0
	./build/HeurGRMR ${d} ../dataset/normal/normal_${d}d_ex.txt ../dataset/normal/normal_${d}d_top8.txt ../dataset/q/q_${d}d.txt ../dataset/normal/normal_${d}d_valid.txt ../result/HeurGRMR_normal_${d}d_8.txt 0
	./build/HeurGRMR ${d} ../dataset/normal/normal_${d}d_ex.txt ../dataset/normal/normal_${d}d_top16.txt ../dataset/q/q_${d}d.txt ../dataset/normal/normal_${d}d_valid.txt ../result/HeurGRMR_normal_${d}d_16.txt 0
	./build/HeurGRMR ${d} ../dataset/normal/normal_${d}d_ex.txt ../dataset/normal/normal_${d}d_top32.txt ../dataset/q/q_${d}d.txt ../dataset/normal/normal_${d}d_valid.txt ../result/HeurGRMR_normal_${d}d_32.txt 0
done

for size in $sizes; do
	./build/HeurGRMR 6 ../dataset/normal/normal_${size}_ex.txt ../dataset/normal/normal_${size}_top4.txt ../dataset/q/q_6d.txt ../dataset/normal/normal_${size}_valid.txt ../result/HeurGRMR_normal_${size}_4.txt 0
	./build/HeurGRMR 6 ../dataset/normal/normal_${size}_ex.txt ../dataset/normal/normal_${size}_top8.txt ../dataset/q/q_6d.txt ../dataset/normal/normal_${size}_valid.txt ../result/HeurGRMR_normal_${size}_8.txt 0
	./build/HeurGRMR 6 ../dataset/normal/normal_${size}_ex.txt ../dataset/normal/normal_${size}_top16.txt ../dataset/q/q_6d.txt ../dataset/normal/normal_${size}_valid.txt ../result/HeurGRMR_normal_${size}_16.txt 0
	./build/HeurGRMR 6 ../dataset/normal/normal_${size}_ex.txt ../dataset/normal/normal_${size}_top32.txt ../dataset/q/q_6d.txt ../dataset/normal/normal_${size}_valid.txt ../result/HeurGRMR_normal_${size}_32.txt 0
done

for d in $dims; do
	./build/HeurGRMR ${d} ../dataset/uniform/uniform_${d}d_ex.txt ../dataset/uniform/uniform_${d}d_top4.txt ../dataset/q/q_${d}d.txt ../dataset/uniform/uniform_${d}d_valid.txt ../result/HeurGRMR_uniform_${d}d_4.txt 0
	./build/HeurGRMR ${d} ../dataset/uniform/uniform_${d}d_ex.txt ../dataset/uniform/uniform_${d}d_top8.txt ../dataset/q/q_${d}d.txt ../dataset/uniform/uniform_${d}d_valid.txt ../result/HeurGRMR_uniform_${d}d_8.txt 0
	./build/HeurGRMR ${d} ../dataset/uniform/uniform_${d}d_ex.txt ../dataset/uniform/uniform_${d}d_top16.txt ../dataset/q/q_${d}d.txt ../dataset/uniform/uniform_${d}d_valid.txt ../result/HeurGRMR_uniform_${d}d_16.txt 0
	./build/HeurGRMR ${d} ../dataset/uniform/uniform_${d}d_ex.txt ../dataset/uniform/uniform_${d}d_top32.txt ../dataset/q/q_${d}d.txt ../dataset/uniform/uniform_${d}d_valid.txt ../result/HeurGRMR_uniform_${d}d_32.txt 0
done

for size in $sizes; do
	./build/HeurGRMR 6 ../dataset/uniform/uniform_${size}_ex.txt ../dataset/uniform/uniform_${size}_top4.txt ../dataset/q/q_6d.txt ../dataset/uniform/uniform_${size}_valid.txt ../result/HeurGRMR_uniform_${size}_4.txt 0
	./build/HeurGRMR 6 ../dataset/uniform/uniform_${size}_ex.txt ../dataset/uniform/uniform_${size}_top8.txt ../dataset/q/q_6d.txt ../dataset/uniform/uniform_${size}_valid.txt ../result/HeurGRMR_uniform_${size}_8.txt 0
	./build/HeurGRMR 6 ../dataset/uniform/uniform_${size}_ex.txt ../dataset/uniform/uniform_${size}_top16.txt ../dataset/q/q_6d.txt ../dataset/uniform/uniform_${size}_valid.txt ../result/HeurGRMR_uniform_${size}_16.txt 0
	./build/HeurGRMR 6 ../dataset/uniform/uniform_${size}_ex.txt ../dataset/uniform/uniform_${size}_top32.txt ../dataset/q/q_6d.txt ../dataset/uniform/uniform_${size}_valid.txt ../result/HeurGRMR_uniform_${size}_32.txt 0
done
