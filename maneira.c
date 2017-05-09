#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_MAX_LEN 1024

char* getVar(char* input){
	printf("getvar - > %s\n",input);
	char *var = malloc(STR_MAX_LEN * sizeof(char));
	memset(var,'\0',STR_MAX_LEN);
	
	if(0 == strcmp(input,"var")){
		strcpy(var,"z");
	}
	else if(0 == strcmp(input,"var1")){
		strcpy(var,"z1");
	}
	else if(0 == strcmp(input,"var2")){
		strcpy(var,"z2");
	}
	else if(0 == strcmp(input,"var3")){
		strcpy(var,"z3");
	}
	
	else if(0 == strcmp(input,"varz1")){
		strcpy(var,"j1");
	}
	else if(0 == strcmp(input,"varj1z2")){
		strcpy(var,"HH");
	}
	else if(0 == strcmp(input,"varl1")){
		strcpy(var,"m1");
	}
	
	else if(0 == strcmp(input,"varm1z3")){
		strcpy(var,"ferrou");
	}
	else if(0 == strcmp(input,"varabc1z3")){
		strcpy(var,"funcionou");
	}
	
	return var;
}


char* maneira (char* sInput,char isVar, int *pos)
{	
	if (sInput[0] == '\0')
	{
		return "\0";
	}
	else if (sInput[0] == '$')
	{
		int posVelho = *pos;
		*pos += 1;
		return strcat(getVar(maneira(sInput + 1,1, pos)), maneira(sInput + *pos - posVelho,isVar, pos));
	}
	else if ((sInput[0] == '(') && (isVar)){
		*pos=*pos+1;
		return maneira(sInput + 1,isVar, pos);
	}
	else if ((sInput[0] == ')')&& (isVar))
	{
		*pos=*pos+1;
		return "";
	}
	else{
		printf("tesRRR\n");
		*pos=*pos+1;
		//char * ret = malloc(STR_MAX_LEN*sizeof(char));
		char ret[STR_MAX_LEN] = "";
		memset(ret,'\0',STR_MAX_LEN);
		ret[0]=sInput[0];
		
		strcat(ret,maneira(sInput + 1,isVar, pos));
		return ret;
	}
}


int main(){
	
	char digest[STR_MAX_LEN];
	strcpy(digest,"url=$(var1)");
	//strcpy(digest,"url=$(var$(var2))");
	//strcpy(digest,"url=$(var$(var2)TESTE)$var");//appilegal
	//strcpy(digest,"url=$(var$(var2)TESTE)$var$(var2)");//appiabc
	//strcpy(digest,"url=$(var$(var$(var1))$(var2))(oi)");//legal(oi)         //var3 = z3       var2 -> z2
																		//1z3				var1z2 ->j1
																		//abc1z3             var3 -> z3
																		//varabc1z3			var() 
//var j1 l1
	//strcpy(digest,"url=teste");
	int pos =0;
	printf(" valor ehh -> %s \n",maneira(digest,0,&pos));
	
	
}
