# !/bin/bash

dir=$1
exec=$dir/build/Matrix.out
file=$2

touch $dir/test/test.txt
$exec < $file > $dir/test/test.txt
read value 0< $dir/test/test.txt
rm $dir/test/test.txt
read ref_value 0< $file.ans
if [[ $value -eq $ref_value ]]
then
    exit 0
else
    exit 1
fi
