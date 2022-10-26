#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h> //Needed for strcat()
#include <ctype.h>
#include "utilities.h"
#include "funcoes.h"

char NamePrefix[][5] = {
    "",     //who said we need to add a prefix?
    "bel",  //lets say that means "the good"
    "nar",  //"The not so good as Bel"
    "xan",  //"The evil"
    "bell", //"the good"
    "natr", //"the neutral/natral"
    "ev",   //Man am I original
};

char NameSuffix[][5] = {
    "", "us", "ix", "ox", "ith",
    "ath", "um", "ator", "or", "axia",
    "imus", "ais", "itur", "orex", "o",
    "y"};

const char NameStems[][10] = {
    "adur", "aes", "anim", "apoll", "imac",
    "educ", "equis", "extr", "guius", "hann",
    "equi", "amora", "hum", "iace", "ille",
    "inept", "iuv", "obe", "ocul", "orbis"};

char* NameGen()
{
    char *PlayerName = malloc(sizeof(char) * 21);
    PlayerName[0] = 0; //initialize the string to "" (zero length string).
    //add the prefix...
    strcat(PlayerName, NamePrefix[(rand() % 7)]);
    //add the stem...
    strcat(PlayerName, NameStems[(rand() % 20)]);
    //add the suffix...
    strcat(PlayerName, NameSuffix[(rand() % 16)]);
    //Make the first letter capital...
    PlayerName[0] = toupper(PlayerName[0]);
    return PlayerName;
}

char *randstring(size_t length)
{

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; //Caracteres usado na string gerada
    char *randomString = NULL;

    if (length)
    {
        randomString = malloc(sizeof(char) * (length + 1));

        if (randomString)
        {
            for (int n = 0; n < length; n++)
            {
                int key = rand() % (int)(sizeof(charset) - 1);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}

int compara_nome(const void *a, const void *b)
{
    return strcmp(((cliente *)a)->nome, ((cliente *)b)->nome);
}

int compara_cpf(const void *a, const void *b)
{
    return strcmp(((cliente *)a)->cpf, ((cliente *)b)->cpf);
}
