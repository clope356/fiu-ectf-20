#include "aes.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#define CBC 1
#define CTR 1
#define ECB 1
//#define DEBUG_
//#define DEBUG_WAV

void fgetnchar(char * buff,int length,FILE* file){
	
	
	for(int i = 0; i < length;i++){
		buff[i] = fgetc(file);
	}
	
}

int main(int argc,char * argv[]){
	//double time_spent = 0.0;

	//clock_t begin = clock();
	if(argc < 4){
		printf("Use: %s keypath inputfile outputfile\n",argv[0]);
		return -1;
	}	
	
	char key[16];
	FILE * key_file = fopen(argv[1],"rb");
	FILE * plain_file = fopen(argv[2],"rb");
	if(!key_file){
		printf("Couldn't open key file\n");
		return -3;
	}
	if(!plain_file){
		printf("Couldn't open plain file\n");
		return -3;
	}

	fseek(key_file,0,SEEK_END);
	int key_size = ftell(key_file);
	rewind(key_file);
	#ifdef DEBUG_
	printf("File size: %d\n",key_size);
	#endif
	if(key_file<16){
		printf("Invalid key\n");
		return -2;
	}
	for(int i = 0; i < 16; i++){
		key[i] = fgetc(key_file);
		//printf("%d\n",i);
		//if(key[i]==EOF){
		//	printf("Invalid key, must be 128 bits long\n");
		//	return -2;
		//}
	}	
	fclose(key_file);
	struct AES_ctx ctx;
	AES_init_ctx(&ctx, key);
	
	fseek(plain_file,0,SEEK_END);
	int plain_size = ftell(plain_file) - 44;
       
	rewind(plain_file);
        if(plain_size < 0){
		return -9;
	}
	#ifdef DEBUG_
	printf("File size: %d\n",plain_size);
	#endif
	char encrypted[17];
	FILE* outfile = fopen(argv[3],"wb");
	if(!outfile){
		printf("Error opening output file\n");
		return -5;
	}
	char wave_headers[45];
        fgetnchar(wave_headers,44,plain_file);
	/*if(!ret){
		printf("wave header error\n");
		return -7;
	}*/
	fwrite(wave_headers,44,1,outfile);
        #ifdef DEBUG_WAV
	for(int k = 0;k < 44;k++){
		printf("%c: 0x%x\n",wave_headers[k],wave_headers[k]);
	}
	#endif
	for(int i = 0; i < (plain_size / 16);i++){
		memset(encrypted,0,17);
		fgetnchar(encrypted,16,plain_file);
      		#ifdef DEBUG_WAV
		if(i<2){
			printf("Block : %d\n",i);
			printf("Plain\n");
			for(int k = 0;k < 16;k++){
				printf("0x%x ",encrypted[k]);
			}
			printf("\n");
		}
		#endif
		#ifdef DEBUG_
		printf("iteration: %d\n",i);
		printf("Bytes read: %s\n",encrypted);
		for(int j = 0;j < 17;j++){
			printf("%d ",encrypted[j]);
		}
		printf("\n");
		#endif
		
	
		AES_ECB_encrypt(&ctx, encrypted);
	
	
		int written = fwrite(encrypted,16,1,outfile);
		#ifdef DEBUG_WAV
		if(i<2){
			
			printf("Encrypted\n");
			for(int k = 0;k < 16;k++){
				printf("0x%x ",encrypted[k]);
			}
			printf("\n");
		}
		#endif
		#ifdef DEBUG_
		printf("Bytes written: %d\n",written);
		#endif
	}

	int padding = (plain_size % 16)-1;
	//Manually saved files add a newline at end, annoying.
	if(padding){
		memset(encrypted,0,17);
		fgetnchar(encrypted,padding,plain_file);
		#ifdef DEBUG_
		printf("Bytes read: %s\n",encrypted);
		for(int j = 0;j < 17;j++){
			printf("%d ",encrypted[j]);
		}
		printf("\n");
		#endif
		AES_ECB_encrypt(&ctx, encrypted);
		int written = fwrite(encrypted,16,1,outfile);
		#ifdef DEBUG_
		printf("Bytes written: %d\n",written);
		#endif
	}
	/*for(int i = 0; i < plain_size;i++){
		int a = fgetc(plain_file);
		printf("%d ",a);
	}*/
	fclose(plain_file);
	fclose(outfile);
	
	
	/*clock_t end = clock();

	// calculate elapsed time by finding difference (end - begin) and
	// dividing the difference by CLOCKS_PER_SEC to convert to seconds
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Time elpased is %f seconds", time_spent);
			*/

	return 0;

}
