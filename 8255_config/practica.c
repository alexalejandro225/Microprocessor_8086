#define BYTE unsigned char
#define WORD unsigned int
#define PA 0x40
#define PB 0x41
#define PC 0x42
#define RCtr 0x43
#define PTOs_all_out 0x80
#define PTOs_all_in 0x9B
extern void myputchar(char x);
extern char getch(); 
extern void outportb( WORD port, BYTE dato);
extern BYTE inportb( WORD port);
void SetBitPort(WORD Puerto, BYTE num_bit);
BYTE TstBitPort ( WORD Puerto, BYTE num_bit );
void myItoa(unsigned int num,int base, char *salida);
void puts(char *str);
char rotChar (char x, char n);
void led1_out();
void led2_out();
void led3_out();
void led4_out();
void led5_out();
void led6_out();
char prueba2[50];
char symbol[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
unsigned char salida[10];
int j,i;


int main()
{   
    int k;
    int temp_dato;

    outportb(RCtr,PTOs_all_in);
    
    while(1)
    {
        for(k=0;k<8;k++)
        {
            getch();
            temp_dato+=TstBitPort(PC,4);
            temp_dato=temp_dato<<1;
            puts("DATO_IN\n\r");
        }

        myItoa(temp_dato,2,salida);
        puts(salida);
        led1_out();
        getch();
        led2_out();
        getch();
        led3_out();
        getch();
        led4_out();
        getch();
        led5_out();
        getch();
        led6_out();
        getch();
    }
    return 0;
}

void led1_out()
{
    outportb(RCtr,0x89);
    outportb(PA,0);
    outportb(PB,2);
}

void led2_out()
{
    outportb(RCtr,0x89);
    outportb(PA,2);
    outportb(PB,0);
}

void led3_out()
{
    outportb(RCtr,0x98);
    outportb(PB,0);
    outportb(PC,2);
}

void led4_out()
{
    outportb(RCtr,0x98);
    outportb(PB,2);
    outportb(PC,0);
}

void led5_out()
{
    outportb(RCtr,0x8A);
    outportb(PA,2);
    outportb(PC,0);
}

void led6_out()
{
    outportb(RCtr,0x8A);
    outportb(PA,0);
    outportb(PC,2);
}

void SetBitPort(WORD Puerto, BYTE num_bit)
{
 BYTE mask=0x01; /* mascara inicial */
 BYTE temp; /* dato auxiliar */
 temp = inportb(Puerto); /* leer dato del puerto */
 mask = mask << num_bit; /* ajustar mascara según num_bit */
 temp = temp | mask; /* aplicar mascara con operador OR */
 outportb(Puerto,temp ); /* presentar resultado en el puerto */
}

BYTE TstBitPort ( WORD Puerto,BYTE num_bit )
{
 BYTE mask=0x01; 
 BYTE temp; 
 temp = inportb(Puerto); 
 mask = mask << num_bit; 
 temp = temp & mask; 
 temp = temp >> num_bit;
    if(temp)
    {
        return (1);
    }

    return(0);
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

