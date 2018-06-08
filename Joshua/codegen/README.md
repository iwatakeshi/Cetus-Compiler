# CS467 Cetus-1 Compiler

### Automatic Test Instructions
1. In order to run our compiler with the provided Csimple test files, make sure that the make.sh bash file is executable. If it is not run
```
chmod +x make.sh
```
Then you can run the bash script with
```
./make.sh
```
.Then you can run the executables, labeled start1, start2, start3, and start4 with
```
./[executable]
```
---

1. If you would like to run the tests individually you can run
```
make test(x)
```
, where x = 1, 2, 3, or 4. Like the AST, it only tests the valid test files, or else the type checker would just exit with an error and link properly. Then you can run the corresponding executable. “./start1” or other name.

### Manual Test Instructions

1. If you want to manually input Csimple code you can run
```
./csimple
```
and it will ask for input. It will continue scanning unless you enter invalid Csimple code, then it will output an error.  It will only scan/parse/type check since  it does not output to a file.

---

* If you would like to run the full Csimple compiler. Here are the steps needed to link the Csimple source code to an executable.

---

1.
```
make csimple
```

2.
```
./csimple < [source code filename] >> testoutput.s
```

3.
```
gcc -c -m32 -o csimple.o testoutput.s
```

4.
```
gcc -c -m32 -o start.o start.c
```

5.
```
gcc -c -m32 -o start1 start.o csimple.o
```

6.
```
./start1  
```
