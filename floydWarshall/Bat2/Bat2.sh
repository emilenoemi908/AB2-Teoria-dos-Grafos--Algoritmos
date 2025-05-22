#!/bin/bash

echo "Testando algoritmo de Floyd-Warshall"

floyd=./floyd.bin                     
INPUT_DIR="entradas"              
GABARITO_DIR="gabarito"          
OUTPUT_DIR="saida"           

mkdir -p "$OUTPUT_DIR"            

for input_file in $INPUT_DIR/*.txt
do
    echo -e "\e[33mInstância $(basename $input_file)\e[0m"

    output_file="$OUTPUT_DIR/$(basename $input_file)"
    gabarito_file="$GABARITO_DIR/$(basename $input_file)"

    $floyd -f "$input_file" -s > "$output_file"

    diff -w "$output_file" "$gabarito_file" > /dev/null
    if [ $? -eq 0 ]; then
        echo -e "\e[32mOK\e[0m"
    else
        echo -e "\e[31mErro\e[0m"
        echo "Diferença entre $(basename $input_file):"
        diff -w "$output_file" "$gabarito_file"
    fi

    rm "$output_file"

done

rmdir "$OUTPUT_DIR"
