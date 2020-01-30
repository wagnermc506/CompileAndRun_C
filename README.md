## CompileAndRun_C

It's just a Command Line App for compile and run c-code on the same command.

It's quite as limited, it's my first CLI attempt.

First compile the <i>compile.c</i> file with

```
gcc compile.c -o compile
```

and run typing the arguments below. It must have another c file to compile and run on the folder

```
./compile [inputfile.c] -o outputfile
```

You can ommit the "-o outputfile". Just as in gcc, if it's ommited, the binary file will be named as "a.out"