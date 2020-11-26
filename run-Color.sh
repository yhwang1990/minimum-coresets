#!/bin/bash

params="0.25 0.225 0.2 0.175 0.15 0.125 0.1 0.075 0.05 0.025 0.01"

for eps in $params; do
    timeout 12h ./build/approx2 9 ${eps} ../dataset/Color.txt ../dataset/q/q_9d.txt ../dataset/Color_valid.txt ../result/approx_Color.txt
done
