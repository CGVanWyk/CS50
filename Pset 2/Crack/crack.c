//To use the function crypt()
#define _XOPEN_SOURCE
#include <unistd.h>
#include<cs50.h>
#include<stdio.h>
#include<string.h>
//To include usage of functions isupper, islower, and isalpha
#include <ctype.h>

int main(int argc, string argv[])
{

	//Check whether there is only a single command-line argument passed when running ./crack
	if (argc != 2)
	{
		printf("The program only accepts a single command-line argument. Please re-run the program and insert a hash as an argument\n");
		return 1;
	}
	string hash = argv[1];
	string encryptedHash;
	char arrChars[3] = {hash[0], hash[1], '\0'};
	string salt = arrChars;
	char password[6];
	password[5] = '\0';
	for (int i = 0; i < 52; i++)
	{
		for (int j = 0; j < 52; j++)
		{
			for (int k = 0; k < 52; k++)
			{
				for (int l = 0; l < 52; l++)
				{
					for (int m = 0; m < 52; m++)
					{
						//For loop Begins
						if (strcmp(password, "") == 0)
						{
							password[0] = 'a';
						}
						else
						{
							if (m > 24)
							{
								if (m == 25)
								{
									password[0] = 'A';
								}
								else
								{
									if (password[0] == 'Z')
									{
										password[0] = 'a';
									}
									else
									{
										password[0]++;
									}

								}
							}
							//Split Uppercase Letters(^) and Lowercase Letters(v)
							else
							{
								password[0]++;
							}
						}
						if (strcmp(crypt(password, salt), hash) == 0)
						{
							printf("Password found: %s", password);
							return 1;
						}
					}
					//For loop Begins
					if (strcmp(&password[1], "") == 0)
					{
						password[1] = 'a';
					}
					else
					{
						if (l > 24)
						{
							if (l == 25)
							{
								password[1] = 'A';
							}
							else
							{
								if (password[1] == 'Z')
								{
									password[1] = 'a';
								}
								else
								{
									password[1]++;
								}

							}
						}
						//Split Uppercase Letters(^) and Lowercase Letters(v)
						else
						{
							password[1]++;
						}
					}
					if (strcmp(crypt(password, salt), hash) == 0)
					{
						printf("Password found: %s\n", password);
						return 1;
					}
				}
				//For loop Begins
				if (strcmp(&password[2], "") == 0)
				{
					password[2] = 'a';
				}
				else
				{
					if (k > 24)
					{
						if (k == 25)
						{
							password[2] = 'A';
						}
						else
						{
							if (password[2] == 'Z')
							{
								password[2] = 'a';
							}
							else
							{
								password[2]++;
							}

						}
					}
					//Split Uppercase Letters(^) and Lowercase Letters(v)
					else
					{
						password[2]++;
					}
				}
				if (strcmp(crypt(password, salt), hash) == 0)
				{
					printf("Password found: %s\n", password);
					return 1;
				}
			}
			//For loop Begins
			if (strcmp(&password[3], "") == 0)
			{
				password[3] = 'a';
			}
			else
			{
				if (j > 24)
				{
					if (j == 25)
					{
						password[3] = 'A';
					}
					else
					{
						if (password[3] == 'Z')
						{
							password[3] = 'a';
						}
						else
						{
							password[3]++;
						}
					}
				}
				//Split Uppercase Letters(^) and Lowercase Letters(v)
				else
				{
					password[3]++;
				}
			}
			if (strcmp(crypt(password, salt), hash) == 0)
			{
				printf("Password found: %s\n", password);
				return 1;
			}
		}
		//For loop Begins
		if (strcmp(&password[4], "") == 0)
		{
			password[4] = 'a';
		}
		else
		{
			if (i > 24)
			{
				if (i == 25)
				{
					password[4] = 'A';
				}
				else
				{
					if (password[4] == 'Z')
					{
						password[4] = 'a';
					}
					else
					{
						password[4]++;
					}

				}
			}
			//Split Uppercase Letters(^) and Lowercase Letters(v)
			else
			{
				password[4]++;
			}
		}
		if (strcmp(crypt(password, salt), hash) == 0)
		{
			printf("Password found: %s\n", password);
			return 1;
		}
	}
	return 0;
}