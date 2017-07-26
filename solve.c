#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <openssl/md5.h> 

struct list
{
	char alpha;
	int freq;
};

char CODES_solve[26]="abcdefghijklmnopqrstuvwxyz";


int get_position_coinci(char ch)
{
	int i;
	for (i = 0; i < 26; ++i)
	{
		if(CODES_solve[i]==ch)
			break;
	}
	return i;
}



/****************average index of coincidence******************/
void solve_coincidence(FILE *fp2,int max_length)
{
	// char *read_p_bytes=(char*)malloc(sizeof(char)*5000);
	char ch;
	
	// fseek(fp2,0,SEEK_END);
	// // int file_size=ftell(fp2);
	// int L=0;
	// rewind(fp2);


	char *freq_char=(char*)malloc(sizeof(char)*26); 

	memset(freq_char,0,26);
	int j;
	for(j=0;j<26;j++)
	{
		freq_char[j]=0;
	}

	// intiliase all the freqencies to zero initilially
	struct list characters[26];

	for(j=0;j<26;j++)
	{
		characters[j].freq=0;
		characters[j].alpha=CODES_solve[j];
	}


	// calculating the total frequency and frequency of each letter
	int pos=0;
	int L=0;
	while((ch = fgetc(fp2)) != EOF)
	{
		if(ch>='a' && ch<='z')
		{
			L++;
			pos=get_position_coinci(ch);
			characters[pos].freq++;
		}
	}
	printf("Average Index of Coincidence\n");  
	printf("============================\n"); 

	printf("L=%d\n",L );

	//calculating IC
	double IC=0;
	double temp=0;
	double denominator=L*(L-1);
	for (j = 0; j < 26; ++j)
	{
		temp=temp+(double)(characters[j].freq)*(double)((double)(characters[j].freq)-1);
		
	}

	//printing the frequencies
	for(j=0;j<26;j++)
	{
		printf("f('%c')=%d\n",characters[j].alpha,characters[j].freq);
	}

	IC=IC+(temp)/denominator;
	printf("IC=%.08g\n",IC);


	//calculating E(IC)
	int t;
	double left_part;
	double right_part;
	double E;
	double L1=(double)L;
	double t1;
	for(t=1;t<=max_length;t++)
	{
		t1=(double)t;
		L1=(double)L;
		left_part=(1/t1)*(L1-t1)/(L1-1)*0.0658;
		right_part=(double)((t1-1)/t1)*(double)(L1/(double)(L1-1))*((double)(1/(double)26));
		E=left_part+right_part;
		printf("t=%d, E(IC)=%0.8g\n",t,E);
	}
	free(freq_char);
}

void auto_correlation(FILE *fp3,int max_length)
{
	fseek(fp3,0,SEEK_END);
	int f_size=ftell(fp3);
	char *read_p_bytes=(char*)malloc(sizeof(char)*f_size);

	memset(read_p_bytes,0,f_size);
	// printf("%d\n",file_size );
	
	rewind(fp3);
	char ch;
	int input_ctr=0;
	while((ch = fgetc(fp3)) != EOF)
	{
		if((ch<(char)0x20 || ch>(char)0x7e))
		{
			break;
		}
		read_p_bytes[input_ctr]=ch;
		input_ctr++;
		
	}
	int i,t;
	int count;
	printf("Auto-correlation Method\n");
	printf("=======================\n");
	for(t=1;t<=max_length;t++)
	{
		count=0;
		for(i=0;i<f_size-t;i++)
		{
			if(read_p_bytes[i]>='a' && read_p_bytes[i]<='z')
			{
				if(read_p_bytes[i]==read_p_bytes[i+t])
					count++;
			}
			
		}
		printf("t=%d, count=%d\n",t,count );
	}
	
	free(read_p_bytes);
}

void solve(FILE *fp1,FILE *fp2,FILE *fp3,int max_length)
{
	/**********************METHOD OF KASISKI***********************/
	fseek(fp1,0,SEEK_END);
	int f_size=ftell(fp1);
	char *read_p_bytes=(char*)malloc(sizeof(char)*f_size);

	// char * read_p_bytes={0};
	memset(read_p_bytes,0,f_size);
	// printf("%d\n",file_size );
	
	rewind(fp1);
	char ch;
	int input_ctr=0;
	while((ch = fgetc(fp1)) != EOF)
	{
		if((ch<(char)0x20 || ch>(char)0x7e))
		{
			break;
		}
		read_p_bytes[input_ctr]=ch;
		input_ctr++;
		
	}

	int file_size=strlen(read_p_bytes);


	char *bytes_i=NULL;
	char *bytes_j=NULL;


	bytes_i=(char*)malloc(sizeof(char)*file_size);
	bytes_j=(char*)malloc(sizeof(char)*file_size);
	memset(bytes_i,0,file_size);
	memset(bytes_j,0,file_size);

	int i,j,k;
	int len;
	int check;
	int match=0;

	printf("Kasiski Method\n"); 
 	printf("==============\n");

 	len=4;
 	for(;;)
 	{
 		match=0;
 		for(i=0;i<file_size-len;i++)
		{
			check=1;
			memcpy(bytes_i,&read_p_bytes[i],len);
			int temp;
			temp=strlen(bytes_i);
			// printf("temp%d\n",temp );
			for (k = 0; k < temp; ++k)
			{
				if(bytes_i[k]<'a' || bytes_i[k]>'z')
				{
					check=0;
					break;
				}
			}
			if(check==1)
			{
				for(j=i+1;j<file_size-len;j++)
				{
					memcpy(bytes_j,&read_p_bytes[j],len);
					if(strcmp(bytes_i,bytes_j)==0)
					{
						printf("len=%d, i=%d, j=%d, j-i=%d, %s\n",len,i,j,j-i,bytes_i);
						match=1;

					}
				}
			}
			for (k = 0; k < temp; ++k)
			{
				bytes_i[k]='\0';
			}

		}
		if (match==0)
		{
			printf("len=%d, no more matches\n",len);
			break;
		}
		else if(match==1)
		{
			len++;
		}
 	}
 	printf("\n");
 	free(read_p_bytes);
 	free(bytes_i);
 	free(bytes_j);
	solve_coincidence(fp2,max_length);
	printf("\n");
	auto_correlation(fp3,max_length);
	printf("\n");
}
