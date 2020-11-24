#!/bin/bash

paramsh="0.25 0.225 0.2 0.175 0.15 0.125 0.1 0.075 0.05 0.025 0.01"

for eps in $paramsh; do
    ./build/heur 1 4 ${eps} ../dataset/Climate_ex.txt ../dataset/Climate_dg.txt ../dataset/q/q_4d.txt ../dataset/Climate_valid.txt ../result/heur_Climate.txt
done

for eps in $paramsh; do
    ./build/approx 4 ${eps} ../dataset/Climate.txt ../dataset/q/q_4d.txt ../dataset/Climate_valid.txt ../result/approx_Climate.txt
done
