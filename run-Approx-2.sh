#!/bin/bash

./build/approx 6 0.05 ../dataset/uniform/uniform_6d.txt ../dataset/q/q_6d.txt ../dataset/uniform/uniform_6d_valid.txt ../result/approx_uniform_6d.txt
./build/approx 6 0.025 ../dataset/uniform/uniform_6d.txt ../dataset/q/q_6d.txt ../dataset/uniform/uniform_6d_valid.txt ../result/approx_uniform_6d.txt
./build/approx 6 0.01 ../dataset/uniform/uniform_6d.txt ../dataset/q/q_6d.txt ../dataset/uniform/uniform_6d_valid.txt ../result/approx_uniform_6d.txt

timeout 12h ./build/approx 9 0.05 ../dataset/Color.txt ../dataset/q/q_9d.txt ../dataset/Color_valid.txt ../result/approx_Color.txt
timeout 12h ./build/approx 9 0.025 ../dataset/Color.txt ../dataset/q/q_9d.txt ../dataset/Color_valid.txt ../result/approx_Color.txt
timeout 12h ./build/approx 9 0.01 ../dataset/Color.txt ../dataset/q/q_9d.txt ../dataset/Color_valid.txt ../result/approx_Color.txt
