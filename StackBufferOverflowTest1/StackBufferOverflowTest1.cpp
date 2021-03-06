// StackBufferOverflowTest1.cpp : Defines the entry point for the console application.
// Disabled security check, disabled exceptions, compiled with EHsc.

#include "stdafx.h"
#include "stdlib.h"
#include "string.h"


//When this program is run with a command line argument that overflows from the password_buffer memory into the auth_flag memory, the authentication check will return a positive number which the if statement at line 39 will accept. Thus one can get access without a correct password.

int check_authentication(char *password)
{
	int auth_flag = 0;						//If auth_flag was declared after password_buffer, the overflow this program demonstrates would not occur.
	char password_buffer[16];

	#pragma warning(suppress: 4996)			//Visual Studio knows strcpy is unsafe so we suppress the warning (should use strcpy_s to be safe).
	strcpy(password_buffer, password);

	if (strcmp(password_buffer, "brillig") == 0)	//Copies "brillig" into the C string array password_buffer.
	{
		auth_flag = 1;
	}
	if (strcmp(password_buffer, "outgrabe") == 0)
	{
		auth_flag = 1;
	}

	return auth_flag;
}


int main(int argc, char *argv[])
{
	if (argc < 2)			//Default argc value is 1 increasing for each additional argument.
	{
		printf("usage: %s <password>\n", argv[0]);			//If the user does not provide a value for hte password argument then the program will simply indicate that it needs a password argument and will then exit.
		exit(0);
	}
	if (check_authentication(argv[1]))
	{
		printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
		printf("      Access Granted.\n");
		printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	}
	else
	{
		printf("\nAccess Denied.\n");
	}

    return 0;
}

