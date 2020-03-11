extern unsigned char peek(unsigned int offset);
extern void poke(unsigned int offset, unsigned char data) ;
extern void myputchar(char x);
extern char getch(); 
void myItoa(unsigned int num,int base, char *salida);
void puts(char *str);
char rotChar (char x, char n);
void test_ceros();
void test_ones();
void test_bus_lines();
char prueba2[50];
char symbol[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
unsigned char contador_entrada=0;
unsigned char salida[5];
int j,i;


int main()
{
    char i=1;
    
    while(1)
    {
        puts("PRESIONA ENTER PRUEBA EN CEROS\n\r");
        getch();
        test_ceros();
        puts("PRESIONA ENTER PRUEBA EN UNOS\n\r");
        getch();
        test_ones();
        puts("PRESIONA ENTER PRUEBA EN LINEAS DE DATOS\n\r");
        getch();
        test_bus_lines();
    }
}

void test_bus_lines()
{
     char offset=1;
     int i;
     char data_out=0;

        for(i=0; i<8; i++)
        {
            poke(offset,offset);
            offset=offset<<1;
        }

        offset=1;

        for(i=0; i<8; i++)  

            {
            myItoa(i,10,salida);
            data_out=peek(offset);
            if(data_out==offset)
            {
                puts("LINEA DE DATOS CORRECTA NUM_");
                puts(salida);
                puts("\n\r");
            }
            else
            {
                puts("LINEA DE DATOS FALLIDA NUM_");
                puts(salida);
                puts("\n\r");
            }
            offset=offset<<1;
        }

        offset=1;
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

