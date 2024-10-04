default:
	gcc -o entropy_calculator entropyV2.c -lm
	./entropy_calculator

clean:
	rm entropy_calculator
