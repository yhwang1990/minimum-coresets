#!/bin/bash

params="0.001 0.0025 0.005 0.01 0.025 0.05 0.075 0.1 0.125 0.15 0.175 0.2 0.225 0.25"
paramsh="0.25 0.225 0.2 0.175 0.15 0.125 0.1 0.075 0.05 0.025 0.01"
sizes="1k 10k 100k 1m 10m"
dims="3 4 5 6 7 8 9 10"

for eps in $params; do
    ./build/approx 2 ${eps} ../dataset/normal/normal_2d.txt ../dataset/q/q_2d.txt ../dataset/normal/normal_2d_valid.txt ../result/approx_normal_2d.txt
done

for eps in $params; do
    ./build/approx 2 ${eps} ../dataset/FourSquare_NYC.txt ../dataset/q/q_2d.txt ../dataset/FourSquare_NYC_valid.txt ../result/approx_FourSquare_NYC.txt
done

for eps in $params; do
    ./build/approx 2 ${eps} ../dataset/FourSquare_TKY.txt ../dataset/q/q_2d.txt ../dataset/FourSquare_TKY_valid.txt ../result/approx_FourSquare_TKY.txt
done

for size in $sizes; do
    ./build/approx 2 0.1 ../dataset/normal/normal_2d_${size}.txt ../dataset/q/q_2d.txt ../dataset/normal/normal_2d_${size}_valid.txt ../result/approx_normal_2d_${size}.txt
done

for eps in $paramsh; do
    timeout 10h ./build/approx 3 ${eps} ../dataset/RoadNetwork.txt ../dataset/q/q_3d.txt ../dataset/RoadNetwork_valid.txt ../result/approx_RoadNetwork.txt
    timeout 10h ./build/approx 6 ${eps} ../dataset/AirQuality.txt ../dataset/q/q_6d.txt ../dataset/AirQuality_valid.txt ../result/approx_AirQuality.txt
    timeout 10h ./build/approx 6 ${eps} ../dataset/normal/normal_6d.txt ../dataset/q/q_6d.txt ../dataset/normal/normal_6d_valid.txt ../result/approx_normal_6d.txt
done

for size in $sizes; do
    timeout 10h ./build/approx 6 0.1 ../dataset/normal/normal_${size}.txt ../dataset/q/q_6d.txt ../dataset/normal/normal_${size}_valid.txt ../result/approx_normal_${size}.txt
    timeout 10h ./build/approx 6 0.1 ../dataset/uniform/uniform_${size}.txt ../dataset/q/q_6d.txt ../dataset/uniform/uniform_${size}_valid.txt ../result/approx_uniform_${size}.txt
done

for d in $dims; do
    timeout 10h ./build/approx ${d} 0.1 ../dataset/normal/normal_${d}d.txt ../dataset/q/q_${d}d.txt ../dataset/normal/normal_${d}d_valid.txt ../result/approx_normal_${d}d.txt
    timeout 10h ./build/approx ${d} 0.1 ../dataset/uniform/uniform_${d}d.txt ../dataset/q/q_${d}d.txt ../dataset/uniform/uniform_${d}d_valid.txt ../result/approx_uniform_${d}d.txt
done

for eps in $paramsh; do
    timeout 10h ./build/approx 9 ${eps} ../dataset/Color.txt ../dataset/q/q_9d.txt ../dataset/Color_valid.txt ../result/approx_Color.txt
    timeout 10h ./build/approx 6 ${eps} ../dataset/uniform/uniform_6d.txt ../dataset/q/q_6d.txt ../dataset/uniform/uniform_6d_valid.txt ../result/approx_uniform_6d.txt
done
