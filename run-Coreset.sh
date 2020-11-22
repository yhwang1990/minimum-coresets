#!/bin/bash

epsLD="0.001 0.0025 0.005 0.01 0.025 0.05 0.1 0.15 0.2 0.25"
epsHD="0.25 0.225 0.2 0.175 0.15 0.125 0.1 0.075 0.05 0.025 0.01"

sizes="1k 10k 100k 1m 10m"
dims="3 4 5 6 7 8 9 10"

./build/opt ../dataset/FourSquare_NYC.txt ../result/opt_FourSquare_NYC.txt
./build/opt ../dataset/FourSquare_TKY.txt ../result/opt_FourSquare_TKY.txt
./build/opt ../dataset/normal/normal_2d.txt ../result/opt_normal_2d.txt

for size in $sizes; do
  ./build/opt ../dataset/normal/normal_2d_${size}.txt ../result/opt_normal_2d_${size}.txt
done

for eps in $epsLD; do
  ./build/heur 1 2 ${eps} ../dataset/normal/normal_2d_ex.txt ../dataset/normal/normal_2d_dg.txt ../dataset/q/q_2d.txt ../dataset/normal/normal_2d_valid.txt ../result/heur_normal_2d.txt
done

for eps in $epsLD; do
    ./build/heur 1 2 ${eps} ../dataset/FourSquare_NYC_ex.txt ../dataset/FourSquare_NYC_dg.txt ../dataset/q/q_2d.txt ../dataset/FourSquare_NYC_valid.txt ../result/heur_FourSquare_NYC.txt
done

for eps in $epsLD; do
    ./build/heur 1 2 ${eps} ../dataset/FourSquare_TKY_ex.txt ../dataset/FourSquare_TKY_dg.txt ../dataset/q/q_2d.txt ../dataset/FourSquare_TKY_valid.txt ../result/heur_FourSquare_TKY.txt
done

for size in $sizes; do
    ./build/heur 1 2 0.1 ../dataset/normal/normal_2d_${size}_ex.txt ../dataset/normal/normal_2d_${size}_dg.txt ../dataset/q/q_2d.txt ../dataset/normal/normal_2d_${size}_valid.txt ../result/heur_normal_2d_${size}.txt
done

for eps in $epsHD; do
    ./build/heur 1 3 ${eps} ../dataset/RoadNetwork_ex.txt ../dataset/RoadNetwork_dg.txt ../dataset/q/q_3d.txt ../dataset/RoadNetwork_valid.txt ../result/heur_RoadNetwork.txt
    ./build/heur 1 6 ${eps} ../dataset/AirQuality_ex.txt ../dataset/AirQuality_dg.txt ../dataset/q/q_6d.txt ../dataset/AirQuality_valid.txt ../result/heur_AirQuality.txt
    ./build/heur 1 6 ${eps} ../dataset/normal/normal_6d_ex.txt ../dataset/normal/normal_6d_dg.txt ../dataset/q/q_6d.txt ../dataset/normal/normal_6d_valid.txt ../result/heur_normal_6d.txt
    ./build/heur 1 9 ${eps} ../dataset/Color_ex.txt ../dataset/Color_dg.txt ../dataset/q/q_9d.txt ../dataset/Color_valid.txt ../result/heur_Color.txt
    ./build/heur 1 6 ${eps} ../dataset/uniform/uniform_6d_ex.txt ../dataset/uniform/uniform_6d_dg.txt ../dataset/q/q_6d.txt ../dataset/uniform/uniform_6d_valid.txt ../result/heur_uniform_6d.txt
done

for size in $sizes; do
    ./build/heur 1 6 0.1 ../dataset/normal/normal_${size}_ex.txt ../dataset/normal/normal_${size}_dg.txt ../dataset/q/q_6d.txt ../dataset/normal/normal_${size}_valid.txt ../result/heur_normal_${size}.txt
    ./build/heur 1 6 0.1 ../dataset/uniform/uniform_${size}_ex.txt ../dataset/uniform/uniform_${size}_dg.txt ../dataset/q/q_6d.txt ../dataset/uniform/uniform_${size}_valid.txt ../result/heur_uniform_${size}.txt
done

for d in $dims; do
    ./build/heur 1 ${d} 0.1 ../dataset/normal/normal_${d}d_ex.txt ../dataset/normal/normal_${d}d_dg.txt ../dataset/q/q_${d}d.txt ../dataset/normal/normal_${d}d_valid.txt ../result/heur_normal_${d}d.txt
    ./build/heur 1 ${d} 0.1 ../dataset/uniform/uniform_${d}d_ex.txt ../dataset/uniform/uniform_${d}d_dg.txt ../dataset/q/q_${d}d.txt ../dataset/uniform/uniform_${d}d_valid.txt ../result/heur_uniform_${d}d.txt
done
