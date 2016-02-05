/*funzione che presa in ingresso una stirnga, la divida in sillabe
cvcvcv--> ogni gruppo cv forma una sillaba
vcvcvcv--> v forma una sillaba da sola e poi il resto è come il caso precedente*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//ritorna 1 se c è contenuto in s
int cins(char c, char *s){
   for(;*s!='\0';s++){
      if(*s==c)
         return 1;
   }
   return 0;

}

//ritorna 1 se c è un carattere dell'alfabeto
int ischar(char c){
   return (c>='a' && c<='z') ||(c>='A'&& c<='Z');
}

//ritorna 1 se c è una vocale
int isvocale(char c){
   return ischar(c)&&cins(c,"aeiouAEIOU");
}

//ritrona 1 se c è consonante
int iscons(char c){
   return ischar(c)&&!isvocale(c);
}

//funzione che ritorna il puntatore al primo spazio
char * findspace(char *s){
   while(ischar(*s))
      s++;
   return s;
}

//funzione che ritorna il puntatore al primo carattere della stringa s
char * findchar( char *s){
   while( !ischar(*s) && *s!='\0')
      s++;
   return s;
}

//funzione che ritorna il puntatore all'ennesima parola della stringa s
char * parola( char* s, int n ){
   s=findchar(s);
   
   for(; n>0  ; n--){   
      s=findchar(findspace(s));
      
   }
   return s;    
}

//funzione che ritorna la prima parola della stringa s
char * estraiparola(char *s){
   char *f=findspace(s);
   int dim=f-s+1;
   char* ret=malloc(sizeof(char)*dim);
   int i;
   for(i=0;i<dim-1;i++)
      ret[i]=s[i];
   ret[i]='\0';
   return ret;
}
//funzione che restituisce precisamente la ennesima parola della stringa s
char * nparola(char *s , int n){
   char *c=estraiparola(parola(s,n));
   return c;
}

//funzione che conta le parole da cui è formata la stirnga
int numero(char *s){ 
   int i=0,n=0;
   char* g=s;
   for(i;s[i]!='\0';i++){
      g=parola(s,n);
      int l=strlen(estraiparola(g));
      i=(findchar(g+l)-s)-1;
      n++;
      
   }
    return n++;  
}

//funzione che ritorna 1 se la stringa s rispetta lo schema cvcvcv
int schema1(char *s){
   int i=0,n;
   for(i;s[i]!='\0';i++){
      if(iscons(s[i])){
      	 if(isvocale(s[i+1])){
	    i++;
	    n=1;
         }
      }
      else
         n=0;
   }
   return n;
}

//funzione che ritorna 1 se la stringa s rispetta lo scheva vcvcv
int schema2(char *s){
   int i=0;
   for(i;s[i]!='\0';i++){
      if(isvocale(s[0])){
         if(schema1(s+1))
            return 1;
         else
	    return 0;
      }
      else return 0;
   }
}

//funzione che crea un array di puntatori a char
char ** convtoarray( char * s){
   int n=numero(s),i=0;
   char ** ret=malloc(sizeof(char)*n);
   for(i=0;i<n;i++)
      ret[i]=estraiparola(parola(s,i));
   ret[i]="\0";
   return ret;
   
}
//funzione che restituisce la lunghezza di un array di stringhe
int len(char ** s){
   int i=0;
   for(i;s[i]!="\0";i++);
   return i;
}
//funzione che restituisce una stringa sillabata dello schema 1 es: divagavano-->di-va-ga-va-no
char * silschema1(char *s){
   int d=strlen(s)+(strlen(s)/2);
   char * ret=malloc(sizeof(char)*d);
   int i=0,j=0;
   for(i;s[i]!='\0';i++,j++){
      if(isvocale(s[i])){
	 ret[j]=s[i];
         if(s[i+1]!='\0')
            ret[j+1]='-';
	 j++;
      }
      else
         ret[j]=s[i];
   }
   ret[d]='\0';
   return ret;
}
//funzione che restituisce una stringa sillabata dello schema 2 es:amico--> a-mi-co
char * silschema2(char* s){
   int d=strlen(s)+(strlen(s)/2)+1;
   char* ret=malloc(sizeof(char)*d);
   char * vet=silschema1(s+1);
   ret[0]=s[0];
   ret[1]='-';
   ret[2]='\0';
   ret=strcat(ret,vet);
   return ret;
}
//funzione che controlla a che tipo di schema corrisponde la parola e agisce di conseguenza
char * onesillaba(char *s){
   char* vet;
   if(schema1(s))
      vet=silschema1(s);
   else if(schema2(s))
      vet=silschema2(s);
   return vet;
}

//funzione che trasforma un array di stringhe in un'unica stringa NON FUNZIONA
char * atos( char **s ){
   int dim=len(s);
   int i=0,n=1;
   for(i;i<dim;i++)
      n=n+strlen(onesillaba(s[i]));
   char * ret=malloc(sizeof(char)*n);
   ret="";
   for(i=0;i<dim;i++)
      ret=strcat(ret,s[i]);
   ret[i]='\0';
   printf("%s",ret);
   return ret;
}




void main(){
int i=0;
/*printf("%s\n",onesillaba("amico asino    asino"));
printf("%s\n",onesillaba("edivagavano"));
printf("%s\n",onesillaba("edividere"));
printf("%s\n",onesillaba("asino"));
printf("%s\n",onesillaba("evadere"));*/
//printf("%d",len(convtoarray("ciao dani come stai")));
printf("%s",atos(convtoarray("ciao dani come stai")));
/*char *s="amico";
s=silschema2(s);
for(i=0;s[i]!='\0';i++)
   printf("%c\n",s[i]);*/

/*char* s="ciao dani come va";
char **ret=convtoarray(s);
for(i;i<numero(s);i++)
   printf("%s\n", ret[i] );*/

}
