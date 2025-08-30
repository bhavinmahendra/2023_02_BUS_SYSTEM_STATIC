/*
 * Author: Bhavin Mahendra Gulab
 * Description: Program that manipulates a bus route system
 * Static Memory Allocation Version (Obviouly Less Efficent and Less Practical)
 * Portuguese Version
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


/* Valores maximos */
#define MAX_CARREIRAS 200
#define MAX_PARAGENS 10000
#define MAX_LIGACOES 30000

/*
Caracteriticas das listas
 * carreiras_list, 0 = nome, 1 = origem, 2 = destino;
 * paragens_list, 0 = nome, 1 = latidude, 2 = longitude, 3 = carreiras;
 * ligacoes_list 0 = carreira, 1 = origem, 2 = chegada, 3 = custo, 4 = duracao;
 * percursos 0 = carreira, 1 = percurso
*/

/* Variaveis globais, listas que conteem toda a informacao */
char carreiras_list[MAX_CARREIRAS][3][100];
char paragens_list[MAX_PARAGENS][4][100 * MAX_CARREIRAS];
char ligacoes_list[MAX_LIGACOES][5][100];
char paragens_only[MAX_PARAGENS][100];
char percursos[MAX_CARREIRAS][2][100 * MAX_PARAGENS];

/* Linha de leitura, alterada cada vez que se clica no Enter */
char line[500][500];

/* Verifica se uma string se encontra contida em outra*/
int check(char list[], char carreira[]) {
    int i, j = 0;
    char word[MAX_CARREIRAS * 2 * 100];
    
    for (i = 0; list[i] != '\0'; i++) {
        if (list[i] != ' ')
            word[j++] = list[i];
        else {
            word[j] = '\0';
            if (strcmp(word, carreira) == 0) return 1;
            j = 0;
        }
    }
    
    word[j] = '\0';
    if (strcmp(word, carreira) == 0)
        return 1;
    return 0;
}

/* Inicializa todas as listas a cadeias de caracteres vazias*/
void initialize(void) {
    int i, j;
    for (i = 0; i < MAX_CARREIRAS; i++)
        for(j = 0; j < 3; j++)
            strcpy(carreiras_list[i][j], "");
    for (i = 0; i < MAX_PARAGENS; i++)
        for (j = 0; j < 4; j++)
            strcpy(paragens_list[i][j], "");
    for (i = 0; i < MAX_LIGACOES; i++)
        for (j = 0; j < 5; j++)
            strcpy(ligacoes_list[i][j], "");
    for (i = 0; i < MAX_PARAGENS; i++)
        strcpy(paragens_only[i], "");
    for (i = 0; i < MAX_CARREIRAS; i++)
        for(j = 0; j < 2; j++)
            strcpy(percursos[i][j], "");
}

/* Determina o tamanho de um vetor de strings */
int size(char line[500][500]) {
    int i = 0;
    for (i = 0; strcmp(line[i], "") != 0; i++);
    return i;
}

/* Algoritmo Bubble Sort para strings */
int sort(char liststring[]) {
    char list[MAX_CARREIRAS][200], word[200] = "";
    int len = 0, i, j, k;

    for (i = 0; i < MAX_CARREIRAS; i++)
        strcpy(list[i], "");

    for (i = 0, k = 0; i < MAX_CARREIRAS; i++) {
        if (liststring[i] != ' ' && liststring[i] != '\0')
            word[k++] = liststring[i];
        else {
            word[k] = '\0';
            if (k > 0) {
                strcpy(list[len++], word);
                k = 0;
            }
            if (liststring[i] == '\0')
                break;
        }
    }

    for (i = 0; i < len - 1; i++)
        for (j = 0; j < len - i - 1; j++)
            if (strcmp(list[j], list[j+1]) > 0) {
                strcpy(word, list[j]);
                strcpy(list[j], list[j+1]);
                strcpy(list[j+1], word);
            }

    strcpy(liststring, "");
    for (i = 0; i < len; i++) {
        strcat(liststring, list[i]);
        if (i < len - 1)
            strcat(liststring, " ");
    }
    
    return len;
}

void inverso(char liststring[], char inverted[]) {
    char list[MAX_CARREIRAS][200], word[200] = "";
    int len = 0, i, k;

    for (i = 0; i < MAX_CARREIRAS; i++)
        strcpy(list[i], "");

    for (i = 0, k = 0; i < MAX_CARREIRAS; i++) {
        if (liststring[i] != ',' && liststring[i] != ' ' && liststring[i] != '\0')
            word[k++] = liststring[i];
        else {
            word[k] = '\0';
            if (k > 0) {
                strcpy(list[len++], word);
                k = 0;
            }
            if (liststring[i] == '\0')
                break;
        }
    }
    
    for (i = len - 1; i >= 0; i--) {
        strcat(inverted, list[i]);
        if (i > 0)
            strcat(inverted, ", ");
    }
}

/* cria uma lista com palavras introduzidas pelo utilizador, por linha */
void split(void) {
    int ex, ey, i, j, k, aspas, space;
    for (ex = 0; ex < 500; ex++)
        for (ey = 0; ey < 500; ey++)
            line[ex][ey] = '\0';
    i = j = aspas = space = 0;
    for (k = getchar(); k != '\n'; k = getchar()) {
        if ((k == ' ' || k == '\0' || k == '\n') && aspas % 2 == 0) {
            space++;
            if (space == 1)
                i++;
            j = 0;
        }
        else {
            space = 0;
            if (k != '"') {
                line[i][j] = k;
                j++;
            }
            if (k == '"') {
                aspas++;
            }
        }
    }
}

/* Comando c sem argumentos - imprime o nome da carreira, a origem,
o numero de paragens, o custo total e a duracao total */
void comando_c_no_args(void) {
    int i, j, k, paragens;
    for (i = 0; i < MAX_LIGACOES; i++) {
        paragens = 0;
        if (strlen(ligacoes_list[i][0]) == 0)
            break;
        for (j = 0; j < MAX_CARREIRAS; j++)
            if (strcmp(percursos[j][0], ligacoes_list[i][0]) == 0)
                break;
        for (k = 0; k < 100 * MAX_PARAGENS; k++) {
            if (percursos[j][1][k] == '\0')
                break;
            if (percursos[j][1][k] == ',')
                paragens++;
        }
        if (strcmp(percursos[j][1], "") != 0)
            paragens++;
        if (strlen(ligacoes_list[i][1]) == 0 && strlen(ligacoes_list[i][2]) != 0)
            printf("%s %s %d %.2f %.2f\n", ligacoes_list[i][0], 
                ligacoes_list[i][2], paragens, atof(ligacoes_list[i][3]), 
                atof(ligacoes_list[i][4]));
        else if (strlen(ligacoes_list[i][1]) != 0 && strlen(ligacoes_list[i][2]) == 0)
            printf("%s %s %d %.2f %.2f\n", ligacoes_list[i][0], 
                ligacoes_list[i][1], paragens, 
                atof(ligacoes_list[i][3]), atof(ligacoes_list[i][4]));
        else if (strlen(ligacoes_list[i][1]) == 0 && strlen(ligacoes_list[i][2]) == 0)
            printf("%s %d %.2f %.2f\n", ligacoes_list[i][0], paragens, 
                atof(ligacoes_list[i][3]), atof(ligacoes_list[i][4]));
        else
            printf("%s %s %s %d %.2f %.2f\n", ligacoes_list[i][0], 
                ligacoes_list[i][1], ligacoes_list[i][2], paragens, 
                atof(ligacoes_list[i][3]), atof(ligacoes_list[i][4]));
    }
}

/* Comando c com um argumento - imprime todas as paragens por ordem do percurso
de uma determinada carreira. Se a carreira nao existir, adiciona ao sistema */
void comando_c_one_args(char carreira[]) {
    int i, exists = 0;
    for (i = 0; i < MAX_CARREIRAS; i++)
        if (strlen(carreiras_list[i][0]) == 0 || strcmp(carreiras_list[i][0], carreira) == 0)
            break;
    if (strcmp(carreiras_list[i][0], carreira) == 0)
        exists = 1;
    if (exists == 0) {
        strcpy(carreiras_list[i][0], carreira);
        strcpy(ligacoes_list[i][0], carreira);
        strcpy(percursos[i][0], carreira);
    }
    if (exists == 1) {
        puts(percursos[i][1]);
    }
}

/* Comando c com um argumento - imprime todas as paragens por ordem inversa
do percurso de uma determinada carreira. Se a carreira nao existir, adiciona 
ao sistema */
void comando_c_two_args(char carreira[]) {
    int i;
    char inverted[2 * 200 * MAX_CARREIRAS] = "";

    for (i = 0; i < MAX_CARREIRAS; i++)
        if (strlen(carreiras_list[i][0]) == 0 || strcmp(carreiras_list[i][0], carreira) == 0)
            break;
    
    inverso(percursos[i][1], inverted);
    puts(inverted);
}

/* Comando p sem argumentos - imprime todas as paragens, bem como a respetiva
latitude, longitude e numero de carreiras associadas */
void comando_p_no_args(void) {
    int i, j, nr_carreiras;
    char carreira[100] = "";
    for (i = 0; strlen(paragens_list[i][0]) != 0; i++) {
        strcpy(carreira, paragens_list[i][0]);
        nr_carreiras = 0;

        for (j = 0; j < MAX_CARREIRAS; j++) {
            if (paragens_list[i][3][j] == ' ')
                nr_carreiras++;
            if (paragens_list[i][3][j] == '\0')
                break;
        }
        if (strlen(paragens_list[i][3]) > 0)
            nr_carreiras++;
        printf("%s: %16.12f %16.12f %d\n", paragens_list[i][0],
            atof(paragens_list[i][1]), atof(paragens_list[i][2]), nr_carreiras);
    }
}

/* Comando p com um argumento - imprime a latitude e longitude da paragem */
void comando_p_one_args(char paragem[]) {
    int i;
    for (i = 0; i < MAX_PARAGENS; i++)
        if (strcmp(paragens_list[i][0], paragem) == 0) {
            printf("%16.12f %16.12f\n", atof(paragens_list[i][1]), atof(paragens_list[i][2]));
            return;
        }
    printf("%s: no such stop.\n", paragem);
}

/* Comando p com tres argumento - adiciona uma nova paragem, com uma determinada
latitude e longitude */
void comando_p_three_args(char paragem[], char lat[], char lng[]) {
    int i, exists = 0;
    for (i = 0; i < 100 * MAX_PARAGENS; i++)
        if (strlen(paragens_list[i][0]) == 0 || strcmp(paragens_list[i][0], paragem) == 0)
            break;
    if (strcmp(paragens_list[i][0], paragem) == 0) {
        printf("%s: stop already exists.\n", paragem);
        exists = 1;
    }
    if (exists == 0) {
        strcpy(paragens_list[i][0], paragem);
        strcpy(paragens_list[i][1], lat);
        strcpy(paragens_list[i][2], lng);
        for (i = 0; i < MAX_PARAGENS; i++)
            if (strlen(paragens_only[i]) == 0)
                break;
        strcpy(paragens_only[i], paragem);
    }
}

/* Comando l - imprime todas as carreiras, cada uma com a sua origem, destino,
custo e duracao */
void comando_l(char carreira[], char origem[], char destino[], char custo[], char duracao[]) {
    int errors = 0;
    int i, j, k, l, m, n, o;
    float aux1, aux2;
    char aux[MAX_CARREIRAS * 2 * 100] = "";

    for (k = 0; k < MAX_PARAGENS; k++)
        if (strcmp(paragens_list[k][0], origem) == 0)
            break;
    for (l = 0; l < MAX_PARAGENS; l++)
        if (strcmp(paragens_list[l][0], destino) == 0)
            break;
    for (i = 0; i < MAX_LIGACOES; i++)
        if (strlen(ligacoes_list[i][0]) == 0 || strcmp(ligacoes_list[i][0], carreira) == 0)
            break;
    for (j = 0; j < MAX_CARREIRAS; j++)
        if (strcmp(carreiras_list[j][0], carreira) == 0)
            break;

    if (j == MAX_CARREIRAS) {
        printf("%s: no such line.\n", carreira);
        errors = 1;
    }
    
     if (j < MAX_CARREIRAS) {
        if ((strcmp(carreiras_list[j][1], origem) == 0 && strcmp(carreiras_list[j][2], destino) != 0) ||
            (strcmp(carreiras_list[j][1], origem) != 0 && strcmp(carreiras_list[j][2], destino) == 0) ||
            ((strcmp(carreiras_list[j][1], destino) != 0 && strcmp(carreiras_list[j][2], origem) != 0)
              && strlen(percursos[j][1]) > 0)) {
            puts("link cannot be associated with bus line.");
            errors = 1;
        }
    }
    if (k == MAX_PARAGENS) {
        printf("%s: no such stop.\n", origem);
        errors = 1;
    }
    if (l == MAX_PARAGENS) {
        printf("%s: no such stop.\n", destino);
        errors = 1;
    }
    if (atof(custo) < 0 || atof(duracao) < 0) {
        puts("negative cost or duration.");
        errors = 1;
    }

    if (errors == 0) {
        for (o = 0; o < MAX_CARREIRAS; o++)
            if (strcmp(percursos[o][0], carreira) == 0)
                break;

        aux1 = atof(custo);
        aux2 = atof(duracao);

        if (strcmp(ligacoes_list[i][2], origem) == 0) {
            strcpy(carreiras_list[j][2], destino);
            strcpy(ligacoes_list[i][2], destino);
            aux1 += atof(ligacoes_list[i][3]);
            aux2 += atof(ligacoes_list[i][4]);
            snprintf(ligacoes_list[i][3], sizeof(ligacoes_list[i][3]), "%.2f", aux1);
            snprintf(ligacoes_list[i][4], sizeof(ligacoes_list[i][4]), "%.2f", aux2);
            if (strlen(percursos[o][1]) != 0)
                strcat(percursos[o][1], ", ");
            strcat(percursos[o][1], destino);
        }
        else if (strcmp(ligacoes_list[i][1], destino) == 0) {
            strcpy(carreiras_list[j][1], origem);
            strcpy(ligacoes_list[i][1], origem);
            aux1 += atof(ligacoes_list[i][3]);
            aux2 += atof(ligacoes_list[i][4]);
            snprintf(ligacoes_list[i][3], sizeof(ligacoes_list[i][3]), "%.2f", aux1);
            snprintf(ligacoes_list[i][4], sizeof(ligacoes_list[i][4]), "%.2f", aux2);
            if (strlen(percursos[o][1]) != 0) {
                strcpy(aux, origem);
                strcat(aux, ", ");
                strcat(aux, percursos[o][1]);
                strcpy(percursos[o][1], aux);
            }
            else
                strcpy(percursos[o][1], origem);
        }
        else {
            strcpy(carreiras_list[j][1], origem);
            strcpy(carreiras_list[j][2], destino);
            strcpy(ligacoes_list[i][0], carreira);
            strcpy(ligacoes_list[i][1], origem);
            strcpy(ligacoes_list[i][2], destino);
            strcpy(ligacoes_list[i][3], custo);
            strcpy(ligacoes_list[i][4], duracao);
            if (strlen(percursos[o][1]) != 0) {
                strcat(percursos[o][1], ", ");
                strcat(percursos[o][1], origem);
            }
            else
                strcpy(percursos[o][1], origem);
            strcat(percursos[o][1], ", ");
            strcat(percursos[o][1], destino);
        }


        for (n = 0; n < MAX_PARAGENS; n++)
            if (strcmp(paragens_list[n][0], origem) == 0)
                break;
        if (strlen(paragens_list[n][3]) == 0)
            strcpy(paragens_list[n][3], carreira);
        else if (check(paragens_list[n][3], carreira) == 0) {
            strcat(paragens_list[n][3], " ");
            strcat(paragens_list[n][3], carreira);
        }

        for (m = 0; m < MAX_PARAGENS; m++)
            if (strcmp(paragens_list[m][0], destino) == 0)
                break;
        if (strlen(paragens_list[m][3]) == 0)
            strcpy(paragens_list[m][3], carreira);
        else if (check(paragens_list[m][3], carreira) == 0) {
            strcat(paragens_list[m][3], " ");
            strcat(paragens_list[m][3], carreira);
        }
    }
}


/* Comando i - imprime as intersecoes de carreiras, paragens com mais de uma
carreira associada */
void comando_i(void) {
    int i, len;
    
    for (i = 0; i < MAX_PARAGENS; i++) {
        len = sort(paragens_list[i][3]);
        if (len > 1)
            printf("%s %d: %s\n", paragens_list[i][0], len, paragens_list[i][3]);
    }
}

/* Responsavel por colocar o programa em pratica, o programa termina
quando o utilizador introduz o caracter q, seguido do enter */
int main(void) {
    int i = 0;
    initialize();
    split();
    while (strcmp(line[0], "q") != 0) {
        i = size(line);
        if (i == 1) {
            if (strcmp(line[0], "c") == 0) {
                comando_c_no_args();
            }
            else if (strcmp(line[0], "p") == 0) {
                comando_p_no_args();
            }
            else if (strcmp(line[0], "i") == 0) {
                comando_i();
            }
        }
        else if (i == 2) {
            if (strcmp(line[0], "c") == 0) {
                comando_c_one_args(line[1]);
            }
            else if (strcmp(line[0], "p") == 0) {
                comando_p_one_args(line[1]);
            }
        }
        else if (i == 3) {
            if (strcmp(line[0], "c") == 0) {
                if ((strcmp(line[2], "i") == 0 || strcmp(line[2], "in") == 0 || strcmp(line[2], "inv") == 0 ||
                     strcmp(line[2], "inve") == 0 || strcmp(line[2], "inverso") == 0))
                    comando_c_two_args(line[1]);
                else
                    puts("incorrect sort option.");
            }
        }
        else if (i == 4) {
            if (strcmp(line[0], "p") == 0)
                comando_p_three_args(line[1], line[2], line[3]);
        }
        else if (i == 6) {
            if (strcmp(line[0], "l") == 0)
                comando_l(line[1], line[2], line[3], line[4], line[5]);
        }
        i = 0;
        split();
    }
    return 0;
}
