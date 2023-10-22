#include <stdio.h>
#include <stdbool.h>

#define VICTORIA 1
#define DERROTA -1
#define TAULES 0

#define COLUMNES 7
#define FILES 6

#define ENRALLA 4

char jaCercats[562949953421312]={0};

void mostrarMatriu(char matriu[FILES][COLUMNES]);
void inicialitzarMatriu(char matriu[FILES][COLUMNES]);
short minimax(char matriu[FILES][COLUMNES], int profunditat);
bool buscaVictoria(char matriu[FILES][COLUMNES], int x, int y);
void giraMatriu(char matriu[FILES][COLUMNES]);
unsigned long long funcioClau(char matriu[FILES][COLUMNES]);

int main()
{
    char matriu[FILES][COLUMNES];
    inicialitzarMatriu(matriu);
    mostrarMatriu(matriu);
    for(unsigned long long i =0;i<100;i++)
    {
        printf("%d: %d\n",i,jaCercats[i]);
    }
    //printf("%d",minimax(matriu,0));
}

void inicialitzarMatriu(char matriu[FILES][COLUMNES])
{
    //X jugador.
    //O contrincant
    //_ casella buida

    for(int i=0;i<FILES;i++)
    {
        for(int j=0;j<COLUMNES;j++)
        {
            matriu[i][j]='_';
        }
    }
}

void mostrarMatriu(char matriu[FILES][COLUMNES])
{
    for(int i=FILES-1;i>=0;i--)
    {
        for(int j=0;j<COLUMNES;j++)
        {
            printf("%c ",matriu[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
    printf("\n");
}

short minimax(char matriu[FILES][COLUMNES], int profunditat)
{
    //printf("%d\n",profunditat);
    //mostrarMatriu(matriu);
    
    unsigned long long codi=funcioClau(matriu);
    if(jaCercats[codi]!=0) {printf("Profunditat %d",profunditat);return (short)jaCercats[codi];}
    bool ple=true;
    int resultat=DERROTA;
    for(int i=0;i<COLUMNES;i++)
    {
        int j=0;
        bool trobat=false;
        while(j<FILES && !trobat)
        {
            if(matriu[j][i]=='_')
            {
                trobat=true;
                ple=false;
                if(buscaVictoria(matriu,j,i))
                {
                    return VICTORIA;
                }
                else
                {
                    matriu[j][i]='X';
                    giraMatriu(matriu);
                    int resultatActual=-minimax(matriu, profunditat+1);
                    matriu[j][i]='_';
                    giraMatriu(matriu);
                    if(resultatActual>resultat)
                    {
                        if (resultatActual == VICTORIA) 
                        {
                            jaCercats[codi]=(char)VICTORIA;
                            return VICTORIA;
                        }
                        resultat=resultatActual;
                    }
                }
            }
            j++;
        }
    }

    if(ple)
    {
        jaCercats[codi]=(char)TAULES;
        return TAULES;
    }
    else
    {
        jaCercats[codi]=(char)resultat;
        return resultat;
    }
}

bool buscaVictoria(char matriu[FILES][COLUMNES], int y, int x)
{
    int vertical=0;
    int horitzontal=0;
    int dCreixent=0;
    int dDecreixent=0;
    bool ver=true;
    bool hor=true;
    bool dCre=true;
    bool dDec=true;
    for(int i = 1; i<ENRALLA;i++)
    {
        if(i+x<COLUMNES)
        {
            if(i+y<FILES && dCre)
            {
                if(matriu[y+i][x+i]=='X')
                {
                    dCreixent++;
                }
                else
                {
                    dCre=false;
                }
            }
            if(i-y>=0 && dDec)
            {
                if(matriu[y-i][x+i]=='X')
                {
                    dDecreixent++;
                }
                else
                {
                    dDec=false;
                }
            }
            if(hor)
            {
                if(matriu[y][x+1]=='X')
                {
                   horitzontal++;
                }
                else
                {
                    hor=false;
                }
            }
        }
    }
    hor=true;
    dCre=true;
    dDec=true;
    for(int i = -1; i>-ENRALLA;i--)
    {
        if(i+x>=0)
        {
            if(i+y>=0 && dCre)
            {
                if(matriu[y+i][x+i]=='X')
                {
                    dCreixent++;
                }
                else
                {
                    dCre=false;
                }
            }
            if(y-i<FILES && dDec)
            {
                if(matriu[y-i][x+i]=='X')
                {
                    dDecreixent++;
                }
                else
                {
                    dDec=false;
                }
            }
            if(hor)
            {
                if(matriu[y][x+i]=='X')
                {
                   horitzontal++;
                }
                else
                {
                    hor=false;
                }
            }
        }
        if(i+y>=0)
        {
            if(ver)
            {
                if(matriu[y+i][x]=='X')
                {
                   vertical++;
                }
                else
                {
                    ver=false;
                }
            }
        }
    } 
    if(vertical>ENRALLA-2 || horitzontal>ENRALLA-2 || dDecreixent>ENRALLA-2 || dCreixent>ENRALLA-2)
    {
        return true;
    }
    return false;
}

void giraMatriu(char matriu[FILES][COLUMNES])
{
    for(int i =0; i<FILES;i++)
    {
        for(int j=0;j<COLUMNES;j++)
        {
            if(matriu[i][j]=='X')
            {
                matriu[i][j]='O';
            }
            else if (matriu[i][j]=='O')
            {
                matriu[i][j]='X';
            }
        }
    }
}

unsigned long long funcioClau(char matriu[FILES][COLUMNES])
{
    /*
    42 primers bits indicant si hi ha una peça blanca. Les caselles superiors sempre seran marcades independentment del color.
    7 bits indicant el color d'aquestes peces.
    */    
    unsigned long long resultat=0;
    unsigned long long  primers=0;
    for(int i=0; i<COLUMNES;i++)
    {
        primers<<=1;
        bool primeraOcupada=false;
        for(int j=FILES-1;j>=0;j--)
        {
            resultat<<=1;
            if(!(matriu[j][i]=='_') && !primeraOcupada)
            {
                primeraOcupada=true;
                resultat++;
                if(matriu[j][i]=='X') primers++;
            }
            else if(matriu[j][i]=='X') resultat++;
        }
    }
    resultat<<=COLUMNES;
    resultat+=primers;
    return resultat;
}
