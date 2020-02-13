extern void myputchar(char x);
extern char getch();
int myAtoi(char* str);
void myItoa(unsigned int num,int base, char *salida);
void myItor(unsigned int num,char *str);
void puts(char *str);
void gets(char *str);
char symbol[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
int decimal[] = {65000,60000,50000,10000,5000,1000,900,500,400,100,90,50,40,10,9,5,4,1};
int j,i;

int main(void)
{  
    puts("hola mundo");
    getch();
    
    
    return 0;
}

void myItoa(unsigned int num,int base, char *salida)
{
    char aux_string[16];
    i=0,j=0;

    if(num!=0){
     while(num){ 
            *(aux_string+i)=symbol[num%base];
            num=num/base;
            i++;
    }
        *(aux_string+i)=0;
        

        while(i)
        {
            i--;
           (*(salida+j))=aux_string[i];
           j++;

        }
        (*(salida+j))=0;
    }
    else 
    {
        
        salida[0]='0';
        salida[1]=0;
    
    }
}

int myAtoi(char* str)
{
    int res = 0; 
    
    int i = 0; 
   
    if(*str=="0")
    {
        return 0;
    }

    if(*str==" ")
    {
        return 0;
    }
  
    for (i=0; str[i] != '\0' && str[i] >= 48 && str[i] <= 57  ; ++i)
	{
        res = res * 10 + str[i] - '0';
	}
    return  res;
}



void puts(char* str)
{
    while(*str)
    {
        myputchar(*str++);
    }
}

void gets(char* str)
{
    char temp;
    int i=0;
    while((temp=getch())!='\r')
    {    
        if(temp==8 && i>0 )
        {
            i--;
            str--;
            myputchar(temp);
            myputchar(' ');
            myputchar(temp);
            
            
        }
        if(temp!=8 && i<10)
        {
            myputchar(temp);
          *(str++)=temp;
           i++;  /* code */
        
        }
       
    }
    *str=0;
}

