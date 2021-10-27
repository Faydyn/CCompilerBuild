objects = main.o src/diagnosis.o src/buffer.o src/scanner.o src/tokens.o src/symboltable.o
flags = -Wall -Werror

moco : $(objects)
		cc -o $(flags) moco $(objects)

main.o : include/diagnosis.h include/buffer.h include/scanner.h include/tokens.h
src/diagnosis.o : include/diagnosis.h include/scanner.h
src/buffer.o : include/buffer.h include/diagnosis.h
src/scanner.o : include/scanner.h include/diagnosis.h include/buffer.h
src/tokens.o : include/tokens.h
src/symboltable.o : include/symboltable.h include/scanner.h

.PHONY : clean
clean :
	 	rm moco $(objects)