#include "functions.h"

int main(int argc, char const *argv[])
{

	char *pphrase;
	char *ch_period;//period is in char
	int period;//period is in int

	char * keyfile;

	char *ch_which_pos;//position is in char
	int which_pos;//position is in int

	char *ch_max_len;//position is in char
	int max_len;//position is in int
	
	if(argc<3 || argc>5)
	{
		fprintf(stderr, "Error-invalid input\n");
	}
	if(strcmp(argv[1],"keygen")==0)//key generation
	{
		if(argc!=4) 
		{
			fprintf(stderr, "Error-invalid input\n");
		} 
		else
		{
			if(argv[2][1]=='p')
			{
				pphrase = strchr(argv[2], '=');
				pphrase++;
				if(strcmp(pphrase," ")==0)
				{
					fprintf(stderr, "Key Phrase is empty\n");
				}
				
			}
			if (argv[3][1]=='t')
			{
			
				ch_period = strchr(argv[3], '=');
				ch_period++;
				period = atoi(ch_period);
				keygen(pphrase,period);
			}
			if(argv[3][1]=='p')
			{
				pphrase = strchr(argv[3],'=');
				pphrase++;
			}
			if (argv[2][1]=='t')
			{
				ch_period = strchr(argv[3], '=');
				ch_period++;
				period = atoi(ch_period);
				keygen(pphrase,period);
			}
		}
	}
	if(strcmp(argv[1],"crypt")==0)//encryption/decryption
	{
		
		FILE*fp_key1=NULL;
		FILE*fp_key2=NULL;
		if (argv[2][1]=='k')
		{
		
			keyfile = strchr(argv[2], '=');
			keyfile++;
			
			fp_key1=fopen(keyfile,"rb");
			fp_key2=fopen(keyfile,"rb");

		}
		if(argc==4)
		{
			FILE *fp=NULL;
			fp=fopen(argv[3],"r"); //contains the ASCII file
			crypt(fp,fp_key1,fp_key2);
		}
		else//if no input file is given 
		{
			crypt(stdin,fp_key1,fp_key2);
		}
	
	}
	if(strcmp(argv[1],"invkey")==0)//stream
	{
		if(argc!=3) 
		{
			fprintf(stderr, "Error-invalid input\n");
		} 
		else
		{
			if(argv[2]==NULL)
			{
				fprintf(stderr, "Error-invalid input\n");
			}
			else
			{
				FILE *keyfile1 = NULL;
				FILE *keyfile2 = NULL;
				keyfile1 = fopen(argv[2], "r");
				keyfile2 = fopen(argv[2], "r");

				if(keyfile1==NULL && keyfile2==NULL)
				{
					fprintf(stderr, "Error-invalid key file\n");
				}
				else
				{
					inverse_key(keyfile1,keyfile2);
				}
			}
		}
	}
	if(strcmp(argv[1],"histo")==0)//stream
	{
		if(argc<4 || argc>5) 
		{
			fprintf(stderr, "Error-invalid input\n");
		
		} 
		else
		{
			if(argv[2][1]=='t')
			{
				ch_period = strchr(argv[2], '=');
				ch_period++;
				period = atoi(ch_period);
				
			}
			if (argv[3][1]=='i')
			{
				ch_which_pos = strchr(argv[3], '=');
				ch_which_pos++;
				which_pos = atoi(ch_which_pos);
			}
			if(argv[3][1]=='t')
			{
				ch_period = strchr(argv[2], '=');
				ch_period++;
				period = atoi(ch_period);
			}
			if (argv[2][1]=='i')
			{
				ch_which_pos = strchr(argv[2], '=');
				ch_which_pos++;
				which_pos = atoi(ch_which_pos);
			}
			if(argc==5)
			{
				FILE *fp=NULL;
				fp=fopen(argv[4],"r");
				which_pos=which_pos-1;
				histogram(fp,period,which_pos);
			}
			else//if no input file is given 
			{
				which_pos=which_pos-1;
				histogram(stdin,period,which_pos);
			}
		}
	}
	if(strcmp(argv[1],"solve")==0)//stream
	{
		if(argc!=4) 
		{
			fprintf(stderr, "Error-invalid input\n");
		
		} 
		else
		{
			if(argv[2][1]=='l')
			{
				ch_max_len = strchr(argv[2], '=');
				ch_max_len++;
				max_len = atoi(ch_max_len);
				
			}
			else
			{
				fprintf(stderr, "Error-invalid input\n");
			}
			if(argc==4)
			{
				FILE *fp1=NULL;
				FILE *fp2=NULL;
				FILE *fp3=NULL;
				fp1=fopen(argv[3],"r");
				fp2=fopen(argv[3],"r");
				fp3=fopen(argv[3],"r");
				solve(fp1,fp2,fp3,max_len);
			}
			else//if no input file is given 
			{
				fprintf(stderr, "Error-invalid input\n");
			}
		}
	}


	
	return 0;
}

