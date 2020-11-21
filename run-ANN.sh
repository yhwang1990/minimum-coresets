#!/bin/bash

params="0.001 0.0025 0.005 0.01 0.025 0.05 0.075 0.1 0.125 0.15 0.175 0.2 0.225 0.25"
paramsh="0.25 0.225 0.2 0.175 0.15 0.125 0.1 0.075 0.05 0.025 0.01"
sizes="1k 10k 100k 500k 1m 5m 10m"
dims="3 4 5 6 7 8 9 10"

for eps in $params; do
    ./coreset/coreset ${eps} 2 ../dataset/normal/normal_2d.txt ../dataset/q/q_2d.txt ../dataset/normal/normal_2d_valid.txt ../result/ann_normal_2d.txt
done

for eps in $params; do
    ./coreset/coreset ${eps} 2 ../dataset/FourSquare_NYC.txt ../dataset/q/q_2d.txt ../dataset/FourSquare_NYC_valid.txt ../result/ann_FourSquare_NYC.txt
done

for eps in $params; do
    ./coreset/coreset ${eps} 2 ../dataset/FourSquare_TKY.txt ../dataset/q/q_2d.txt ../dataset/FourSquare_TKY_valid.txt ../result/ann_FourSquare_TKY.txt
done

for size in $sizes; do
    ./coreset/coreset 0.1 2 ../dataset/normal/normal_2d_${size}.txt ../dataset/q/q_2d.txt ../dataset/normal/normal_2d_${size}_valid.txt ../result/ann_normal_2d_${size}.txt
done

for eps in $paramsh; do
    timeout 10h ./coreset/coreset ${eps} 3 ../dataset/RoadNetwork.txt ../dataset/q/q_3d.txt ../dataset/RoadNetwork_valid.txt ../result/ann_RoadNetwork.txt
    timeout 10h ./coreset/coreset ${eps} 6 ../dataset/AirQuality.txt ../dataset/q/q_6d.txt ../dataset/AirQuality_valid.txt ../result/ann_AirQuality.txt
    timeout 10h ./coreset/coreset ${eps} 9 ../dataset/Color.txt ../dataset/q/q_9d.txt ../dataset/Color_valid.txt ../result/ann_Color.txt
done

for size in $sizes; do
    timeout 10h ./coreset/coreset 0.1 6 ../dataset/normal/normal_${size}.txt ../dataset/q/q_6d.txt ../dataset/normal/normal_${size}_valid.txt ../result/ann_normal_${size}.txt
    timeout 10h ./coreset/coreset 0.1 6 ../dataset/uniform/uniform_${size}.txt ../dataset/q/q_6d.txt ../dataset/uniform/uniform_${size}_valid.txt ../result/ann_uniform_${size}.txt
done

for d in $dims; do
    timeout 10h ./coreset/coreset 0.1 ${d} ../dataset/normal/normal_${d}d.txt ../dataset/q/q_${d}d.txt ../dataset/normal/normal_${d}d_valid.txt ../result/ann_normal_${d}d.txt
    timeout 10h ./coreset/coreset 0.1 ${d} ../dataset/uniform/uniform_${d}d.txt ../dataset/q/q_${d}d.txt ../dataset/uniform/uniform_${d}d_valid.txt ../result/ann_uniform_${d}d.txt
done
