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
struct Abacus* createAbacus(int base, char* n){
    struct Abacus* give = malloc(sizeof(struct Abacus));
    give->first = NULL;
    give->last = NULL;
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

int main(){
    struct PlaceValue* lols = initPV();
    printf("%d", lols->value);
    int un = 0;
    int dec = 0;
    int cent = 0;

    int set = 2;
    int i = 1;
    int n = set * 10;

    while (1){
        if (un == (set - 1) && dec == (set - 1)){
            dec = 0;
            un = 0;
            cent++;
        }
        else if (un == (set - 1)){
            dec++;
            un = 0;
        }
        else un++;
        printf("%d%d%d", cent, dec, un);
        i++;
        if (i>n) break;
        if (i%set == 1) printf("\n");
        else printf(", ");
    }

}
