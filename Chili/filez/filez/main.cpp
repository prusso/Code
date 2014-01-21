#include <stdio.h>

void main()
{
	/* write text to a file
	FILE* pFile = fopen("foo.txt","w");

	int a = 1, b = 2;
	int c = a + b;

	fprintf(pFile, "Calculation: %d + %d = %d", a, b, c);

	fclose(pFile);
	

	// read text from a file
	FILE* pFile = fopen("foo.txt","r");

	char buffer[255];
	fscanf(pFile, "%s", buffer);


	printf("%s\n", buffer);

	fclose(pFile);

	// write binary data to a file
	FILE* pFile = fopen("foo.txt","wb");

	int data = 0x15A19BB1; // or 1337 or whatever you want
	fwrite(&data, sizeof(data), 1, pFile);

	fclose(pFile);

	// read binary data from a file
	FILE* pFile = fopen("foo.txt","rb");

	int data = 0x00000000; // or 1337 or whatever you want
	fread(&data, sizeof(data), 1, pFile);
	printf("%X\n", data);

	fclose(pFile);

	*/

	// write in binary with new lines (works fine?)
	FILE* pFile = fopen("foo.txt", "wb");

	fprintf( pFile,"line 1\nline 2\n");

	fclose(pFile);

}