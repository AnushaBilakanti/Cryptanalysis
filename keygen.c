#include "functions.h" 

int first_time=1;
char *md5_8byte=NULL;

char * MD5_gen(char *pphrase,int length)
{
	char md5_buf[MD5_DIGEST_LENGTH];
	int len=strlen(pphrase)+2+MD5_DIGEST_LENGTH;
	char *s=malloc(len+1);
	int i=0,m;

	MD5((unsigned char *)pphrase, (unsigned  int)strlen(pphrase), (unsigned char *)md5_buf);

	char * key_str = malloc(sizeof(unsigned char)*((2*length)+1));// used to return key stream of specified length
	
	memset(key_str,0,(2*length)+1);

	int counter;
	
	int c_str=0;
	counter=length;
	for (;;)
	{
		if(counter>0)
		{
			sprintf(&s[MD5_DIGEST_LENGTH], "%02d%s", i, pphrase);
			memcpy(s, md5_buf, MD5_DIGEST_LENGTH);
			MD5((unsigned char *)s,  (unsigned int)len,(unsigned char * )md5_buf); //returns MD5 value of s of 
			for(m=0;m<8;m++)
			{
				sprintf(&key_str[c_str], "%02x", (unsigned int)(unsigned char)md5_buf[m]);
				c_str=c_str+2;

			}
			
		}
		else
		{
			break;
		}
		counter=counter-8;
		if (++i == 100) 
				i = 0;
	}
	
	
	free(s);
	return key_str;
	
}

char * RandomInteger(char *pphrase,int length)
{
	char * temp = malloc(sizeof(char)*16);
	memset(temp,0,16);
	if(first_time==1)
	{
		md5_8byte=MD5_gen(pphrase,length);
		strncpy(temp,md5_8byte,8);
		md5_8byte+=8;
		first_time++;
		return temp;
	}
	else
	{
		strncpy(temp,md5_8byte,8);
		md5_8byte+=8;
		return temp;

	}
}
void keygen(char *pphrase,int period)
{
	
	int i,itr,R;//R will be within 25
	unsigned int L=26;
	long long X;//unsigned int is 4 bytes
	char temp;

	char *hex_md5={0};
	FILE *fp=NULL;
	fp=fopen("keyfile.txt","w");

	for(i=0;i<period;i++)
	{
		
		char state[26]="abcdefghijklmnopqrstuvwxyz";
		for(itr=0;itr<2;itr++)
		{
			L=26,X=0,R=0;
			while(L>1)
			{
				hex_md5=RandomInteger(pphrase,period*2*25*4);
				X=strtoll(hex_md5,NULL,16);//strtol converts hexastring to int
				R=(int)(X%L);
				if(R!=(L-1))
				{
					temp=state[R];
					state[R]=state[L-1];
					state[L-1]=temp;
				}
				L=L-1;
			}
		}
		printf("%s\n", state);
		// fputs(state,fp);
		fwrite(state,1,strlen(state),fp);
		fputs("\n",fp);

	}
	fclose(fp);
	
}
