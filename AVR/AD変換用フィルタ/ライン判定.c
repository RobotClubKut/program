#include <stdio.h>

char line(char l3,char l2,char l1,char c,char r1,char r2,char r3){
	char m=0,p=0,s[7]={l3,l2,l1,c,r1,r2,r3};
	
	for(int i=0;i < 7;i++){
		if(m<s[i]){
			m = s[i];
			p = i;
		}
	}
	return p;
}

