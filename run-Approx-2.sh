#!/bin/bash

paramsh="0.25 0.225 0.2 0.175 0.15 0.125 0.1 0.075 0.05 0.025 0.01"

for eps in $paramsh; do
    timeout 10h ./build/approx 9 ${eps} ../dataset/Color.txt ../dataset/q/q_9d.txt ../dataset/Color_valid.txt ../result/approx_Color.txt
    timeout 10h ./build/approx 6 ${eps} ../dataset/uniform/uniform_6d.txt ../dataset/q/q_6d.txt ../dataset/uniform/uniform_6d_valid.txt ../result/approx_uniform_6d.txt
done
