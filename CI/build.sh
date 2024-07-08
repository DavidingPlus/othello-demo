#!/bin/bash

echo "****** Value of yml_project_dir: $yml_project_dir ******"

project_dir=$yml_project_dir
cd $project_dir

mkdir -p build
cd build

conan install ..
cmake ..
make
