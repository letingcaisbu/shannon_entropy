default:
	gcc -O2 -o entropy_program entropyV2.c -lm
	./entropy_program

clean:
	rm -rf entropy_program 
