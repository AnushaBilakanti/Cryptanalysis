#include "functions.h" 

char CODES_crypt[26]=CODES;

int getPosition(char ch)
{
	int i;
	for(i=0;i<26;i++)
	{
		if(CODES_crypt[i]==ch)
			break;
			
	}
	return i;
}


void crypt(FILE *fp_input,FILE *fp_key1,FILE *fp_key2)
{
	if(fp_input==NULL )
	{
		fprintf(stderr, "Error-invalid input file\n");
	}
	if(fp_key1==NULL)
	{
		fprintf(stderr, "Error-invalid key file\n");
	}
	if(fp_key2==NULL)
	{
		fprintf(stderr, "Error-invalid key file\n");
	}
	else
	{
		int lines=1;
		//count number of lines in fp_key
		char ch;
		while((ch = fgetc(fp_key1)) != EOF)
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
			key_array[i] = (char *)malloc(sizeof(char)*26);
			key_array[i][0] = '\0';
			fread(key_array[i],1,27,fp_key2);

		
		}

		
		//store the entire input into array
		char * input_array=(char*) malloc(100000);
		memset(input_array,0,100000);
		int input_ctr=0;

		while((ch = fgetc(fp_input)) != EOF)
		{
			if(ch=='\n')
			{
				break;
			}
			if((ch<(char)0x20 || ch>(char)0x7e))
			{
				fprintf(stderr, "Invalid characters in text file");
				exit(0);
			}
			
			input_array[input_ctr]=ch;
			input_ctr++;
			
		}

		//encrypting
		char *encrypt_array=(char*) malloc(100000);
		memset(encrypt_array,0,100000);

		int j;
		int k_ctr=0;
		int pos;
		int size=strlen(input_array);
		for(i=0;i<size;i++)
		{
			
			if(input_array[i]>='a' && input_array[i]<='z')
			{
				pos=getPosition(input_array[i]);
				k_ctr=i%(lines-1);
				encrypt_array[i]=key_array[k_ctr][pos];
			}
			else
			{
				encrypt_array[i]=input_array[i];
			}
		}
		
		for (j=0;j<strlen(encrypt_array);j++)
		{
			printf("%c",encrypt_array[j] );
		}
		printf("\n");
		fclose(fp_input);
		fclose(fp_key1);
		fclose(fp_key2);
	}

}

