#include "functions.h" 

struct list
{
	char alpha;
	int freq;
};

char CODES_histo[26]=CODES;

int get_position_histo(char ch)
{
	int i;
	for (i = 0; i < 26; ++i)
	{
		if(CODES_histo[i]==ch)
			break;
	}
	return i;
}
//input file is ciphertext-97 to 122
void histogram(FILE *fp, int period, int which)
{
	//array to store freq of each char
	char *freq_char=(char*)malloc(sizeof(char)*26); 
	int j;
	memset(freq_char,0,26);
	// intiliase all the freqencies to zero initilially
	struct list characters[26];
	for(j=0;j<26;j++)
	{
		characters[j].freq=0;
		characters[j].alpha=CODES_histo[j];
	}

	//read every period into a buffer
	char *read_p_bytes=(char*)malloc(sizeof(char)*period);//read period no of bytes
	memset(read_p_bytes,0,period); 
	int sum=0;
	int pos=0;
	int count;
	while(!feof(fp))
	{
		count=fread(read_p_bytes,1,period,fp);// fread reads max of period number of ele, can be less than that
		
		if(count==0)
		{
			break;
		}
		if(read_p_bytes[which]>='a' && read_p_bytes[which]<='z')
		{
			pos=get_position_histo(read_p_bytes[which]);
			characters[pos].freq++;
			sum++;
		}
		
		
	}

	//sort the structure based on freq
	int l,k;
	struct list temp;
	for(l=0;l<26;l++)
	{
		for(k=0;k<26-l-1;k++)
		{
			if(characters[k].freq<characters[k+1].freq)
			{
				temp=characters[k];
				characters[k]=characters[k+1];
				characters[k+1]=temp;
			}
		}
	}

	printf("L=%d\n", sum);
	
	for(j=0;j<26;j++)
	{
		printf("%c: %d (%2.2lf%%)\n",characters[j].alpha,characters[j].freq,(double)((double)(characters[j].freq)/(double)sum)*100);
		
	}
	free(freq_char);
	free(read_p_bytes);
}
