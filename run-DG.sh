#!/bin/bash

sizes="1k 10k 100k 1m 10m"
dims="3 4 5 6 7 8 9 10"

./build/heur 0 2 ../dataset/FourSquare_NYC_ex.txt na ../dataset/FourSquare_NYC_dg.txt
./build/heur 0 2 ../dataset/FourSquare_TKY_ex.txt na ../dataset/FourSquare_TKY_dg.txt
./build/heur 0 2 ../dataset/normal/normal_2d_ex.txt na ../dataset/normal/normal_2d_dg.txt
./build/heur 0 2 ../dataset/uniform/uniform_2d_ex.txt na ../dataset/uniform/uniform_2d_dg.txt

for size in $sizes; do
    ./build/heur 0 2 ../dataset/normal/normal_2d_${size}_ex.txt na ../dataset/heur_normal_2d_${size}_dg.txt
done

./build/heur 0 3 ../dataset/RoadNetwork_ex.txt ../dataset/RoadNetwork_ipdg.txt ../dataset/RoadNetwork_dg.txt
./build/heur 0 6 ../dataset/AirQuality_ex.txt ../dataset/AirQuality_ipdg.txt ../dataset/AirQuality_dg.txt
./build/heur 0 9 ../dataset/Color_ex.txt ../dataset/Color_ipdg.txt ../dataset/Color_dg.txt

for d in $dims; do
    ./build/heur 0 ${d} ../dataset/normal/normal_${d}d_ex.txt ../dataset/normal/normal_${d}d_ipdg.txt ../dataset/normal/normal_${d}d_dg.txt
done

for size in $sizes; do
    ./build/heur 0 6 ../dataset/normal/normal_${size}_ex.txt ../dataset/normal/normal_${size}_ipdg.txt ../dataset/normal/normal_${size}_dg.txt
done

for d in $dims; do
    ./build/heur 0 ${d} ../dataset/uniform/uniform_${d}d_ex.txt ../dataset/uniform/uniform_${d}d_ipdg.txt ../dataset/uniform/uniform_${d}d_dg.txt
done

for size in $sizes; do
    ./build/heur 0 6 ../dataset/uniform/uniform_${size}_ex.txt ../dataset/uniform/uniform_${size}_ipdg.txt ../dataset/uniform/uniform_${size}_dg.txt
done
