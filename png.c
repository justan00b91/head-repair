#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<errno.h>

// The Max Size of PNG image is assumed to be 16 MB
#define MAX_SIZE (1024 * 1024 * 1024)

// ================
// Error Function
// ================
void errExit(char* msg, ...) {
	fprintf(stderr, "ERROR: %s\n", msg);
	exit(EXIT_FAILURE);
}

void head_rep() {
	printf("TODO\n");
}

// ================
// Checking PNG file
// ================ 
int chk(char* buf) {
	int flag = 0;
	uint8_t png_header[] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };

	printf("Checking PNG Headers ...\n");
	for (int i=0; i<8; i++){
		if ( (uint8_t)png_header[i] != (uint8_t)buf[i] ) {
			printf("%02X != %02X\n", (uint8_t)png_header[i], (uint8_t)buf[i]);
			flag = 1;
		}
		else {
			printf("%02X == %02X\n", (uint8_t)png_header[i], (uint8_t)buf[i]);
		}
	}
	return flag;
}

// ================
// Main Fucntion
// ================
int main(int argc, char* argv[]) {
	if (argc != 2 || strcmp(argv[1],"--help") == 0) {
		printf("Usage: %s <file>.png\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	char usr_c;
	char* buf = (char*) malloc(MAX_SIZE);
	FILE* img = fopen(argv[1], "rb");
	if ( !img ) {
		errExit("Counld not open file.");
	}
	if ( fread(buf, 1, MAX_SIZE, img) == -1) {
		errExit("Cannot read file.");
	}
	if ( chk(buf) == 1 ) {
		printf("Initiate Head Repair?(Y/n)\n");
		scanf("%c",&usr_c);
	}

	if ( (usr_c == 'Y' ) || (usr_c == 'y') ) {
		head_rep();
	}

	else {
		printf("Exiting...\n");
	}

	return EXIT_SUCCESS;
}
