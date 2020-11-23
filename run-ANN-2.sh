#!/bin/bash

paramsh="0.25 0.225 0.2 0.175 0.15 0.125 0.1 0.075 0.05 0.025 0.01"

for eps in $paramsh; do
    ./coreset/coreset ${eps} 6 ../dataset/normal/normal_6d.txt ../dataset/q/q_6d.txt ../dataset/normal/normal_6d_valid.txt ../result/ann_normal_6d_all.txt
    ./coreset/coreset ${eps} 6 ../dataset/uniform/uniform_6d.txt ../dataset/q/q_6d.txt ../dataset/uniform/uniform_6d_valid.txt ../result/ann_uniform_6d_all.txt
done
