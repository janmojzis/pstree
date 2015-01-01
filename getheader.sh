#!/bin/sh

get_headerfiles(){
  file=$1
  for header in `grep "#include " $file | grep -v ">" | grep -v "<" | cut -d '"' -f 2 | sort | uniq`;do
    echo $header
    if [ -f $header ]; then
      get_headerfiles $header
    fi
  done
}


get_headerfiles $1
