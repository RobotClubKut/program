#include "stdio.h"
#include <conio.h>


int main(){
	
	short j,k,l,aj,ak,al;
	j=k=l=0;
	aj=ak=al=1;
	
	clrscr( ) ;

	while(1){
		do{
			j=(j==9?0:j+aj);
			k=(k==9?0:k+ak);
			l=(l==9?0:l+al);
		
			printf("\r%d %d %d",j,k,l);
			
			if(kbhit()){
				switch(getch()){
					case 'j':
						aj=0;
					break;
					case 'k':
						ak=0;
					break;
					case 'l':
						al=0;
					break;
				}
				
			}
		}while(aj+ak+al!=0);
		
		if((j==k)&&(k==l)){
			printf("‘S•”‚»‚ë‚Á‚½-\n");
		}else if((j==k)||(k==l)||(l==j)){
			printf("1kko\n");
		}
		
		aj=ak=al=1;
	}
	
	
}
