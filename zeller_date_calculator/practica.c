extern void myputchar(char x);
extern char getch();
/*--------------------------------------------------------------------------------------------*/
int myAtoi(char* str);
void myItoa(unsigned int num,int base, char *salida);
void puts(char *str);
void gets(char *str);
int get_fecha(char *str,int index_a,int index_b);
void zeller_congruense();
int bisiesto(int year);
void delay();
/*--------------------------------------------------------------------------------------------*/
char symbol[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
int decimal[] = {65000,60000,50000,10000,5000,1000,900,500,400,100,90,50,40,10,9,5,4,1};
char *days_zeller[]={"sabado","domingo","lunes","martes","miercoles","jueves","viernes"};
int month_days[]={31,29,31,30,31,30,31,31,30,31,30,31};
char *months[]={"enero","febrero","marzo","abril","mayo","junio","julio","agosto","septiembre","octubre","noviembre","diciembre"};
/*-----------------------------------------------------------------------------------------------*/
char fecha[12];
char aux[10];
char aux2[6];
char aux3[11]={" del a/o "};


int main(void)
{  
    while(1)
    {
   zeller_congruense();
    }
    return 0;
}

void zeller_congruense()
{

int day,month,k,j,q,year,m,h;
    gets(fecha);
    day=get_fecha(fecha,0,1);
    month=get_fecha(fecha,3,4);
    q=day;
    m=month;
    year=get_fecha(fecha,6,9);

    if(day>month_days[month-1])

    {
        puts("FECHA NO VALIDA");
        return ;
    }

    if(day==29 && month==2 && bisiesto(year)!=1)
    {
        puts("Fecha no valida");
        return ;
    }

    if(m==1)
    {
        m=13;
        year--;
    }

    if(m==2)
    {
        m=14;
        year--;
    }
    aux[0]=' ';
    aux[1]=fecha[0];
    aux[2]=fecha[1];
    aux[3]=' ';
    aux[4]='d';
    aux[5]='e';
    aux[6]=' ';
    aux[7]=0;
    /*===================================*/
    aux2[0]=fecha[6];
    aux2[1]=fecha[7];
    aux2[2]=fecha[8];
    aux2[3]=fecha[9];
    aux2[4]=0;
/*=======================================*/
    k=year%100;
    j=year/100;
    h=(q+((m+1)*26/10)+k+(k/4)+(j/4)-(2*j));
    h=h%7;
    myputchar(10);
    myputchar(13);
    puts(days_zeller[h]);
    puts(aux);
    puts(months[month-1]);
    puts(aux3);
    puts(aux2);
    myputchar(10);
    myputchar(13);
}


void delay()
{
    int i;
    for(i=0; i==100; i++)
    {
        i++;
    }
}
int get_fecha(char *str,int index_a,int index_b)
{   int i=0;
    int res=0;
    
    for (i=index_a; i<=index_b ; ++i)
	{
        res = res * 10 + str[i] - '0';
	}
    return  res;
}

int bisiesto(int year)

{
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);

}

void myItoa(unsigned int num,int base, char *salida)
{
    int j,i;
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

int myAtoi(char* str)
{
    
    int res = 0; 
    
    int i = 0; 
   
    if(*str=="0")
    {
        return 0;
    }

    if((*str)==" ")
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
        myputchar(*str++);
    }
}

void gets(char* str)
{
    char temp;
    int i=0;
    while((temp=getch())!='\r')
    {    
        if(temp==8 && i>0 )
        {
            i--;
            str--;
            myputchar(temp);
            myputchar(' ');
            myputchar(temp);
            
            
        }
        if(temp!=8 && i<10)
        {
            myputchar(temp);
          *(str++)=temp;
           i++;  /* code */
        
        }
       
    }
    *str=0;
}

