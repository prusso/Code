#include <stdio.h>


void GetString(char* buf, int maxLen)
{	
	int index = 0;

	for (char c = getchar(); index < (maxLen - 1) && c != '\n'; index++)
	{
		buf[index] = c;
		c = getchar();
	}

	buf[index] = '\0';
}

void ReverseString(char* buf, int maxLen)
{
	int index = 0;

	for (char c = getchar(); index < (maxLen - 1) && c != '\n'; index++)
	{
		buf[index] = c;
		c = getchar();
	}

	buf[index] = '\0';


	for (int i = index - 1; i >= 0 ; i--)
	{
		putchar(buf[i]);
	}
}

// "const correctness" - const will make it so you can't change/write into the array
void PutString( const char* pChar)
{
	for ( ; *pChar != 0; pChar++)
	{
		putchar( *pChar ); 
	}
}

void main()
{
	char stringaling[] = { 80,117,98,101,115,33,10,0 }; // null terminated string or a 'c string'
	char stringdingdong[] = { 'B', 'r', 'o', '\n',0 }; 
	// "string literal" - best way to do strings cause it reads each char automatically
	char inputMSG[] = "Input your message to be reversed: ";
	char string[] = "You typed the following text: ";
	char stringrev[] = " is the reverse of what you typed.";

	PutString( stringaling );
	PutString( stringdingdong );
	
	char buf[128];

	//GetString(buf, 128);
	//RevString(buf, 128);
	
	printf ( inputMSG );
	ReverseString(buf, 128);
	printf( stringrev );
	printf( "\n" );


}