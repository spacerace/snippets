#!/bin/bash

BUILD=`cat VERINFO.h | grep BUILD | cut -d ' ' -f 3`
VERSION=`cat VERINFO.h | grep VERSION | cut -d ' ' -f 3`

BUILD=$BUILD

let x=$BUILD+1

echo "#ifndef __VERINFO_H__SHELL__" > VERINFO.h
echo "#define VERSION $VERSION" >> VERINFO.h
echo "#define BUILD $x" >> VERINFO.h
echo "#endif" >> VERINFO.h
