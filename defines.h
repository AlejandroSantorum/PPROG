#ifndef DEFINES_H
#define DEFINES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
#define AMMO 1021
#define FOOD 1022
#define DRINK 1023
#define MEDICINE 1024

/*Enemies types*/
#define ZOMBIE 1030
#define WALL 1031

/*Weapon owned*/
#define OWNED 1040
#define NOT_OWNED 1041

/*Orientation of character*/
#define NORTH 1050
#define SOUTH 1051
#define EAST 1052
#define WEST 1053


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
#define ERROR -11111

#endif /* DEFINES_H */
