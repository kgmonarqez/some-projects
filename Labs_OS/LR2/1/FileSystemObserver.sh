#!/bin/bash

name=$(realpath "${1:-FileSystemObserver}")	# Имя создаваемого файла
rm -f $name
touch -f $name

filetypes="-dcblps"  
for (( i=0; i<${#filetypes}; i++ )); do  
	exp="^${filetypes:$i:1}"  
	`ls -lR 2>/dev/null / | grep $exp -m 1 -s > $name`  
done 
