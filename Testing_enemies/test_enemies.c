#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "resources.h"
#include "enemies.h"

int main(){
  Enemy **enemies=NULL;
  Enemy **enemies2=NULL;
  
  enemies = load_enemies("enemies.txt");
  if(enemies == NULL){
    printf("Error when allocating memory for double enemies´ pointer.\n");
    return ERROR;
  }
  
  printf("\nEnemy 1.\n");
  printf("%c ", enemy_getDisplay(enemies[0]));
  printf("%d ", enemy_getType(enemies[0]));
  printf("%d ", enemy_getHP(enemies[0]));
  printf("%d ", enemy_getSpeed(enemies[0]));
  printf("%d ", enemy_getDamage(enemies[0]));
  printf("%d ", enemy_getRow(enemies[0]));
  printf("%d ", enemy_getCol(enemies[0]));
  printf("%s ", enemy_getName(enemies[0]));

  printf("\nEnemy 2.\n");
  printf("%c ", enemy_getDisplay(enemies[1]));
  printf("%d ", enemy_getType(enemies[1]));
  printf("%d ", enemy_getHP(enemies[1]));
  printf("%d ", enemy_getSpeed(enemies[1]));
  printf("%d ", enemy_getDamage(enemies[1]));
  printf("%d ", enemy_getRow(enemies[1]));
  printf("%d ", enemy_getCol(enemies[1]));
  printf("%s ", enemy_getName(enemies[1]));

  
  printf("\nEnemy 3.\n");
  printf("%c ", enemy_getDisplay(enemies[2]));
  printf("%d ", enemy_getType(enemies[2]));
  printf("%d ", enemy_getHP(enemies[2]));
  printf("%d ", enemy_getSpeed(enemies[2]));
  printf("%d ", enemy_getDamage(enemies[2]));
  printf("%d ", enemy_getRow(enemies[2]));
  printf("%d ", enemy_getCol(enemies[2]));
  printf("%s ", enemy_getName(enemies[2]));

  
  printf("\nEnemy 4.\n");
  printf("%c ", enemy_getDisplay(enemies[3]));
  printf("%d ", enemy_getType(enemies[3]));
  printf("%d ", enemy_getHP(enemies[3]));
  printf("%d ", enemy_getSpeed(enemies[3]));
  printf("%d ", enemy_getDamage(enemies[3]));
  printf("%d ", enemy_getRow(enemies[3]));
  printf("%d ", enemy_getCol(enemies[3]));
  printf("%s ", enemy_getName(enemies[3]));
  printf("\n\n");
  
  
  enemies2 = (Enemy **) malloc(5 * sizeof(Enemy *));
  
  enemies2[0] = generate_enemy(enemies,"Sacacorchos");
  if(enemies2[0]==NULL){
    printf("\nPeto en el 0.\n");
  }
  
  enemies2[1] = generate_enemy(enemies, "Rapidzombie");
  if(enemies2[1]==NULL){
    printf("\nPeto en el 1.\n");
  }
  
  enemies2[2] = generate_enemy(enemies,"Lanzasemen");
  if(enemies2[2]==NULL){
    printf("\nPeto en el 2.\n");
  }
  
  enemies2[3] = generate_enemy(enemies,"Muro");
  if(enemies2[3]==NULL){
    printf("\nPeto en el 3.\n");
  }
  enemies2[4]=NULL;
  
  printf("\nEnemy 1.2.\n");
  printf("%c ", enemy_getDisplay(enemies2[0]));
  printf("%d ", enemy_getType(enemies2[0]));
  printf("%d ", enemy_getHP(enemies2[0]));
  printf("%d ", enemy_getSpeed(enemies2[0]));
  printf("%d ", enemy_getDamage(enemies2[0]));
  printf("%d ", enemy_getRow(enemies2[0]));
  printf("%d ", enemy_getCol(enemies2[0]));
  printf("%s ", enemy_getName(enemies2[0]));
  
  printf("\nEnemy 2.2.\n");
  printf("%c ", enemy_getDisplay(enemies2[1]));
  printf("%d ", enemy_getType(enemies2[1]));
  printf("%d ", enemy_getHP(enemies2[1]));
  printf("%d ", enemy_getSpeed(enemies2[1]));
  printf("%d ", enemy_getDamage(enemies2[1]));
  printf("%d ", enemy_getRow(enemies2[1]));
  printf("%d ", enemy_getCol(enemies2[1]));
  printf("%s ", enemy_getName(enemies2[1]));

  
  printf("\nEnemy 3.2.\n");
  printf("%c ", enemy_getDisplay(enemies2[2]));
  printf("%d ", enemy_getType(enemies2[2]));
  printf("%d ", enemy_getHP(enemies2[2]));
  printf("%d ", enemy_getSpeed(enemies2[2]));
  printf("%d ", enemy_getDamage(enemies2[2]));
  printf("%d ", enemy_getRow(enemies2[2]));
  printf("%d ", enemy_getCol(enemies2[2]));
  printf("%s ", enemy_getName(enemies2[2]));

  
  printf("\nEnemy 4.2.\n");
  printf("%c ", enemy_getDisplay(enemies2[3]));
  printf("%d ", enemy_getType(enemies2[3]));
  printf("%d ", enemy_getHP(enemies2[3]));
  printf("%d ", enemy_getSpeed(enemies2[3]));
  printf("%d ", enemy_getDamage(enemies2[3]));
  printf("%d ", enemy_getRow(enemies2[3]));
  printf("%d ", enemy_getCol(enemies2[3]));
  printf("%s ", enemy_getName(enemies2[3]));
  printf("\n\n");
  
  if(modify_enemyhp(enemies2[0], -10000) == ERROR){
      return -1;
  }
  if(enemy_getPhyStat(enemies[0])==DEAD){
        printf("\nEnemy 0 is dead.\n");
  }

  if(modify_enemyhp(enemies2[0], -10) == ERROR){
      return -1;
  }
  
  if(modify_enemyhp(enemies2[1], 20) == ERROR){
      return -1;
  }
  if(enemy_getPhyStat(enemies[1])==DEAD){
        printf("\nEnemy 1 is dead.\n");
  }
  if(modify_enemyhp(enemies2[2], -10) == ERROR){
      return -1;
  }
  if(enemy_getPhyStat(enemies[2])==DEAD){
        printf("\nEnemy 2 is dead.\n");
  }
  if(modify_enemyhp(enemies2[3], -100) == ERROR){
      return -1;
  }
  if(enemy_getPhyStat(enemies[3])==DEAD){
        printf("\nEnemy 3 is dead.\n");
  }
  
  printf("0 - %d \n", enemy_getHP(enemies2[0]));
  printf("0 - %d \n", enemy_getPhyStat(enemies2[0]));
  printf("1 - %d \n", enemy_getHP(enemies2[1]));
  printf("2 - %d \n", enemy_getHP(enemies2[2]));
  printf("3 - %d \n", enemy_getHP(enemies2[3]));
  
  
  destroy_enemies(enemies2);
  destroy_enemies(enemies);
  
  return 0;
}