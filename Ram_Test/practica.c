extern unsigned char peek(unsigned int offset);
extern void poke(unsigned int offset, unsigned char data) ;
extern void myputchar(char x);
extern char getch(); 
void myItoa(unsigned int num,int base, char *salida);
void puts(char *str);
char rotChar (char x, char n);
void test_ceros();
void test_ones();
int test_bus_lines();
int  test_direct_lines();
char prueba2[50];
char symbol[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
unsigned char contador_entrada=0;
unsigned char salida[10];
int j,i;


int main()
{   
    char bus_test;
    int dir_test;
    while(1)
    {
        bus_test=test_bus_lines();
        if(bus_test!=0)
        {
            myItoa(dir_test,10,salida);
            puts("data mala_\n\r");
            puts(salida);
            puts("\n\r");
        }
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
        poke(offset,patter);
    }

        test_offset=0;
        poke(test_offset,antipattern);

/* check for addres bit stuck in high*/

    for(offset=1; offset<=0x800; offset<<=1)
    {
        if(peek(offset) != patter)
        {
            return (offset);
        }
        
    }

    poke(test_offset,patter);

/* check for addres bit stuck in low or short circuit*/
    for(test_offset=1 ; test_offset<=0x800; test_offset<<=1)
    {
        poke(test_offset,antipattern);

        for(offset=1 ; offset<=0x800; offset<<=1)
        {
            if((peek(offset) !=patter ) && (offset!=test_offset))
            {
                return (test_offset);
            }
        }
        poke(test_offset,patter);
    }
    return (0);

}


int test_bus_lines()
{
     int offset;
     for(offset=1; offset!=256; offset<<=1)
     {
         poke(0,offset);

         if(peek(0) != offset)
         {
             return (offset);
         }
         
         myItoa(offset,10,salida);
         puts("Linea ok_");
         puts(salida);
         puts("\n\r");
     }

     return (0);

}

void test_ones()
{
     int i=0;
     char data_out;

        for(i=0; i<=0x800; i++)
        {
            poke(i,1);
        }
        
            for(i=0; i<=0x800; i++)       
            {
            data_out=peek(i);
            myItoa(i,16,salida);

            if(data_out==1)
            {
                puts(salida);
                puts("\n\r");
            }
            else
            {
                puts("CELDA DE MEMORIA FALLIDA NUM_");
                puts(salida);
                puts("\n\r");
            }
        }
}

void test_ceros()
{
     int i=0;
     char data_out;

        for(i=0; i<=0x800; i++)
        {
            poke(i,0);
        }

        for(i=0; i<=0x800; i++)
        {
            data_out=peek(i);
            myItoa(i,16,salida);

            if(data_out==0)
            {
                puts(salida);
                puts("\n\r");
            }

            else
            {
                puts("CELDA DE MEMORIA FALLIDA NUM_");
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

