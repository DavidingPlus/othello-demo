#!/bin/bash

echo "****** Value of yml_project_dir: $yml_project_dir ******"

project_dir=$yml_project_dir
cd $project_dir

mkdir -p build
cd build

conan user lark5 -p Sinux123_ -r larkstudio
conan user lark5 -p Sinux123_ -r lark3rdparty

conan install ..
cmake ..
make
