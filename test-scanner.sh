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

echo "Porovnavam vysledky scanner, vysledky v Testy/resultX.o"
echo "chyby v teste v 1:"
diff Testy/test1.o Testy/test1.output #>>Testy/result1.o 
echo "chyby v teste 2:"
diff Testy/test2.o Testy/test2.output>>Testy/result2.o 
echo "chyby v teste 3:"
diff Testy/test3.o Testy/test3.output>>Testy/result3.o 
echo "chyby v teste 4:"
diff Testy/test4.o Testy/test4.output>>Testy/result4.o 
echo "chyby v teste 5:"
diff Testy/test5.o Testy/test5.output>>Testy/result5.o 
echo "chyby v teste 6:"
diff Testy/test6.o Testy/test6.output>>Testy/result6.o 
echo "chyby v teste 7:"
diff Testy/test7.o Testy/test7.output>>Testy/result7.o 
echo "chyby v teste 8:"
diff Testy/test8.o Testy/test8.output>>Testy/result8.o 
echo "chyby v teste 9:"
diff Testy/test-eof.o Testy/test-eof.output>>Testy/result-eof.o 