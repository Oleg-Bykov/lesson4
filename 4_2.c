#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 255
#define STACK_SIZE 255

char oper[STACK_SIZE] = {0};
int oend=0;

void printStack(void)                   // фунция печати
{
    for (int i=0; i<oend;i++)
    {
        printf("Stack: %c ", oper[i]);
    }
    printf("\n");
}

void push(char v)                       // 
{
    oper[oend++] = v;
}

char pop()                              // проверяем на перезаполняемость
{
    if((oend<=0) || oend>=BUFFER_SIZE)
    {
        fprintf(stderr,"Stack overflow\n");
        exit(1);
    }
    oend--;
    return oper[oend];
}

_Bool emptyStack()                      // обозначаем пустой стек
{
    return oend==0;
}

_Bool isOperator(char c)                // обозначаем действия
{
    return c=='&' || c=='|' || c=='^'; 
}

int priority(char c)                    // выставляем приоритетность
{
    if (c=='|')
        return 1;
    if (c=='^')
        return 2;
    if (c=='&')
        return 3;
    return 0;
}

int main(void)                          // главная функция
{
    char c;
    int pos=0;
    char answer[BUFFER_SIZE]={0};       
    for(int i=0;i<BUFFER_SIZE;i++)      //записываем 0 память чтоб не получить мусор
        answer[i]=0;
    printf("Input infix string  ");
    char str[1000];
    int len=0;
    while((c=getchar()) != '\n')        // запускаем цикл ввода до перехода на повую строку
        str[len++]=c;                   // вводим значения
    str[len]=0;                         // последнее значение присваивем 0 
    for (int i=0;i<len;i++)             // запускаем цикл на уже известную длинну
    {
        if (str[i]>='0' && str[i]<='9')     // проверяем на наличие цифр
        {
            int number,size=0;
            for(number=0; str[i]>='0' && str[i]<='9';i++,size++)
            {
                number=number*10 + str[i]-'0';      // как на семинаре с переменной val
            }                                       // если цифра продолжается, мы увеличиваем десяток: 123, мы записываем 1,видим 2,1*10  и добавляем 2, потом 12*10  и добавляем 3 до тех пор пока 0<=str[i]<=9
            sprintf(answer+pos, "%d ",number);
            pos += size+1;                          // переходим к следующему за числом символу
        }
        else                        // если у нас встречается не число
        {
            if(i>=len)              // проверяем ушли ли за пределы строки
                break;
            c = str[i];
            if(isOperator(c))       // проверяем приоритетность сравнивая введенный символ со значение расставленыъ приоритетов в фунции priority (1,2,3 или 0)
            {
                while( !emptyStack())   //пока стек не будет пустым проверяем
                {
                    char top =pop();
                    if(priority(top)>= priority(c))
                    {
                        sprintf(answer+pos, "%c ",top);
                        pos +=2;
                    }
                    else
                    {
                        push(top);
                        break;
                    }
                }
                push(c);
            }
            else if(c=='(')
            {
                push(c);
            }
            else if (c==')')
            {
                while ( (c=pop()) != '(')
                {
                    sprintf(answer+pos,"%c ",c);
                    pos += 2;
                }
            }
        }
    }
    while ( !emptyStack())
    {
        sprintf(answer+pos, "%c ", pop() );
        pos += 2;
    }    
    printf("Answer %s\n", answer);
    return 0;
}

