#!/bin/sh

echo "Spustam test na scanner"

echo "Vykonavam testy"
./scanner-test Testy/test1 >>Testy/test1.o 2>Testy/1.err
./scanner-test Testy/test2 >>Testy/test2.o 2>Testy/2.err
./scanner-test Testy/test3 >>Testy/test3.o 2>Testy/3.err
./scanner-test Testy/test4 >>Testy/test4.o 2>Testy/4.err
./scanner-test Testy/test5 >>Testy/test5.o 2>Testy/5.err
./scanner-test Testy/test6 >>Testy/test6.o 2>Testy/6.err
./scanner-test Testy/test7 >>Testy/test7.o 2>Testy/7.err
./scanner-test Testy/test8 >>Testy/test8.o 2>Testy/8.err
./scanner-test Testy/test-eof >>Testy/test-eof.o 2>Testy/eof.err

echo "Porovnavam vysledky"


