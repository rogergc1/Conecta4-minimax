#include <stdio.h>
#include <stdbool.h>

const short VICTORIA=1;
const short DERROTA=-1;
const short TAULES=0;

const int COLUMNES=4;
const int FILES=4;

//static char diccionari[9223372036854775807];

void mostrarMatriu(char matriu[FILES][COLUMNES]);
void inicialitzarMatriu(char matriu[FILES][COLUMNES]);
short funcioRecursiva(char matriu[FILES][COLUMNES], int profunditat);
bool buscaVictoria(char matriu[FILES][COLUMNES], int x, int y);
void copiarMatriu(char matriuAntiga[FILES][COLUMNES], char matriuNova[FILES][COLUMNES]);
void giraMatriu(char matriu[FILES][COLUMNES]);
//long funcioClau(char matriu[FILES][COLUMNES]);
//void inicialitzarDiccionari();

int main()
{
    //inicialitzarDiccionari();
    char matriu[FILES][COLUMNES];
    inicialitzarMatriu(matriu);
    printf("%d",funcioRecursiva(matriu,0));
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

short funcioRecursiva(char matriu[FILES][COLUMNES], int profunditat)
{
    mostrarMatriu(matriu);
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
                    char novaMatriu[FILES][COLUMNES];
                    copiarMatriu(matriu, novaMatriu);
                    novaMatriu[j][i]='X';
                    giraMatriu(novaMatriu);
                    int resultatActual=-funcioRecursiva(novaMatriu, profunditat+1);
                    if(resultatActual>resultat)
                    {
                        if(resultatActual==1) return 1;
                        resultat=resultatActual;
                    }
                }
            }
            j++;
        }
    }

    if(ple)
    {
        return TAULES;
    }
    else
    {
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
    for(int i = 1; i<4;i++)
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
    for(int i = -1; i>-4;i--)
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
    if(vertical>2 || horitzontal>2 || dDecreixent>2 || dCreixent>2)
    {
        return true;
    }
    return false;
}

void copiarMatriu(char matriuAntiga[FILES][COLUMNES], char matriuNova[FILES][COLUMNES])
{
    for(int i =0; i<FILES;i++)
    {
        for(int j=0;j<COLUMNES;j++)
        {
            matriuNova[i][j]=matriuAntiga[i][j];
        }
    }
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

/*long funcioClau(char matriu[FILES][COLUMNES])
{
    unsigned long resultat=0;
    for(int i=0; i<COLUMNES;i++)
    {
        bool primerValor=true;
        for(int j=FILES-1;j>=0;j--)
        {
            if(matriu[j][i]!='_') 
            {
                if(primerValor)
                {
                    resultat<<3;
                    resultat+=j;
                }
                resultat<<1;
                if(matriu[j][i]=='X') resultat++; 
            }
        }
    }
    return resultat;
}
*/

/*void inicialitzarDiccionari()
{
    for(unsigned long i=0;i<9223372036854775807;i++)
    {
        diccionari[i]='0';
    }
}
*/