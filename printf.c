#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/*
Program to recreate the printf function of the stdio library.
*/

// Variadic function (Which takes an indefinite number of parameters.

int print(const char* string, ...)
{

	int i;
	int j = 0;
	char *s;
	char buffer[100] = {0}; // A dynamic memory area is allocated for the string output.
	char tmp[20];
	va_list arg;
	va_start(arg, string); // We initialize the va_list structure.

	for(i = 0; string[i] != '\0'; i++)
	{
		if(string[i] == '%')
		{
			i++; // We move forward one memory box to go on the flag.
			switch(string[i])
			{
				case 'c': // Char.
				{
					buffer[j] = va_arg(arg, int);
					j++;
					break;
				}
				case 's': // String.
				{
					snprintf(tmp, sizeof(tmp), "%s", va_arg(arg, char *));
					strcpy(&buffer[j], tmp);
					j += strlen(tmp);
					break;
				}
				case 'd': // Decimal (Int).
				{
					snprintf(tmp, sizeof(tmp), "%d", va_arg(arg, int)); // We convert the integer into a chain.
					strcpy(&buffer[j], tmp); // We copy the tmp string into buffer.
					j += strlen(tmp);
					break;
				}
				case 'o': // Octal.
				{
					snprintf(tmp, sizeof(tmp), "%o", va_arg(arg, unsigned int));
					strcpy(&buffer[j], tmp);
					j += strlen(tmp);
					break;
				}
				case 'x': // Hexa.
					snprintf(tmp, sizeof(tmp), "%x", va_arg(arg, unsigned int));
					strcpy(&buffer[j], tmp);
					j += strlen(tmp);
					break;
			}
		}
		else
		{
			buffer[j] = string[i]; // We don't meet any flags.
			j++;
		}

	}
	fwrite(buffer, j, 1, stdout);
	va_end(arg);
	return j;
}

int print(const char* string, ...);

int main(void)
{
	int nombre = 2147483648;
	print("%d", nombre);
	return 0;
}

