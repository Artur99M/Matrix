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
    echo "TEST OK!"
    exit 0
else
    echo "ERROR: ref = $ref_value, real = $value"
    exit 1
fi
