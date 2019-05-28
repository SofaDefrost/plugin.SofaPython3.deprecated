#!/bin/sh

sofa_src=/home/tgaugry/sofa/src/master
build_dir=/home/tgaugry/sofa/build/master/Release
sofapython3_src=$(realpath ..)
include_dirs="-I/usr/lib64/llvm5.0/lib/clang/5.0.1/include -I${build_dir}/include -I${sofa_src}/SofaKernel/framework -I${sofapython3_src}/binding -I/usr/include/python3.7m"
mkdir -p  ${build_dir}/doc
for header in ${sofapython3_src}/bindings/Sofa/src/SofaPython3/Sofa/Simulation/Binding*.h;
do
    bdir=$(dirname $header)
    bname=$(basename $header | cut -d "_" -f 2 | cut -d "." -f1)
    outname=${bname}_doc.h
    echo $header $outname $bname
    binded_file=${sofa_src}/SofaKernel/framework/sofa/simulation/${bname}.h
    ./mkdoc.py $include_dirs $binded_file > ${build_dir}/doc/$outname
done
