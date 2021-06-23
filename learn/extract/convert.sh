#!/bin/bash

if [ $# != 1 ]; then
  echo "no filename"
  exit 1
fi

export LD_LIBRARY_PATH=/home/yss/caffe_cpu/build/lib:/home/yss/cuda/cuda-11.2/lib64:
python3 ep_short_auto_py3.py $1
