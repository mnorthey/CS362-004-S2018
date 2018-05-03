#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	int randNum = 95 * (rand() / (RAND_MAX + 1.0));
	randNum += 32;
	
	char randChar = (char) randNum;
	
	return randChar;
}

char *inputString()
{
    int i;
	int length = 5;
	char *str = malloc(sizeof(char) * (length + 1));
    
	for (i = 0; i < length; i++)
	{
		/**************
		int randNum = 26 * (rand() / (RAND_MAX + 1.0));
		randNum += 97;
		
		char randChar = (char) randNum;
		
		str[i] = randChar;
		***************/
		
		int randNum = 4 * (rand() / (RAND_MAX + 1.0));
		
		if (randNum == 0)
		{
			str[i] = 'r';
		}
		else if (randNum == 1)
		{
			str[i] = 'e';
		}
		else if (randNum == 2)
		{
			str[i] = 's';
		}
		else if (randNum == 3)
		{
			str[i] = 't';
		}
	}
	
	str[5] = '\0';
	
	return str;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  clock_t start_t = time(0);	// Added
  while (1 && difftime(time(0), start_t) < 300)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
