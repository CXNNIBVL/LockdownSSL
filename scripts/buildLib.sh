# !/bin/bash

cd .. && \
cd ./bin/obj/ && \
g++ -Wall -Wno-sign-compare -c -I ../../include/ -g ../../lib/*/*.cpp && \
cd ../ && \
ar -rvs ./libLockdownSSL.a ./obj/*.o && \
ranlib ./libLockdownSSL.a && \
rm -r ./obj/*.o