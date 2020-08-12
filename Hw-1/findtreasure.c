#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*This function takes output file argument and output array as parameters 
and write this array to the output file*/

void output(char* arg,int visited[]){
	
	int counter=visited[4];
	int i=0;
	FILE *fptr;
   	fptr = fopen(arg,"w");
   	for(i=5;i<counter;i=i+3){
   		fprintf(fptr,"%d,%d:%d\n",visited[i],visited[i+1],visited[i+2]); 
	   }
	fclose(fptr);
	
   	
}
	/*	"move" is a recursive function.Key moves(directions) are determine by this function.
	*/
void move(int **map_matrix,int **key_matrix,int visited[],int rom,int com,char* arg){
	
	int key_size=visited[0];
	int mapi=visited[1];
	int mapj=visited[2];
	int result=visited[3];
	int counter=visited[4];
	
	int sum=0;
	int i=0,j=0;
		
		/*	direction is computed by taking mod five of matrix multiplication   
		 	RESULT=0 	=>	FOUND TREASURE
			RESULT=1 	=>	GO UP
			RESULT=2  	=>	GO DOWN
			RESULT=3	=>	GO RIGHT
			RESULT=4	=>	GO LEFT
			RESULT=5	=>	FIRST SUB-MATRIX
		*/
		
	if(result==0){
		output(arg,visited); // Call the function output for file writing
		exit(0);
	}
	
	switch(result){
		case 1:
			mapi-=key_size;
			if(mapi<0){		//	CHECK THE BOUNDARY OF MAP MATRIX
				result=2;
				visited[3]=result;
				move(map_matrix,key_matrix,visited,rom,com,arg);
			}
			
				for(i=0;i<key_size;i++){
					for(j=0;j<key_size;j++){
					sum+=(map_matrix[mapi+i][mapj+j]*key_matrix[i][j]);
					}
				}
				result=sum%5;
				if(result==2){
					result=1;
				}
				visited[3]=result;
				visited[1]=mapi;
		
				visited[counter]=mapi+(key_size/2);		//	CENTER ROW INDICE OF SUBMATRIX
				visited[counter+1]=mapj+(key_size/2);	//	CENTER COLUMN INDICE OF SUBMATRIX
				visited[counter+2]=sum;					//	SUM OF MATRIX MULTIPLICATION
				counter+=3;
		
				visited[4]=counter;
				break;
	
		case 2: 
			mapi+=key_size;

			if(mapi>rom-1){	//	CHECK THE BOUNDARY OF MAP MATRIX
				result=1;
				visited[3]=result;
				move(map_matrix,key_matrix,visited,rom,com,arg);
			}
				for(i=0;i<key_size;i++){
					for(j=0;j<key_size;j++){
					sum+=(map_matrix[mapi+i][mapj+j]*key_matrix[i][j]);
					}
				}
				result=sum%5;
				
				if(result==1){
					result=2;
				}
				
				visited[3]=result;
				visited[1]=mapi;
		
				visited[counter]=mapi+(key_size/2);		//	CENTER ROW INDICE OF SUBMATRIX
				visited[counter+1]=mapj+(key_size/2);	//	CENTER COLUMN INDICE OF SUBMATRIX
				visited[counter+2]=sum;					//	SUM OF MATRIX MULTIPLICATION
				counter+=3;
		
				visited[4]=counter;
			break;
		
		case 3:
			mapj+=key_size;
			if(mapj>com-1){	//	CHECK THE BOUNDARY OF MAP MATRIX
				result=4;
				visited[3]=result;
				move(map_matrix,key_matrix,visited,rom,com,arg);
			}
				for(i=0;i<key_size;i++){
					for(j=0;j<key_size;j++){
						sum+=(map_matrix[mapi+i][mapj+j]*key_matrix[i][j]);
					}
				}
				result=sum%5;
				if(result==4){
					result=3;
				}
				visited[3]=result;
				visited[2]=mapj;
		
				visited[counter]=mapi+(key_size/2);		//	CENTER ROW INDICE OF SUBMATRIX
				visited[counter+1]=mapj+(key_size/2);	//	CENTER COLUMN INDICE OF SUBMATRIX
				visited[counter+2]=sum;					//	SUM OF MATRIX MULTIPLICATION
				counter+=3;
		
				visited[4]=counter;
			break;
		
		case 4:
			mapj-=key_size;
			if(mapj<0){	//	CHECK THE BOUNDARY OF MAP MATRIX
				result=3;
				visited[3]=result;
				move(map_matrix,key_matrix,visited,rom,com,arg);
			}
				for(i=0;i<key_size;i++){
					for(j=0;j<key_size;j++){
						sum+=(map_matrix[mapi+i][mapj+j]*key_matrix[i][j]);
					}
				}
				result=sum%5;
				if(result==3){
					result=4;
				}
			
				visited[3]=result;
				visited[2]=mapj;
		
				visited[counter]=mapi+(key_size/2);		//	CENTER ROW INDICE OF SUBMATRIX
				visited[counter+1]=mapj+(key_size/2);	//	CENTER COLUMN INDICE OF SUBMATRIX
				visited[counter+2]=sum;					//	SUM OF MATRIX MULTIPLICATION
				counter+=3;
		
				visited[4]=counter;
				break;
		
		case 5:
				for(i=0;i<key_size;i++){
					for(j=0;j<key_size;j++){
						sum+=(map_matrix[i][j]*key_matrix[i][j]);	
					}
				}
				result=sum%5;
				visited[3]=result;
		
				visited[counter]=mapi+(key_size/2);		//	CENTER ROW INDICE OF SUBMATRIX
				visited[counter+1]=mapj+(key_size/2);	//	CENTER COLUMN INDICE OF SUBMATRIX
				visited[counter+2]=sum;					//	SUM OF MATRIX MULTIPLICATION
				counter+=3;
			
				visited[4]=counter;
			break;
	}
	move(map_matrix,key_matrix,visited,rom,com,arg);
}


int main(int argc, char *argv[]){

	
	int rom,com;		//ROW SIZE OF MAP MATRIX & COLUMN SIZE OF MAP MATRIX
  	sscanf( argv[1], "%dx%d",&rom,&com);
	
	int sizeofkey=atoi(argv[2]);	//	SIZE OF KEY MATRIX
	
	FILE *fp,*fp2;
	char ch;
	int i=0,j=0,a=0,b=0;
	int mapi=0,mapj=0,result=5,counter=5; 	// (mapi,mapj) -> KEEP TRACK OF THE LOCATIONS IN THE MAP MATRIX
											//"result" -> determines direction 
											//"counter" -> keeps size of the visited array
	int *visited;
	visited=(int *)malloc(((rom*com/sizeofkey)+5)*sizeof(int));
	
	visited[0]=sizeofkey;
	visited[1]=mapi;
	visited[2]=mapj;
	visited[3]=result;					
	visited[4]=counter;
	
	//	DYNAMIC MEMORY ALLOCATIONS	
	int *key_elements;
	key_elements=(int *)malloc((sizeofkey*sizeofkey)*sizeof(int));
	
	int *map_elements;
	map_elements=(int *)malloc((rom*com)*sizeof(int));
	
	int** key_matrix;
	key_matrix=(int **)malloc(sizeofkey*sizeof(int*));
	for(a=0;a<sizeofkey;a++){
		key_matrix[a]=(int *)malloc(sizeofkey*sizeof(int));
	}
	int** map_matrix;
	map_matrix= (int **)malloc(rom*sizeof(int*));
	for(a=0;a<rom;a++){
		map_matrix[a]=(int *)malloc(com*sizeof(int));
	}
	
	
	fp=fopen(argv[3],"r");	// mapmatrix.txt
	fp2=fopen(argv[4],"r");	// keymatrix.txt
	
	if(fp!=NULL){
	a=0,b=0;
		while(!feof(fp)){  
        	fscanf(fp, "%d", &map_elements[b]);	/*	READ ALL VALUES FROM MAP MATRIX AS INTEGERS AND 
													STORE THEM IN AN (ONE DIMENSIONAL) ARRAY NAMED "map_elements"*/
        	b++;
		}
		for(i=0;i<rom;i++){
			for(j=0;j<com;j++){
				map_matrix[i][j]=map_elements[a];	// "map_matrix" KEEPS THE MAP ELEMENTS 
				a++;
			}		
		}	
	}
	else{
		printf("File not found!");
	}
	b=0,a=0;
	
	if(fp2!=NULL){
		while (!feof(fp2)){   
            fscanf(fp2, "%d", &key_elements[b]);	/*	READ ALL VALUES FROM KEY MATRIX AS INTEGERS AND 
													STORE THEM IN AN (ONE DIMENSIONAL) ARRAY NAMED "key_elements"*/
            b++;
        }
	}
	else{
		printf("File not found!");
	}

	for(i=0;i<sizeofkey;i++){
		for(j=0;j<sizeofkey;j++){
			key_matrix[i][j]=key_elements[a];	// "key_matrix" KEEPS THE KEY ELEMENTS 
			a++;
		}
	}	
	
	move(map_matrix,key_matrix,visited,rom,com,argv[5]);

	//	"free" FUNCTION DEALLOCATES THE MEMORY
	for(a=0;a<rom;a++){
		free(map_matrix[a]);
	}
	free(map_matrix);
	free(map_elements);
	
	
	for(a=0;a<sizeofkey;a++){
		free(key_matrix[a]);
	}
	free(key_matrix);
	free(key_elements);
	free(visited);
	
	fclose(fp);	
	fclose(fp2);
}
