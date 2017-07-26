#include "functions.h" 


char CODES_inv[26]=CODES;

int get_char(int i)
{
	return CODES_inv[i];
}

int getPosition_inv(char ch)
{
	int i;
	for(i=0;i<26;i++)
	{
		if(CODES_inv[i]==ch)
			break;
			
	}
	return i;
}


void inverse_key(FILE *keyfile1,FILE *keyfile2)
{
	
	int lines=0;
	//count number of lines in fp_key
	char ch;
	while((ch = fgetc(keyfile1)) != EOF)
	{
		
		if(ch=='\n')
		{
			
			lines++;
		}
	}

	char *key_array[lines];

	int i;
	//initiliasing 2-D array and storing the key elements into a 2-D array
	for(i=0;i<lines;i++)
	{
		key_array[i] = (char *)malloc(sizeof(char)*27);
		key_array[i][0] = '\0';
		fread(key_array[i],1,27,keyfile2);

	
	}

	/********************finding the inversed array**********/
	char *inv_array[lines];

	for(i=0;i<lines;i++)
	{
		inv_array[i] = (char *)malloc(sizeof(char)*27);
		inv_array[i][0] = '\0';
		
	}
	int l,k;
	char ch_ele=0;//will contain each of a,b,c,d,e
	int pos=0;
	for (l= 0; l <lines; ++l)
	{
		for (k = 0; k< 26; ++k)
		{
			ch=key_array[l][k];
			pos=getPosition_inv(ch);
			ch_ele=get_char(k);
			inv_array[l][pos]=ch_ele;

		}	
	}
	for (l= 0; l <lines; ++l)
	{
		for (k= 0; k <26; ++k)
		{
			printf("%c",inv_array[l][k]);
		}
		if(l!=lines-1)
			printf("\n");
	}
	printf("\n");

	fclose(keyfile1);
	fclose(keyfile2);
}
