#include "abacus.h"

int main(){
	struct Abacus* abacus = createAbacus(10);
	addDigit(abacus, 5);
	printAbacus(abacus);
	addDigit(abacus,15);
	printAbacus(abacus);
	addDigit(abacus, 37);
	printAbacus(abacus);
	addDigit(abacus,1139530);
	printAbacus(abacus);
	addDigit(abacus, 200000);
	printAbacus(abacus);
	destroyAbacus(abacus);
}
