#define ram_offset 0x2200
extern unsigned char peek(unsigned int offset);
extern void poke(unsigned int offset, unsigned char data) ;
extern void myputchar(char x);
extern char getch(); 
void myItoa(unsigned int num,int base, char *salida);
void puts(char *str);
char rotChar (char x, char n);
char prueba2[50];
char symbol[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
int i,j,t,contador=0;
char contador_entrada=0;
char salida[3];


int main(void)
{ int i,offset=1,test; 
    while(1)
    {
        for(i=ram_offset; i<=0x4200; i++)
        {
            poke(i,0x55);

        }

        for(i=0; i<13; i++)
        {
            poke(ram_offset+offset,0xAA);
            offset=offset<<1;
        }
        offset=1;
        puts("PRESIONA ENTER PARA PROBAR LINEAS DE DATOS\n\r");

        getch();

        for(i=0; i<8; i++)
        {
            myItoa(i,10,salida);
            if(peek(ram_offset+offset)==0xAA)
            {
                puts("Linea de datos correcta_");
                puts(salida);
                puts("\n\r");
            }
            else 
            {
                puts("Linea de datos incorrecta\n\r");
                puts("FALLA CRITICA LINEA DE DATOS/DIRECCIONES\n\r");
            }
            offset=offset<<1;
        }
        /*=============================================*/
        puts("PRESIONA ENTER PARA PROBAR LINEAS DE DIRECCIONES\n\r");
        getch();
        /*=============================================*/
        for(i=8; i<13; i++)
        {
            test=peek(ram_offset+offset);
            myItoa(i,10,salida);
            getch();
            if(test==0xAA)
            {
                puts("Linea de direccion correcta_");
                puts(salida);
                puts("\n\r");
            }
            else 
            {
                puts("Linea de direccion incorrecta\n\r");
            }
            offset=offset<<1;
        }
        offset=1;


    }
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

