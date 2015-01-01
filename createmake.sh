#!/bin/sh

echo "default: it"
echo

cat Makefile.templ.* 2>/dev/null

for file in `ls -1 *.c`;do
 obj=`echo "$file" | sed s/c$/o/`
 echo "$obj: \\"
 for header in `./getheader.sh $file | sort | uniq`; do
   echo "$header \\"
 done
 echo "$file \\"
 echo "compile"
 echo "	./compile $file"
 echo
done

cat Makefile.templ


