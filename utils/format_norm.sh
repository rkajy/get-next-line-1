#!/bin/bash

mapfile -t c_files < <(find src -type f -regex ".*\.c")

for file in "${c_files[@]}"; do
  echo "formatting C file: $file"
  # You can perform operations on $file here, e.g.:
  c_formatter_42 "$file"
done

c_formatter_42 src/libft.h