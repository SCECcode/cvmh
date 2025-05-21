#!/bin/bash

## tested under ucvm/ucvm_env.sh

cd test

make run_unit >& result_unit.txt
cat result_unit.txt

p=`grep -c FAIL result_unit.txt`
if [ $p != 0 ]; then
   echo "something wrong.."
   exit 1
fi

make run_accept >& result_accept.txt
cat result_accept.txt

p=`grep -c FAIL result_accept.txt`
if [ $p != 0 ]; then
   echo "something wrong.."
   exit 1
fi

exit 0 

