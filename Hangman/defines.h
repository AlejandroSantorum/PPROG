#ifndef DEFINES_H
#define DEFINES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <pthread.h>
#include <termios.h>

/*Game Mode*/
#define EASY 1000
#define MEDIUM 1001
#define HARD 1002
#define LEGENDARY 1003
#define BATTLE_MODE 1004

/*Languages*/
#define ENGLISH 1010
#define SPANISH 1011
#define GALICIAN 1012

/*Object types*/
#define MEDICINE 1020
#define FOOD 1021
#define DRINK 1022
#define AMMO 1023

/*Enemies stuff*/
#define ZOMBIE 1030
#define WALL 1031
#define ALIVE 1032
#define DEAD 1033
#define ALL_KILLED 1034
#define STH_ALIVE 1035
#define NOWHERE -1030


/*Weapon owned & equipped & dir_change*/
#define OWNED 1040
#define NOT_OWNED 1041
#define EQUIPPED 1042
#define NOT_EQUIPPED 1043
#define UPW 1044
#define DOWNW 1045


/*Orientation of character*/
#define UP 1050
#define DOWN 1051
#define RIGHT 1052
#define LEFT 1053
#define HERE 1054

/*Colors*/
#define BLACK 40
#define GREEN 32

/*Types of rectangles*/
#define RECT_RES 1070
#define RECT_INVENT 1071
#define RECT_WEAP 1072
#define RECT_BATTLE 1073
#define RECT_INFO 1074
#define RECT_STORY 1075

/*Things about the interface*/
#define VISIBLE 1060
#define INVISIBLE 1061


/*Status*/
typedef enum{
    FAILED=2000, OK=2001
}Status;


/*Boolean*/
typedef enum{
    T=3000, F=3001
}Boolean;

/*Others*/
#define BUFFER_SIZE 128
#define NAME_SIZE 20
#define ERROR -11111


int rand_num(int inf, int sup);

#endif /* DEFINES_H */
