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


//setToZero sets Abacus to zero by freeing all PVs within.
void setToZero(struct Abacus* abacus){
	struct PlaceValue* pointer = abacus->first;
	while (pointer){
		struct PlaceValue* destroy = pointer;
		pointer = pointer->next;
		free(destroy);
	}
	abacus->len = 0;
	abacus->negative = 0;
}


//destroyAbacus frees Abacus and all PVs within it.
void destroyAbacus(struct Abacus* abacus){
	setToZero(abacus);
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

void printAbacus(struct Abacus* abacus){
	struct PlaceValue* pointer = abacus->last;
	while (pointer){
		printf("%d", pointer->value);
		pointer = pointer->prev;
	}
	printf ("\n");
}
