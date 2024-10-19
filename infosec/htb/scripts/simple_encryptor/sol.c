#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

unsigned char rightRol(unsigned char val, unsigned char quant) {
	return (val >> quant) | (val << (8 - quant));
}

unsigned char leftRol(unsigned char val, unsigned char quant) {
	return (val << quant) | (val >> (8 - quant));
}

void dec(FILE * fptr) {
	fseek(fptr, 0, SEEK_END);
	long size = ftell(fptr) - 4;
	rewind(fptr);

	for (int j = 0; j < 4; j++) fgetc(fptr); // Remove trash from init

	unsigned char c;
	int i = 0;
	
	while (i < size) {
		c = fgetc(fptr);
		unsigned char toXor = rand() & 0xFF;
		unsigned int toRol = rand() & 0x7;
		unsigned char dec = rightRol(c, toRol) ^ toXor; // (rightRol(c, toRol) ^ toXor);

		// if ( (i == 0 && dec != 'H') || (i == 1 && dec != 'T') || (i == 2 && dec != 'B')) break;
		if (dec <= 126 && dec >= 33) printf("%c", dec);
		i++;
	}
	puts("");
	rewind(fptr);
}

int main(int argc, char ** argv) {
	/*time_t now = time(NULL);
	time_t prev = now - (8640 * 810);
	time_t final = prev + (8640 * 50);
	time_t seed = prev;

	for (seed; seed <= final; seed++) {
		srand(seed);
		dec(fptr);
	}
	srand(now);
	printf("Seed: %d\n", now);
	dec(fptr);
	fclose(fptr);*/

	FILE * fptr = fopen(argv[1], "rb");
	long long seed = 0x62b1355a;
	srand(seed);
	dec(fptr);

	return 0;
}
