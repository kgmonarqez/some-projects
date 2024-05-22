#!/bin/bash

dir=$(realpath "${1:-DirBomb.sh}")	# Имя директории
rmdir $dir
mkdir $dir
edge=$2					# Кол-во создаваемых для исследования файлов в аргументах скрипта
echo "Start size: $(du -hsb $dir)"	# Вывод изначального размера директории
for (( i=0; i<=$edge; i++ ))		# Создание через цикл файлов в кол-ве аргумента $2
do
    touch "$dir/file_$i.txt"
    echo $i >> "$dir/file_$i.txt"
done

echo "Final size: $(du -hsb $dir)"	# Вывод конечного размера директории

for (( i=0; i<=$edge; i++ ))		# Удаление всех созданных файлов через цикл
do
    rm -f "$dir/file_$i.txt"
done

echo "Script done. Directory size after removing: $(du -hsb $dir))"
