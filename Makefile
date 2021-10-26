moco : moco.o
		 cc -o moco moco.o
 moco.o : main.c
	 cc -c main.c -o moco.o
 clean :
	 rm moco moco.o