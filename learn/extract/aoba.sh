#!/bin/bash
cd /home/yss/test/koma_ext/
export LD_LIBRARY_PATH=/home/yss/caffe_cpu/build/lib:/home/yss/cuda/cuda-11.2/lib64:
python3 ep_short_auto_py3.py /home/yss/shogi/learn/snapshots/_iter_260000.caffemodel
mv binary.txt w000000000066.txt
xz -9 -z -k w000000000066.txt
mv w000000000066.txt.xz  ../../koma_syn/weight/
