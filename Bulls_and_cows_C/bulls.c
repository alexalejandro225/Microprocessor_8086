#define DEC 10
#define HEX 15
#define BIN 2

typedef struct BullsAndCowsTag{
    unsigned bulls:4;
    unsigned cows:4;
}BullsAndCowsType;

extern void putchar(char data);
extern char getchar(void);
void gets(char *str,char secret);
void puts(char *str);
void itoa(unsigned int number, char* str, unsigned char base);
unsigned int atoi(char *str);
BullsAndCowsType evalBullsAndCows(char *secrete, char *guess);


char secret_number[5];
char guess_number[5];
char bulls[2];
char cows[2];
unsigned char intentos=0;

char symbol[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

int main(void)
{   
    BullsAndCowsType bulls_and_cows={0,0};
    while(1)
    {
    puts("captura la clave secreta=");
    gets(secret_number,1);
    while(intentos<8 && bulls_and_cows.bulls<4)
    {
    puts("\n\r");
    puts("captura la clave del jugador=");
    gets(guess_number,0);
    bulls_and_cows=evalBullsAndCows(secret_number,guess_number);
        if(bulls_and_cows.bulls==4)
        {
            puts("\n\n\r");
            puts("GANASTE");
            puts("\n\n\r");

        }
        else if (bulls_and_cows.bulls<4)
        {
            intentos++;
            puts("\n\n\r");
            itoa(bulls_and_cows.bulls,bulls,DEC);
            puts("Toros=");
            puts(bulls);
            puts("\n\n\r");
            itoa(bulls_and_cows.cows,cows,DEC);
            puts("Vacas=");
            puts(cows);
            puts("\n\n\r");
            if(intentos==8)
            {
                puts("\n\n\r");
                puts("PERDISTE");
                puts("\n\n\r");
            }
        }
    }
    intentos=0; 
    bulls_and_cows.bulls=0;
    bulls_and_cows.cows=0; 
    getchar();
    }
    return 0;
}

void itoa(unsigned int number, char* str, unsigned char base)
{
    int j,i;
    char aux_string[16];
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

BullsAndCowsType evalBullsAndCows(char *secrete, char *guess)
{
    BullsAndCowsType bull_cows={0,0};

    char i,j;

    for(i = 0; i < 4; i++)
    {
        if(secrete[i] == guess[i])
        {
            bull_cows.bulls++;
        }
        else
        {
            for (j = 0; j < 4; j++)
            {
                if(secrete[i] == guess[j])
                {
                    bull_cows.cows++;
                }
            }
            j=0;
        }
        
    }
    return bull_cows;
}