#!/bin/bash

find . -name "*.html" -type f -exec rm -v {} \;


for url in $(cat $1) 
do
	wget -c -r --no-parent $url
done
