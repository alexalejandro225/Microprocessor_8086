#define segment_num 0x0d00
extern unsigned char peek(unsigned int segment,unsigned int offset);
extern void poke(unsigned int segment,unsigned int offset, unsigned char data) ;
extern void myputchar(char x);
void test_mem_range();
extern char getch(); 
void myItoa(unsigned int num,int base, char *salida);
void puts(char *str);
char rotChar (char x, char n);
void test_ceros();
void test_ones();
void test_bus_lines();
int  test_direct_lines();
char prueba2[50];
char symbol[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
unsigned char contador_entrada=0;
unsigned char salida[10];
int j,i;


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
            myItoa(dir_test,10,salida);
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
    char antipattern= 0x55;

/* loading test high pattern*/
    for(offset=0x1 ; offset<=0x800; offset++)
    {
        poke(segment_num,offset,patter);
    }


/* check for addres bit stuck in high*/

    for(offset=0x1 ; offset<=0x800; offset++)
    {
        if(peek(segment_num,offset) != patter)
        {
            puts("Rango de direccion no accesible=");
            myItoa((offset+((segment_num*0x10))),16,salida);
            puts(salida);
            puts("\n\r");
        }
        else{
            puts("Rango de direccion accesible=");
            myItoa((offset+((segment_num*0x10))),16,salida);
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
            myItoa(offset,10,salida);
            puts("Linea mala_");
            puts(salida);
            puts("\n\r");
         }
         
         else
         {
            myItoa(offset,10,salida);
            puts("Linea ok_");
            puts(salida);
            puts("\n\r");
         }
     }

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

void puts(char* str)
{
    while(*str)
    {
        myputchar(*str++);
    }
}

char rotChar (char x, char n)
{
  return (x<<n) | (x>>(8-n));
}

