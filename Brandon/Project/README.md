# CS467 Cetus-1 AST

### Automatic Test Instructions
1. To run and view the abstract syntax tree, you need to enter the AST folder. Make sure that the make.sh bash file is executable. If it is not run
```
chmod +x make.sh
```
Then you can run the bash script with
```
./make.sh
```.

1. If you would like to run the tests individually you can run
```
make test(x)
```
, where x = 1, 2, 3, or 4. It only tests the valid test files, or else the type checker would just exit with an error and not produce a tree

### Manual Test Instructions

1. If you want to manually input Csimple code you can run
```
./csimple
```
and it will ask for input. It will continue scanning unless you enter invalid Csimple code, then it will output an error.  It will only scan/parse/type check since  it does not output to a file.
---

* If you would like to output an abstract syntax tree in a pdf, you need to have the source code in a file. Here are the steps you need need to run

---

1. ```
make csimple
```

2. ```
dos2unix [source code filename]
```

3. ```
./csimple < [source code filename] >> testoutput.out
```
 * Note: You can stop here if you just want to view the parser/scanner output

4. ```
./csimple <  [source code filename] >> testoutput.dot
```

5. ```
dot -Tps testoutput.dot > testoutput.ps
```

6. ```
Ps2pdf testoutput.ps testoutput.pdf
```
