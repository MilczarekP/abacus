#include <stdio.h>
#include <stdlib.h>


// PlaceValue is a dll that acts as the building block for the abacus.
// The first node is the units; the second, tens; the third, hundreds; and so forth.
// value denotes digit value. Ranging from 0 to n, where n is the number system (binary, decimal, hexadecimal, etc).
struct PlaceValue {
    struct PlaceValue* prev;
    struct PlaceValue* next;
    int value;
};


//Abacus is the root of the placeValue dll.
//len refers to the digit length of the number (number of nodes).
struct Abacus {
    struct PlaceValue* first;
    struct PlaceValue* last;
    int len;
    int base;
    int negative;
};


// createPV returns pointer to newly malloced placeValue, with all values set to zero.
struct PlaceValue* createPV(){
    struct PlaceValue* give = malloc(sizeof(struct PlaceValue));
    give->prev = NULL;
    give->next = NULL;
    give->value = 0;

    return give;
}


//createAbacus creates an Abacus containing the number 0 - that is, the abacus is empty.
//int base is base n, where n is the base for the number system (base 10 for decimal, base 2 for binary etc).
struct Abacus* createAbacus(int base){
	struct PlaceValue* new = createPV();
	struct Abacus* give = malloc(sizeof(struct Abacus));
	give->first = new;
	give->last = new;
	give->len = 0;
	give->base = base;
	give->negative = 0;

	return give;
}


//isValidDigit checks if a given character fits within the limits of number base.
//base can be anywhere from base 2 to base 62. First it's digits 0-9, then a-z, and finally A-Z.
//returns 0 if false and 1 if true.
int isValidDigit(char c){
	return (c >= 48 && c <= 57 ||
		c >= 65 && c <= 90 ||
		c >= 97 && c <= 122);
}


//readInput takes char* num as well as base.
//The characers are read one by one, and checked to ensure they fit within base.
//The characters are transfered into a PlaceValue linked list (essentially a FIFO stack).
//function returns 0 if read is successful, 1 if it is not.
int readInput (char* num, int base, struct PlaceValue** linkedList){
	int i = 0;
	for (i; num[i]; i++){
		if(isValidDigit(num[i]), base){
			(&linkedList)->value = num[i];
			struct PlaceValue* temp = (&linkedList);
			&linkedList = initPV();
			(&linkedList)->next  = temp;
		}
		else return 1;
	}
	return 0;
}


//setAbacus sets abacus to number specified by variable n.
//n is a string limited to digits 0-9 and characters a-z and A-Z, contingent on the base of abacus.
void setAbacus(struct Abacus* abacus, char* n);


//destroyAbacus frees Abacus and all PVs within it.
void destroyAbacus(struct Abacus* abacus){
	struct PlaceValue* pointer = abacus->first;
	while(pointer){
		struct PlaceValue* destroy = pointer;
		pointer = pointer->next;
		free(destroy);
	}
	//setToZero(abacus);
	free(abacus);
}


//addOne is the internal mechanism for operating one digit within the abacus number system.
//only used by addDigit.
void addOne(struct Abacus* abacus){

	struct PlaceValue* current = abacus->first;

	while (!current || abacus->base - 1 == current->value){
		if(!current){
			current = createPV();
			current->prev = abacus->last;
			abacus->last->next = current;
			abacus->last = current;
			break;
		}
		current->value = 0;
		current = current->next;
	}
	current->value++;
}
	
//addDigit is performed on one PV of the abacus. It adds input to the current PV as in an abacus.
//n is limited to one digit.
void addDigit(struct Abacus* abacus, int n){
	while (n > 0){
		addOne(abacus);
		n--;
	}
}

//printAbacus prints the value held by given struct Abacus*.
void printAbacus(struct Abacus* abacus){
	struct PlaceValue* pointer = abacus->last;
	while (pointer){
		printf("%d", pointer->value);
		pointer = pointer->prev;
	}
	printf ("\n");
}
