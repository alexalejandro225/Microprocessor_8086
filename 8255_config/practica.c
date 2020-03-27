#define BYTE unsigned char
#define WORD unsigned int
#define PA 0x40
#define PB 0x41
#define PC 0x42
#define RCtr 0x43
#define PTOs_all_out 0x80
#define PTOs_all_in 0x9B
#define click_delay 10
extern void myputchar(char x);
extern char getch(); 
extern void outportb( WORD port, BYTE dato);
extern BYTE inportb( WORD port);

void SetBitPort(WORD Puerto, BYTE num_bit);
BYTE TstBitPort ( WORD Puerto, BYTE num_bit );
void ClrBitPort(WORD Puerto,BYTE num_bit);
void NotBitPort(WORD Puerto,BYTE num_bit);
void ReversBitsPort(WORD Puerto);
void myItoa(unsigned int num,int base, char *salida);
void puts(char *str);
unsigned char reverseBits(unsigned char n);
unsigned char rotChar (unsigned char x,unsigned char n);
void delay(BYTE counter_cycles);
void led1_out();
void led2_out();
void led3_out();
void led4_out();
void led5_out();
void led6_out();
char prueba2[50];
char symbol[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
unsigned char salida[10];
BYTE port_bit_in[8]={0};
int j,i;


int main()
{   
    WORD k;
    BYTE temp_dato,data;


    outportb(RCtr,PTOs_all_in);
    
    while(1)
    {
        data=0xAF;
        temp_dato=0;
        k=0;
        puts("captura los bits de entrada\n\r");
        for(k=0;k<8;k++)
        {
            getch();
            temp_dato=temp_dato<<1;
            temp_dato+=TstBitPort(PC,4);
            puts("DATO_IN\n\r");
        }

        myItoa(temp_dato,2,salida);
        puts(salida);
        puts("\n\r");

        temp_dato=reverseBits(temp_dato);

        temp_dato=temp_dato>>2;

        myItoa(temp_dato,2,salida);
        puts(salida);


        /*=======================================*/

        for(k=0;k<8;k++)
        {
            port_bit_in[k]=temp_dato & 0x01;
            temp_dato=temp_dato >> 1;
        }




        while(1)
        {
            if(port_bit_in[0]==1)
            {
                led1_out();
                delay(click_delay);
            }

            if(port_bit_in[1]==1)
            {
                led2_out();
                delay(click_delay);
            }

            if(port_bit_in[2]==1)
            {
                led3_out();
                delay(click_delay);
            }

            if(port_bit_in[3]==1)
            {
                led4_out();
                delay(click_delay);
            }

            if(port_bit_in[4]==1)
            {
                led5_out();
                delay(click_delay);
            }

            if(port_bit_in[5]==1)
            {
                led6_out();
                delay(click_delay);
            }


        }

    }
    return 0;
}

void delay(BYTE counter_cycles)
{
    BYTE steps=0;
    for(steps; steps<counter_cycles; steps++)
    {
        asm nop;
    }
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

void ClrBitPort(WORD Puerto,BYTE num_bit)
{
 BYTE mask=0xFE; 
 BYTE temp;
 temp = inportb(Puerto); 
 mask = rotChar(mask,num_bit);
 temp = temp & mask;
 outportb(Puerto,temp);
}

void NotBitPort(WORD Puerto,BYTE num_bit)
{
 BYTE mask=0x1; 
 BYTE temp;
 temp = inportb(Puerto); 
 mask = mask << num_bit;
 temp = temp ^ mask;
 outportb(Puerto,temp);
}

void ReversBitsPort(WORD Puerto)
{
 BYTE temp;
 temp = inportb(Puerto); 
 temp = reverseBits(temp);
 outportb(Puerto,temp);
}

unsigned char reverseBits(unsigned char n) 
{ 
    unsigned int rev = 0; 
    
    while (n > 0) 
    { 
       
        rev <<= 1; 
          
        
        if (n & 1 == 1) 
        {
            rev ^= 1; 
        } 

        n >>= 1; 
              
    } 
    return rev; 
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

unsigned char rotChar (unsigned char x,unsigned char n)
{
  return (unsigned)(x<<n) | (x>>(8-n));
}

