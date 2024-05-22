#!/bin/bash

for ((i=1; i <= $1; i++))
do
    echo -e "Клиент №$i создан"
    ./client &
done

