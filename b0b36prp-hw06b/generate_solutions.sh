#!/bin/sh

<<<<<<< HEAD
HW=06b
=======
HW=06
>>>>>>> 6fd26eef095bc05e5c6f24ed9a36b036b370d83a
PROGRAM=./b0b36prp-hw$HW-genref

if [ "$1" = "-osx" ]
then
   echo "Build for osx has been selected."
   PROGRAM=./b0b36prp-hw$HW-genref-osx
fi

mkdir -p files
<<<<<<< HEAD
for i in `seq 1 10`
=======
for i in `seq 1 4`
>>>>>>> 6fd26eef095bc05e5c6f24ed9a36b036b370d83a
do
   PROBLEM=files/hw$HW-$i
   echo "Generate random input '$PROBLEM.in'"
   $PROGRAM -generate > $PROBLEM.in 2>/dev/null
   echo "Solve '$PROBLEM.in' and store the reference solution to '$PROBLEM.out'"
   $PROGRAM < $PROBLEM.in > $PROBLEM.out 2>$PROBLEM.err
done
<<<<<<< HEAD
=======

echo ""
echo "Generate and solve optional assignments"

for i in `seq 1 4`
do
   PROBLEM=`printf "files/hw%sopt-$i" $HW`
   echo "Generate random input '$PROBLEM.in'"
   $PROGRAM -generate -optional > $PROBLEM.in 2>/dev/null
   echo "Solve '$PROBLEM.in' and store the reference solution to '$PROBLEM.out'"
   $PROGRAM -prp-optional < $PROBLEM.in > $PROBLEM.out 2>$PROBLEM.err
done
>>>>>>> 6fd26eef095bc05e5c6f24ed9a36b036b370d83a
