#!/bin/bash

params="0.001 0.0025 0.005 0.01 0.025 0.05 0.075 0.1 0.125 0.15 0.175 0.2 0.225 0.25"

for eps in $params; do
    ./build/heur 1 2 ${eps} ../dataset/uniform/uniform_2d_ex.txt ../dataset/uniform/uniform_2d_dg.txt ../dataset/q/q_2d.txt ../dataset/uniform/uniform_2d_valid.txt ../result/heur_uniform_2d.txt
done

for eps in $params; do
    ./build/approx 2 ${eps} ../dataset/uniform/uniform_2d.txt ../dataset/q/q_2d.txt ../dataset/uniform/uniform_2d_valid.txt ../result/approx_uniform_2d.txt
done
