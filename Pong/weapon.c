#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "weapon.h"

struct _weapon{
    char *name;
    int powder_waste;
    int speed;
    int damage;
    int owned; /*This value is equal to OWNED (1040) or NOT_OWNED (1041)*/
    int equipped;
    int row;
    int col;
};


Weapon** load_weapons(char *filename){
    Weapon **w=NULL;
    FILE *in=NULL;
    char buff[BUFFER_SIZE], name[NAME_SIZE];
    int i, j, n_weapons, powder_waste, speed, damage, owned, equipped, row, col;
    
    /* Checking*/
    if(filename == NULL){
        printf("Error. Weapons-F1-1.\n");
    }
    /*--------------------------------------------*/
    
    in = (FILE *) fopen(filename, "r");
    if(in == NULL){
        printf("Error. Weapons-F1-2.\n");
        return NULL;
    }
    
    fgets(buff, BUFFER_SIZE, in);
    sscanf(buff, "%d", &n_weapons);
    
    
    w = (Weapon **) malloc((n_weapons+1) * sizeof(Weapon*));
    if(w==NULL){
        printf("Error. Weapons-F1-3.\n");
        fclose(in);
        return NULL;
    }
    
    
    for(i=0; i<n_weapons; i++){
        fgets(buff, BUFFER_SIZE, in);
		sscanf(buff, "%s %d %d %d %d %d %d %d", name, &powder_waste, &speed, &damage, &owned, &equipped, &row, &col);
		
		w[i] = create_weapon(name, powder_waste, speed, damage, owned, equipped, row, col);
		if(w[i]==NULL){
		    printf("Error. Weapons-F1-4.\n");
		    for(j=i-1; j>=0; j--){
		        delete_weapon(w[j]);
		    }
		    free(w);
		    fclose(in);
		    return NULL;
		}
	}
	w[n_weapons] = NULL;
	
	fclose(in);
	
	return w;
}



Weapon* create_weapon(char *name, int powder_waste, int speed, int damage, int owned, int equipped, int row, int col){
    Weapon *weap;
    
    /*Checkings*/
    if(damage<0 || name==NULL || powder_waste<0 || speed<0 || row<0 || col<0){
        printf("Error. Weapons-F2-1.\n");
        return NULL;
    }
    if(owned != OWNED && owned != NOT_OWNED){
        printf("Error. Weapons-F2-2.\n");
        return NULL;
    }
    if(equipped != EQUIPPED && equipped != NOT_EQUIPPED){
        printf("Error. Weapons-F2-3.\n");
        return NULL;
    }
    /*-----------------------------------*/
    
     
    weap = (Weapon *) malloc(sizeof(Weapon));
    if(weap==NULL){
        printf("Error. Weapons-F2-4.\n");
        return NULL;
    }
    
     
    weap->name = strdup(name);
    weap->powder_waste = powder_waste;
    weap->speed = speed;
    weap->damage = damage;
    weap->owned = owned;
    weap->equipped = equipped;
    weap->row = row;
    weap->col = col;
    
    return weap;
}


void delete_weapon(Weapon *wp){
    if (wp==NULL) return;
    if (wp->name != NULL){
        free(wp->name);
    }
    free (wp);
}

void destroy_weapons(Weapon **wp){
    Weapon **aux=NULL;
    
    if(wp == NULL) return;
    
    for(aux = wp; *aux!=NULL; aux++){
        delete_weapon(*aux);
    }
    free(wp);
}

char *weapon_getName(Weapon* wp){
    if(wp==NULL){
        return NULL;
    }
    return wp->name;
}

int own_weapon(Weapon *wp){
    if (wp == NULL) return NOT_OWNED;
    if (wp->owned==OWNED)return OWNED;
    return NOT_OWNED;
}



int weapon_getPowderWaste(Weapon *wp){
    if(wp == NULL){
        return ERROR;
    }
    
    return wp->powder_waste;
}


int weapon_getSpeed(Weapon *wp){
    if(wp == NULL){
        return ERROR;
    }
    
    return wp->speed;
}


int weapon_getDamage(Weapon *wp){
    if(wp == NULL){
        return ERROR;
    }
    
    return wp->damage;
}

Status change_own(Weapon *wp){
    if(wp == NULL){
        return FAILED;
    }
    wp->owned = OWNED;
    
    return OK;
}


Status shot_weapon(Weapon **wp, Resources **r){
    Resources **auxr=NULL;
    Resources *r2=NULL;
    Weapon **auxw=NULL;
    Weapon *w2=NULL;
    
    if(wp==NULL||r==NULL){
        printf("Error. Weapons-F10-0.\n");
        return FAILED;
    } 
    
    for(auxr = r; (*auxr) != NULL; auxr++){ /*Searching for the resource of ammo*/
        if(resources_getObjectType(*auxr)==AMMO){
            r2 = *auxr;
        }
    }
    if(r2==NULL){
        printf("Error. Weapons-F10-1.\n");
        return FAILED;
    }
    
    for(auxw = wp; (*auxw) != NULL; auxw++){
        if((*auxw)->equipped == EQUIPPED){
            w2 = *auxw;
        }
    }
    if(w2==NULL){
        printf("Error. Weapons-F10-2.\n");
        return FAILED;
    }
    
    if(w2->powder_waste > resources_getActualValue(r2)) return FAILED;
    
    if(modify_resource(r2, -(w2->powder_waste)) == ERROR){
        printf("Ni puta idea de lo que ha pasado. Weapons-F10-3.\n");
        return FAILED;
    }
    
    return OK;
}


int weapon_getRow(Weapon *wp){
    if(wp == NULL){
        printf("Error. Weapons-F11-1\n");
        return ERROR;
    }
    
    return wp->row;
}


int weapon_getCol(Weapon *wp){
    if(wp == NULL){
        printf("Error. Weapons-F12-1.\n");
        return ERROR;
    }
    
    return wp->col;
}


Status change_equipped(Weapon **wp, int dir){
    Weapon **aux=NULL;
    
    /*Checkings*/
    if(wp == NULL){
        printf("Error. Weapons-F13-1.\n");
        return FAILED;
    }
    if(dir != UPW && dir != DOWNW){
        printf("Error. Weapons-F13-2.\n");
        return FAILED;
    }
    /*--------------------------------------*/
    
    
    for(aux = wp; *aux != NULL; aux++){
        if((*aux)->equipped == EQUIPPED){
            (*aux)->equipped = NOT_EQUIPPED;
            
            if(dir == DOWNW){
                while(1){
                    aux++;
                    if((*aux) == NULL){ /*If it´s reached the end of the array it has to comeback to the first weapon*/
                        aux = wp;
                    }
                    if((*aux)->owned == OWNED){ /*The weapon must be owned*/
                        (*aux)->equipped = EQUIPPED;
                        return OK;
                    }
                }
            }
            
            if(dir == UPW){
                while(1){
                    if(aux == wp){ /*If it is the first weapon and we want to equipp the last one*/
                        while(*aux != NULL){
                            aux++;
                        }
                    }
                    aux--;
                    if((*aux)->owned == OWNED){ /*The weapon must be owned*/
                        (*aux)->equipped = EQUIPPED;
                        return OK;
                    }
                }
            }
        }
    }
    return FAILED;
}


int weapon_equipped(Weapon *wp){
    if(wp == NULL){
        printf("Error. Weapons-F14-1.\n");
        return ERROR;   
    }
    
    if(wp->equipped == EQUIPPED){
        return EQUIPPED;
    }
    
    else{
        return NOT_EQUIPPED;
    }
}