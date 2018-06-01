CS467

To compile the program, run "make" in the file.

Please follow the instructions below to use the premade test files.

## Scanner/Parser

If you want to manually input csimple code you can run ./csimple and it will ask for input

Else if you want to run any of the tests files individually then run "make removeDos" first, then "./csimple < tests/[filename]".

## AST Generation

To create the AST run "make test2pdf"

## Typechecker

Make sure that the make.sh bash file is executable. If it is not run "chmod +x make.sh"

Run the bash script with "./make.sh". It will automatically run the scanner/parser and give out any errors. The AST's are also generated. A build.log is created to view the errors. You can also visualize the errors from the AST whether one was created or not, since the Type checker uses the AST to check for errors.

## Compiler

Make sure that the make.sh bash file is executable. If it is not run "chmod +x make.sh"

Run the bash script with "./make.sh". Sames steps to creating above, but any errors are outputted to the build.log file. Make sure there is a start.c file so you can gather the integer return expressions. The Intermediate Representation created by codegen.c is in the ".s" files, is assembled/compiled by gcc, but is unlinked. We then use the start program to link it with the csimple object to create an executable. 
