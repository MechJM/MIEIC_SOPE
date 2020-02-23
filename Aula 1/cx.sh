rm -f $1 $1.o
gcc -Wall -o $1 $1.c || echo "COMPILATION ERROR"
./$1 $2 $3