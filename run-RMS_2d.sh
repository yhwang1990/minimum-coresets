#!/bin/bash

sizes="10k 50k 100k 500k 1m 5m 10m"

./build/2D_RRMS ../dataset/NBA.txt ../result/2DRRMS_NBA.txt ../dataset/q/q_2d.txt ../dataset/NBA_valid.txt
./build/2D_RRMS ../dataset/Airline.txt ../result/2DRRMS_Airline.txt ../dataset/q/q_2d.txt ../dataset/Airline_valid.txt

for size in $sizes; do
	./build/2D_RRMS ../dataset/normal/normal_2d_${size}.txt ../result/2DRRMS_normal_2d_${size}.txt ../dataset/q/q_2d.txt ../dataset/normal/normal_2d_${size}_valid.txt
done
