/*
	Name: Xuanying Li
	Netid: xli146
	Lab Section: AB1
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "prog9.h"

/*
 * little_endian_2 - reads 2 bytes of little endian and reorganizes it into big endian
 * INPUTS:	     fptr - pointer to the wav file
 * OUTPUTS:	     none
 * RETURNS:	     the data that is converted to big endian
 */
int little_endian_2(FILE *fptr)
{
	int i;			/*declare variables*/
	unsigned char array[2];
	short unsigned int bige=0;
	for (i=0; i<2; i++)  
	{
		fscanf(fptr,"%c",&array[i]); /*reads the file and save to array*/
	}
	for (i=1;i>=0;i--)
	{
		bige = bige << 8; /*convert to big endian and save it*/
		bige = bige + array[i];
		
	}
  return bige;
}

/*
 * little_endian_4 - reads 4 bytes of little endian and reorganizes it into big endian
 * INPUTS:	     fptr - pointer to the wav file
 * OUTPUTS:	     none
 * RETURNS:	     the data that is converted to big endian
 */
int little_endian_4(FILE *fptr)
{
	int i; /*declare varaibles*/
	unsigned char array[4];
	short unsigned int bige=0;
	for (i=0;i<4;i++) /*reads the file and save to array*/
	{
		fscanf(fptr,"%c",&array[i]);
	}
	for (i=3;i>=0;i--)
	{
		bige = bige << 8; /*convert to big endian and save it*/
		bige = bige + array[i];
	}
  return bige;
}

/*
 * read_file  - read the wav file and fill out the wav file struct
 * INPUTS:      wavfile - a string that contains the name of the file
 * OUTPUTS:     none
 * RETURNS:     the pointer to the wav file struct created in this function
 * SIDE EFFECT: prints the information stored in the wav struct
 */
WAV *read_file(char *wavfile)
{
WAV* wav_ptr=(WAV *)malloc(sizeof(WAV));	/*declare varaibles*/
FILE* fptr=fopen(wavfile,"r");		/*open file for read*/
int i;

	printf("RIFF:");	/*read and print RIFF*/
	for (i=0;i<4;i++)
	{
		fscanf(fptr,"%c",&(wav_ptr->RIFF[i]));
		printf("%c", wav_ptr->RIFF[i]);
	}
	printf("\n");

	wav_ptr->ChunkSize=little_endian_4(fptr); 	/*read and print Chunksize*/
	printf("ChunkSize:%d\n", wav_ptr->ChunkSize);

	printf("WAVE:"); 	/*read and print wave*/
	for (i=0;i<4;i++)
	{
		fscanf(fptr,"%c",&(wav_ptr->WAVE[i]));
		printf("%c", wav_ptr->WAVE[i]);
	}
	printf("\n");

	printf("fmt:");	/*read and print fmt*/
	for (i=0;i<4;i++)
	{
		fscanf(fptr,"%c",&(wav_ptr->fmt[i]));
		printf("%c",wav_ptr->fmt[i]);
	}
	printf("\n");

	wav_ptr->Subchunk1Size=little_endian_4(fptr);	/*read and print subchunksize*/
	printf("Subchunk1Size:%d\n",wav_ptr->Subchunk1Size);

	wav_ptr->AudioFormat=little_endian_2(fptr);	/*read and print audioformat*/
	printf("AudioFormat:%d\n",wav_ptr->AudioFormat);

	wav_ptr->NumChan=little_endian_2(fptr);		/*read and print numchan*/
	printf("NumChan:%d\n",wav_ptr->NumChan);

	wav_ptr->SamplesPerSec=little_endian_4(fptr);	/*read and print samplespersec*/
	printf("SamplesPerSec:%d\n",wav_ptr->SamplesPerSec);

	wav_ptr->bytesPerSec=little_endian_4(fptr);	/*read and print butespersec*/
	printf("bytesPerSec:%d\n",wav_ptr->bytesPerSec);

	wav_ptr->blockAlign=little_endian_2(fptr);	/*read and print blockalign*/
	printf("blockAlign:%d\n",wav_ptr->blockAlign);
	
	wav_ptr->bitsPerSample=little_endian_2(fptr);	/*read and print bitspersample*/
	printf("bitsPerSample:%d\n",wav_ptr->bitsPerSample);

	int size_extra=(wav_ptr->Subchunk1Size)-16;	/*calculate, read and save extra*/
	wav_ptr->extra=(char*)malloc(size_extra*sizeof(char));
	for (i=0;i<size_extra;i++)
	{
		fscanf(fptr,"%c",&(wav_ptr->extra[i]));

	}

	printf("Subchunk2ID:");		/*read and print subchunk2id*/
	for (i=0;i<4;i++)
	{
		fscanf(fptr,"%c",&(wav_ptr->Subchunk2ID[i]));
		printf("%c",wav_ptr->Subchunk2ID[i]);
	}
	printf("\n");

	wav_ptr->Subchunk2Size=little_endian_4(fptr);		/*read and print subchunk2size*/
	printf("Subchunk2Size:%d\n",wav_ptr->Subchunk2Size);

	int size_data=(wav_ptr->Subchunk2Size)*8/(wav_ptr->bitsPerSample);	/*calculate, read and save data*/
	wav_ptr->data=(short int*)malloc(size_data*sizeof(short int));
	for(i=0;i<size_data;i++)
	{
			wav_ptr->data[i]=little_endian_2(fptr);
	}

fclose(fptr);	/*close file*/
return wav_ptr;

}

/*
 * sloop  - create a wav file that repeats the inwav from a to b, n times
 * INPUTS:  inwav - the pointer to the wav file struct for the input file
 * 	    outfile - string containing the name of the output file
 * 	    a - start time
 * 	    b - end time
 * 	    n - number of repetitions
 * OUTPUTS: outfile
 * RETURNS: none
 */
void sloop(WAV *inwav, char *outfile, double a, double b, int n)
{	/*basically same comments as previous part */
FILE *fptr=fopen(outfile,"w");	/*open file for write*/
int i,j,temp;
unsigned short int data;
unsigned char bytes[4];


	for(i=0;i<4;i++)						
 	{
 		fprintf(fptr,"%c", inwav->RIFF[i]);
 	}
 	temp = inwav->ChunkSize;
 	
 	for(i=0;i<4;i++)						
 	{
 		bytes[i] = temp;
 		fprintf(fptr,"%c",bytes[i]);
 		temp = temp >> 8;
 	} 	
  	
  	for(i=0;i<4;i++)						
  	{
  		fprintf(fptr,"%c",inwav->WAVE[i]);
  	}
  	
  	for(i=0;i<4;i++)						
  	{
  		fprintf(fptr,"%c",inwav->fmt[i]);
  	}
  	temp = inwav->Subchunk1Size;
  	
  	for(i=0;i<4;i++)						
  	{
  		bytes[i] = temp;
  		fprintf(fptr,"%c",bytes[i]);
  		temp = temp >> 8;
  	}
  	temp = inwav->AudioFormat;

  	for(i=0;i<2;i++)						
  	{
  		bytes[i] = temp;
  		fprintf(fptr,"%c",bytes[i]);
  		temp = temp >> 8;
  	}
  	temp = inwav->NumChan;

  	for(i=0;i<2;i++)					
  	{
  		bytes[i] = temp;
  		fprintf(fptr,"%c",bytes[i]);
  		temp = temp >> 8;
  	}
  	temp = inwav->SamplesPerSec;

  	for(i=0;i<4;i++)						
  	{
  		bytes[i] = temp;
  		fprintf(fptr,"%c",bytes[i]);
  		temp = temp >> 8;
  	}
  	temp = inwav->bytesPerSec;

	for(i=0;i<4;i++)						
	{
		bytes[i] = temp;
		fprintf(fptr, "%c", bytes[i]);
		temp = temp >> 8;
	}
											
	temp = inwav->blockAlign;
	for(i=0;i<2;i++)
	{
		bytes[i] = temp;
		fprintf(fptr, "%c", bytes[i]);
		temp = temp >> 8;
	}
	temp = inwav->bitsPerSample;	

	for(i=0;i<2;i++)
	{
		bytes[i] = temp;
		fprintf(fptr, "%c",bytes[i]);
		temp = temp >> 8;
	}

											
	for(i=0;i<(inwav->Subchunk1Size)-16;i++)
	{
		fprintf(fptr, "%c", inwav->extra[i]);
	}
											
	for(i=0;i<4;i++)
	{
		fprintf(fptr, "%c", inwav->Subchunk2ID[i]);
	}
											
	temp = n*(b-a)*inwav->bytesPerSec;
	for(i=0;i<4;i++)
	{
		bytes[i] = temp;
		fprintf(fptr, "%c", bytes[i]);
		temp = temp >> 8;
	}
	
	for(j=0;j<n;j++)					
	{

		for(i=a*2*(inwav->SamplesPerSec);i<b*2*(inwav->SamplesPerSec);i++)
		{
			data = inwav->data[i];
			bytes[0] = data;
			fprintf(fptr,"%c",bytes[0]);
			data = data >> 8;
			bytes[0] = data;
			fprintf(fptr,"%c",bytes[0]);
		}
	}

  	fclose(fptr);		/*close file */
}

/*
 * find_copy - tries to find wav1 in wav2
 * INPUTS:     wav1 - pointer to the wav file struct
 * 	       wav2 - pointer to the wav file struct
 * OUTPUTS:    none
 * RETURNS:    1 if found, 0 otherwise
 */
int find_copy(WAV *wav1, WAV *wav2)
{
int i,j;
int size_1,size_2;
size_1 = (wav1->Subchunk2Size)*8/(wav1->bitsPerSample);
size_2 = (wav2->Subchunk2Size)*8/(wav2->bitsPerSample);

for (j=0;j<size_2;j++)
{
	i=0;
	while (wav1->data[i] == wav2->data[j])
	{
		if (j == size_2-1)
		{
			return 0;
		}
		if (i == size_1-1)
		{
			return 1;
		}
		i++;
		j++;
	}
}
  return 0;
}

//Extra credit
/*
 * lo_pass - applies a LPF to the wav file
 * INPUTS:   inwav - pointer to the wav file struct
 * 	     outfile - string containing the name of the output file
 * 	     freq - cutoff frequency for the low pass filter
 * OUTPUTS:  creates an outfile
 * RETURNS:  none
 */
void lo_pass(WAV *inwav, char *outfile, int freq)
{

}

