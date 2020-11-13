#define segment_num 0x280
extern unsigned char peek(unsigned int segment,unsigned int offset);
extern void poke(unsigned int segment,unsigned int offset, unsigned char data) ;
extern void putchar(char x);
extern char getch(); 
void gets(char *str,char secret);
void puts(char *str);
void itoa(unsigned int number, char* str, unsigned char base);
unsigned int atoi(char *str);
void test_bus_lines();
int  test_direct_lines();
void test_mem_range();
unsigned char salida[20];

int main()
{   
    int dir_test;
    while(1)
    {
        test_bus_lines();
        getch();
        dir_test=test_direct_lines();
        if(dir_test!=0)
        {
            itoa(dir_test,salida,10);
            puts("dirrecion mala_");
            puts(salida);
            puts("\n\r");
        }
        else
        {
            puts("TODAS LAS DIRECCIONES CORRECTAS\n\r");
        }
        getch();

        test_mem_range();

        getch();
    }
}

void test_mem_range()
{
    
    int offset;
    int test_offset;

    char patter= 0xAA;

/* loading test high pattern*/
    for(offset=0x00 ; offset<=0x800; offset++)
    {
        poke(segment_num,offset,patter);
    }


/* check for addres bit stuck in high*/

    for(offset=0x00 ; offset < 0x800; offset++)
    {
        if(peek(segment_num,offset) != patter)
        {
            puts("Rango de direccion no accesible=");
            itoa((offset+((segment_num*0x10))),salida,16);
            puts(salida);
            puts("\n\r");
        }

        else{
            puts("Rango de direccion accesible=");
            itoa((offset+((segment_num*0x10))),salida,16);
            puts(salida);
            puts("\n\r");
        }
    }
}

int  test_direct_lines()
{
    int offset;
    int test_offset;

    char patter= 0xAA;
    char antipattern= 0x55;

/* loading test high pattern*/
    for(offset=1 ; offset<=0x800; offset<<=1)
    {
        poke(segment_num,offset,patter);
    }

        test_offset=0;
        poke(segment_num,test_offset,antipattern);

/* check for addres bit stuck in high*/

    for(offset=1; offset<=0x800; offset<<=1)
    {
        if(peek(segment_num,offset) != patter)
        {
            return (offset);
        }
        
    }

    poke(segment_num,test_offset,patter);

/* check for addres bit stuck in low or short circuit*/
    for(test_offset=1 ; test_offset<=0x800; test_offset<<=1)
    {
        poke(segment_num,test_offset,antipattern);

        for(offset=1 ; offset<=0x800; offset<<=1)
        {
            if((peek(segment_num,offset) !=patter ) && (offset!=test_offset))
            {
                return (test_offset);
            }
        }
        poke(segment_num,test_offset,patter);
    }
    return (0);

}

void test_bus_lines()
{
     int offset;
     for(offset=1; offset!=256; offset<<=1)
     {
         poke(segment_num,0,offset);

         if(peek(segment_num,0) != offset)
         {
            itoa(offset,salida,10);
            puts("Linea mala_");
            puts(salida);
            puts("\n\r");
         }
         
         else
         {
            itoa(offset,salida,10);
            puts("Linea ok_");
            puts(salida);
            puts("\n\r");
         }
     }

}

void itoa(unsigned int number, char* str, unsigned char base)
{
    int j,i;
    char aux_string[16];
    static char symbol[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    i=0,j=0;


    if(number!=0){
     while(number){ 
            *(aux_string+i)=symbol[number%base];
            number=number/base;
            i++;
    }
        *(aux_string+i)=0;
        

        while(i)
        {
            i--;
           (*(str+j))=aux_string[i];
           j++;

        }
        (*(str+j))=0;
    }
    else 
    {
        
        str[0]='0';
        str[1]=0;
    
    }
}

unsigned int atoi(char *str)
{
    
    int res = 0; 
    
    int i = 0; 
   
    if(*str=='0')
    {
        return 0;
    }

    if((*str)==' ')
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
        putchar(*str++);
    }
}

void gets(char* str,char secret)
{
    char temp;
    int i=0;
    while((temp=getchar())!='\r')
    {    
        if(temp==8 && i>0 )
        {
            i--;
            str--;
            putchar(temp);
            putchar(' ');
            putchar(temp);
            
            
        }
        if(temp!=8 && i<10)
        {
            if((~secret) & 0x01)
            {
                putchar(temp);
            }
            else
            {
                 putchar('*');
            }
            
          *(str++)=temp;
           i++;  /* code */
        
        }
       
    }
    *str=0;
}

