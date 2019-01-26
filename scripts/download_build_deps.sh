#!/bin/bash
# Copyright (C) tkornuta, IBM Corporation 2015-2019
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Assumes that:
# - ROOT_DIR is the root of the project. 
# - ROOT_DIR/deps/ DOES NOT exist.
# - ROOT_DIR/mic/ DOES NOT exist.
# - script is executed in ROOT_DIR (starts and ends in that dir).

# Stop the script on first error.
set -e

source ./scripts/download_release.sh
modules=( "mi-toolchain" "mi-algorithms" )
versions=( "v1.1.1" "v1.2.1" )

# Make dirs.
rm -Rf deps mic # just in case
mkdir mic
mkdir deps

# Iterate over list of modules.
cd deps
for ((i=0;i<${#modules[@]};++i))
do
    module=${modules[i]}
    version=${versions[i]}
    # Clone, configure and install module.
    download_release IBM ${module} ${version}
    mkdir ${module}/build
    cd ${module}/build
    echo "Compile "
    # Overwrite compiler!
    if [[ "${COMPILER}" != "" ]]; then export CXX=${COMPILER}; fi
    cmake .. -DCMAKE_INSTALL_PREFIX=../../../mic/
    make install
    cd ../..
    echo "${module} installed"
done
cd ..
