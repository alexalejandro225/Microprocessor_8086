extern unsigned char peek(unsigned int offset);
extern void poke(unsigned int offset, unsigned char data) ;
extern void myputchar(char x);
extern char getch(); 
void myItoa(unsigned int num,int base, char *salida);
void puts(char *str);
char rotChar (char x, char n);
void test_ceros();
void test_ones();
char prueba2[50];
char symbol[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
int i,j,t,contador=0;
unsigned char contador_entrada=0;
unsigned char salida[5];


int main()
{
    int i;
    
    while(1)
    {
        puts("Presiona enter para cargar ceros\n\r");
        getch();
        for(i=0; i<0x1000; i++)
        {
            poke(i,1);
        }

        puts("Presiona enter para probar ceros\n\r");
        getch();
        
        

        
    }
}

void test_ones()
{
    unsigned int i=0;
    unsigned char data_out;

        i=0;
        
        while(i<0x1000)
        {
            poke(i,1);
            i++;
        }

        i=0;

         while(i<0x1000) 
        {
            data_out=peek(i);
            myItoa(data_out,16,salida);

            if(data_out==1)
            {
                puts("CELDA DE MEMORIA CORRECTA NUM_");
                puts(salida);
                puts("\n\r");
            }

            else
            {
                puts("CELDA DE MEMORIA FALLIDA NUM_");
                puts(salida);
                puts("\n\r");
            }
            i++;
        }
}

void test_ceros()
{
    unsigned int i=0;
    unsigned char data_out;

    puts("PRESIONA ENTER PRUEBA EN CEROS\n\r");
        getch();

        i=0;
        
        while(i<0x1000)
        {
            poke(i,0);
            i++;
        }

        i=0;

         while(i<0x1000) 
        {
            data_out=peek(i);
            myItoa(data_out,16,salida);

            if(data_out==0)
            {
                puts("CELDA DE MEMORIA CORRECTA NUM_");
                puts(salida);
                puts("\n\r");
            }

            else
            {
                puts("CELDA DE MEMORIA FALLIDA NUM_");
                puts(salida);
                puts("\n\r");
            }
            i++;
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

