struct PlaceValue* createPV();

struct Abacus* createAbacus(int base);

void setToZero(struct Abacus* abacus);

void destroyAbacus(struct Abacus* abacus);

void printAbacus(struct Abacus* abacus);

void addDigit(struct Abacus* abacus, int n);
