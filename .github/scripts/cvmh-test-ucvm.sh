#!/bin/bash

## tested under ucvm/ucvm_env.sh

cd test

make run_unit |& tee result_unit.txt

p=`grep -c failed result_unit.txt`
if [ $p != 0 ]; then
   echo "something wrong.."
   exit 1
fi

exit 0 

