#!/bin/bash

name="log_4.txt"	# Имя файла

ls -l -R / 2>/dev/null | grep "^l" | grep "$1$" > "$name"	# Поиск всех символьных 
echo "Total symbolic links: $(wc -l "$name" | cut -d' ' -f1)" >> "$name" # Вывод кол-ва символьных ссылок на данный файл
