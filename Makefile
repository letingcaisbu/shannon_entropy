default:
	gcc -o entropy_calculator entropyCalc.c -lm
	./entropy_calculator

clean:
	rm entropy_calculator
