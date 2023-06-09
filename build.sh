#!/bin/bash

SRC_ROOT=${PWD}
MQTT_INSTALL_PATH=$SRC_ROOT

[ -f Makefile ] && make clean
rm -rf Makefile CMakeFiles CMakeCache.txt cmake_install.cmake \
CPackConfig.cmake CPackSourceConfig.cmake src/CMakeFiles src/Makefile \
src/CMakeCache.txt src/cmake_install.cmake src/CPackConfig.cmake \
src/CPackSourceConfig.cmake src/*.so susi-mapper/CMakeFiles susi-mapper/Makefile \
susi-mapper/cmake_install.cmake

## clean 
if [ "x$1" = "xclean" ];then
	echo "[clean Done]!" 
	exit 0
fi

cd  ${SRC_ROOT}
cmake . -DCMAKE_INSTALL_PREFIX=${MQTT_INSTALL_PATH}/out

make 
make install
