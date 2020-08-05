#include <stdio.h>
#include <stdlib.h>

#define TEMP 10 
#define C_x 0.47
#define C_y 0.47
//                                                     ------STRUCT------
typedef struct{
	float *mat;	
}Matrix;

// 													    -----MODULES------

int return_lines(){
	int l;
	printf("Digite um numero para quantidade de  linhas: ");
	scanf("%d", &l);
	return l;
}

int return_colluns(){
	int c;
	printf("\nDigite um numero para quantidade de colunas: ");
	scanf("%d", &c);
	return c;
}
int return_max_value(Matrix *temp, int COL, int LIN){
	int maxValue=0,l,c;
	for(l=0;l<LIN;l++){
		for(c=0;c<COL;c++){
			if(temp->mat[l*COL+c]>maxValue){
				maxValue = temp->mat[l*COL+c];
			}			
		}
	}
	return maxValue;
}
void matrix_inicialization(Matrix *temp, int LIN, int COL){
	int l,c;
	for(l=0;l<LIN;l++){
		for(c=0;c<COL;c++){
			temp[0].mat[l * COL + c] = (l*(LIN - l -1)) * (c*(COL - c -1));			
		}
	}
	int max=return_max_value(temp, COL, LIN);
	for(l=1;l<LIN-1;l++){
		for(c=1;c<COL-1;c++){
				temp[0].mat[l * COL + c]/=max;			
		}	
	}	
}

void matrix_mapping(Matrix *temp,int LIN,int COL,int tmp){
	int l,c;
	for(l=0;l<LIN;l++){
		for(c=0;c<COL;c++){
			if((l==0)||(c==0)||(l==LIN-1)||(c==COL-1)){
				temp[tmp].mat[l*COL+c] = 0;
			}
			else{
				temp[tmp].mat[l * COL + c]= temp[tmp-1].mat[l * COL + c] + C_x*((temp[tmp-1].mat[(l+1)*COL + c])+(temp[tmp-1].mat[(l-1)*COL + c])-2.*(temp[tmp-1].mat[l * COL + c])) + C_y*((temp[tmp-1].mat[l * COL +(c+1)])+(temp[tmp-1].mat[l*COL+(c-1)])-2.*(temp[tmp-1].mat[l*COL+c]));				
			}	
				
		}
	}
}

void matrix_temp(Matrix *temp,int LIN, int COL){
	int t;
	for(t=1;t<=TEMP;t++){
		temp[t].mat = (int*) malloc (LIN*COL*sizeof(int));
		matrix_mapping(temp, LIN, COL, t);
	}
}
void print_all_matrix(Matrix *temp,int LIN,int COL){
	int l,c,tmp;
	printf("\n\n--------------- Matrix Inicial: ----------------\n\n");	
	for(tmp=0;tmp<=TEMP;tmp++){
		printf("\n\n--------------- Matrix temp_%i: ----------------\n\n",(tmp*TEMP));
		for(l=0;l<LIN;l++){
			for(c=0;c<COL;c++){
				printf(" %.2f\t", temp[tmp].mat[l * COL + c]);			
			}
			printf("\n\n");
		}
	}	
}
void free_matrixs(Matrix *temp){
	int i;
	for(i=0;i<=TEMP;i++){
		free(temp[i].mat);
	}
}
//                                                 		------MAIN------
int main(){
	//matrix dimension
	int LIN = return_lines();
	int COL = return_colluns();
	
	//creating vetor of Matrix(struct)
	Matrix temp[TEMP];
	//alocation of the initial matrix (in shape of vetor), at zero position of temp 
	temp[0].mat = (int*) malloc (LIN*COL*sizeof(int));
	
	//calls method of inicialization of values 
	matrix_inicialization(temp, LIN, COL);
	
	//calls method to return max value of temp matrix and print
	int tamanhoMax = return_max_value(temp, COL, LIN);
	//printf("Max: %.2f",tamanhoMax);
	
	//calls method that applies the function of mapping heat in the matrixs
	matrix_temp(temp,LIN,COL);
	
	//print all matrix tabulated
	print_all_matrix(temp,LIN,COL);
	
	//release all allocated memory
	free_matrixs(temp);
	
}
