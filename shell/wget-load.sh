#!/bin/bash

BASE_PATH=$1
LIST_OF_FILENAMES=$2

while read line; 
do 
	echo "$1$line" | sed "s/ /%20/g" > temp_url_wget_load;
	url=`cat temp_url_wget_load`
	echo "loading: $url"
	wget -c $url
done < $2

rm temp_url_wget_load
