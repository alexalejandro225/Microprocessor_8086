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


int main(void)
{  
    int offset;
    int dir_data;
    int linea=0;
    int aux_offset;
    int k;
    int test;
    
    for(k=0x3800; k<0x3C00; k++)
    {
        poke(k,170);
        
    }

     for(k=0x3800; k<0x3C00; k=k+2)
    {
        poke(k,85);
        
    }

    for(k=0x3800; k<0x3C00; k++)
    {
        test=peek(k);
        if(test==170 || test==85)
        {
            myItoa(test,10,prueba2);
            puts(prueba2);
            myputchar('\n');
            myputchar(13);
            
        }
        else{
            puts("linea de datos mala");
            contador++;
            if(contador>0x800)
            {
                puts("falla critica de lineas de datos");
            }
        }
    }
    getch();

    
    
    offset=1;
    contador_entrada=0;
    while(offset!=2048)
    {
        poke(0x3800+offset,contador_entrada);
        offset=offset<<1;      
        contador_entrada=contador_entrada+1;
    }
    getch();
    
    offset = 1;
    contador_entrada=0;

    while(offset!=2048)
    {
       
        dir_data = peek(0x3800+offset);
        
        if(dir_data != contador_entrada)
        {   
            aux_offset = offset;
            while(aux_offset!=0)
            {
                linea++;
                aux_offset=aux_offset>>1;
            }
            puts("falla en direcciones\n");
            myputchar(linea+'0');
            myputchar(10);
            myputchar(13);
            myputchar(offset);
            myputchar(10);
            myputchar(13);
            myputchar(dir_data);
        }
        else
        { 
            puts("todo funciona\n");
            myputchar(10);
            myputchar(13);
        }
        
      offset = offset << 1; 
      contador_entrada=contador_entrada+1; 
    }
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

