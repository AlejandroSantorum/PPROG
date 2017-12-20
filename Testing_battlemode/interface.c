#include "interface.h"

/*Creates the interface struct reading all the rectangles information and all the maps from the files*/
Interface* create_intrf(char* rect_fname, char* maps_fname){
    int n_rect, i, j, ini_row, ini_col, last_row, last_col, bg, fg, rect_type;
    FILE *in=NULL;
    char buff[BUFFER_SIZE];
    Interface *intrf=NULL;
    Maps **aux=NULL;
    
    /*-----------Checkings-------------------------*/
    if(rect_fname==NULL){
        printf("Error. Interface-F1-1.\n");
        exit(ERROR);
    }
    
    if(maps_fname==NULL){
        printf("Error. Interface-F1-2.\n");
        exit(ERROR);
    }
    /*-----------------------------------------------*/
    
    in = (FILE *) fopen(rect_fname, "r");
    if(in == NULL){
        printf("Error. Interface-F1-3.\n");
        exit(ERROR);
    }
    
    intrf = (Interface *) malloc(sizeof(Interface));
    if(intrf == NULL){
        printf("Error. Interface-F1-4.\n");
        exit(ERROR);
    }
    
    fgets(buff, BUFFER_SIZE, in);
    sscanf(buff, "%d", &n_rect);
    
    intrf->rect_array = (rectangle **) malloc(n_rect * sizeof(rectangle *));
    for(i=0; i<n_rect; i++){
        fgets(buff, BUFFER_SIZE, in);
	    sscanf(buff, "%d %d %d %d %d %d %d", &ini_row, &ini_col, &last_row, &last_col, &bg, &fg, &rect_type);

	    intrf->rect_array[i] = win_new(ini_row, ini_col, last_row, last_col, bg, fg, rect_type);
	    if(intrf->rect_array[i]==NULL){
		    printf("Error. Interface-F1-5.\n");
	        for(j=i-1; j>=0; j--){
	         win_delete(intrf->rect_array[j]);
	        }
	        free(intrf->rect_array);
	        free(intrf);
	        fclose(in);
	        exit(ERROR);
	    }
    }
    
    intrf->n_rectangles = n_rect;
    
    intrf->maps_array = load_maps(maps_fname);
    if(intrf->maps_array == NULL){
        printf("Error. Interface-F1-6.\n");
        for(j=0; j<n_rect; j++){
            win_delete(intrf->rect_array[j]);
        }
        free(intrf->rect_array);
        free(intrf);
        fclose(in);
        exit(ERROR);
    }
    for(aux = intrf->maps_array, i=1; *aux != NULL; aux++, i++);
    
    intrf->n_maps = i-1;
    
    fclose(in);
    
    return intrf;
}


/*Frees all the allocated memory for the interface*/
void destroy_intrf(Interface *intrf){
    int i;
    
    if(intrf == NULL){
        printf("Error. Interface-F2-1.\n");
        exit(ERROR);
    }
    
    for(i=0; i<intrf->n_rectangles; i++){
        win_delete(intrf->rect_array[i]);
    }
    free(intrf->rect_array);
    
    if(intrf->maps_array != NULL){
        destroy_maps(intrf->maps_array);
    }
    free(intrf);
}


/*Function that prints all the actual resources information of the array*/
Status print_resources(Interface *intrf, Resources **r){
    int i, num;
    Resources **aux=NULL;
    char *buff, *str;
    
    if(intrf == NULL || r == NULL){
        printf("Error. Interface-F3-1.\n");
        exit(ERROR);
    }
    
    for(i=0; i<intrf->n_rectangles; i++){ /*Searching for the rectangle which is going to print the resources*/
        if(rectangle_getType(intrf->rect_array[i]) == RECT_RES){ /*Found it*/
        
            num = rectangle_getNCols(intrf->rect_array[i]) - 1;
            
            for(aux = r; *aux != NULL; aux++){  /*Printing all the resources information*/
                buff = (char *) malloc(num * sizeof(char));
                if(buff == NULL){
                    printf("Error. Interface-F3-2.\n");
                    exit(ERROR);
                }
                str = (char *) malloc(num * sizeof(char));
                if(str == NULL){
                    printf("Error. Interface-F3-3.\n");
                    exit(ERROR);
                }
                
                strcpy(buff, resources_getName(*aux));
                sprintf(str, ": %05d / %d", resources_getActualValue(*aux), resources_getMax(*aux));
                strcat(buff, str);
                
                win_write_line_at(intrf->rect_array[i], resources_getRow(*aux), resources_getCol(*aux), buff);
                
                free(buff);
                free(str);
            }
            return OK;
        }
    }
    printf("Error. Interface-F3-4.\n");
    exit(ERROR);
}


/*Function that prints all the actual weapons information of the array*/
Status print_weapons(Interface *intrf, Weapon **wp){
    int i, num;
    Weapon **aux=NULL;
    char *buff, *str;
    
    if(intrf == NULL || wp == NULL){
        printf("Error. Interface-F4-1.\n");
        exit(ERROR);
    }
    
    for(i=0; i<intrf->n_rectangles; i++){ /*Searching for the rectangle which is going to print the 0*/
        if(rectangle_getType(intrf->rect_array[i]) == RECT_WEAP){ /*Found it*/
        
            num = rectangle_getNCols(intrf->rect_array[i]) - 1;
            
            for(aux = wp; *aux != NULL; aux++){  /*Printing all the weapons information*/
                if(own_weapon(*aux) == OWNED){ /*BUT we only print those who are OWNED*/
                    buff = (char *) malloc(num * sizeof(char));
                    if(buff == NULL){
                        printf("Error. Interface-F4-2.\n");
                        exit(ERROR);
                    }
                    str = (char *) malloc(num * sizeof(char));
                    if(buff == NULL){
                        printf("Error. Interface-F4-2.\n");
                        exit(ERROR);
                    }
                
                    strcpy(buff, weapon_getName(*aux));
                    sprintf(str, ": %d", weapon_getPowderWaste(*aux));
                    strcat(buff, str);
                    if(weapon_equipped(*aux) == EQUIPPED){
                        strcat(buff, " E");
                    }
                    else if(weapon_equipped(*aux) == NOT_EQUIPPED){
                        strcat(buff, " N");
                    }
                    
                    win_write_line_at(intrf->rect_array[i], weapon_getRow(*aux), weapon_getCol(*aux), buff);
                
                    free(buff);
                    free(str);
                }
            }
            return OK;
        }
    }
    
    printf("Error. Interface-F4-3.\n");
    exit(ERROR);
}


/*Function that prints all the actual objects information of the array*/
Status print_objects(Interface *intrf, Object **obj){
    int i, num;
    Object **aux=NULL;
    char *buff, *str;
    
    if(intrf == NULL || obj == NULL){
        printf("Error. Interface-F5-1.\n");
        exit(ERROR);
    }
    
    for(i=0; i<intrf->n_rectangles; i++){ /*Searching for the rectangle which is going to print the resources*/
        if(rectangle_getType(intrf->rect_array[i]) == RECT_INVENT){ /*Found it*/
        
            num = rectangle_getNCols(intrf->rect_array[i]) - 1;
            
            for(aux = obj; *aux != NULL; aux++){  /*Printing all the resources information*/
                buff = (char *) malloc(num * sizeof(char));
                if(buff == NULL){
                    printf("Error. Interface-F5-2.\n");
                    exit(ERROR);
                }
                str = (char *) malloc(num * sizeof(char));
                if(buff == NULL){
                    printf("Error. Interface-F5-2.\n");
                    exit(ERROR);
                }
                
                strcpy(buff, object_getName(*aux));
                sprintf(str, ": %d  %d", object_getAmount(*aux), object_getValue(*aux));
                strcat(buff, str);
                
                win_write_line_at(intrf->rect_array[i], object_getRow(*aux), object_getColumn(*aux), buff);
                
                free(buff);
                free(str);
            }
            return OK;
        }
    }
    printf("Error. Interface-F5-3.\n");
    exit(ERROR);
}


/*Function that prints the map with map_id as id*/
Status print_map(Interface *intrf, int map_id){
    int i, j, r, ini_row, ini_col, last_row, n_rows;
    rectangle *aux=NULL;
    Maps *map=NULL;
    
    if(intrf == NULL || map_id < 0){
        printf("Error. Interface-F6-1.\n");
        exit(ERROR);
    }
    
    for(j=0; j<intrf->n_maps; j++){ /* Searching for the correct map */
        if(map_getId(intrf->maps_array[j]) == map_id){
            map = intrf->maps_array[j];
        }
    }
    if(map == NULL){
        printf("Error. Interface-F6-2.\n");
        return FAILED;
    }
    
    r = map->n_rows;
    
    for(j=0; j < intrf->n_rectangles; j++){
        if(rectangle_getType(intrf->rect_array[j]) == RECT_BATTLE){
            aux = intrf->rect_array[j];
            ini_row = intrf->rect_array[j]->ini_row;
            ini_col = intrf->rect_array[j]->ini_row;
            last_row = intrf->rect_array[j]->last_row;
            n_rows = intrf->rect_array[j]->n_rows;
            break;
        }
    }
    
    if(r != n_rows-2){
        printf("Error. Interface-F6-2.\n");
        exit(ERROR);
    }
    
    if(aux == NULL){
        printf("Error. Interface-F6-3.\n");
        exit(ERROR);
    }
    
    for(j = 0, i=ini_row + 1; i < last_row; j++, i++){ /* Printing the map */
        win_write_line_at(aux, i, ini_col + 1, map->field[j]);
    }
    
    return OK;
}


/*Prints the resources, weapons, objects, player and initial map at the beggining of the program*/
Status initialize_intrf(Interface *intrf, int initial_map, Resources **r, Weapon **wp, Object **obj, Player *pl){
    int i, j;
    rectangle *aux=NULL;
    
    /* Error checking */
    if(intrf == NULL || initial_map < 0){
        printf("Error. Interface-F7-1.\n");
        exit(ERROR);
    }
    
    /* Drawing all the rectangle of the interface */
    for(i=0; i < intrf->n_rectangles; i++){
        rectangle_draw(intrf->rect_array[i]);
    }
    
    /* Printing the resources */
    print_resources(intrf, r);
    
    /* Printing the armory */
    print_weapons(intrf, wp);
    
    /* Printing the inventory */
    print_objects(intrf, obj);
    
    /* Printing the initial map */
    print_map(intrf, initial_map);
    
    /* Looking for the Battlefield rectangle in order to print the player sign there later */
    for(j=0; j < intrf->n_rectangles; j++){
        if(rectangle_getType(intrf->rect_array[j]) == RECT_BATTLE){
            aux = intrf->rect_array[j];
            break;
        }
    }
    if(aux == NULL){
        printf("Error. Interface-F7-2.\n");
        exit(ERROR);
    }
    
    /* Printing the player at the initial position */
    win_write_char_at(aux, player_getRow(pl), player_getCol(pl), player_getDisplay(pl));
    
    return OK;
}


/*Function that allows the player to move*/
static int Dr[5] = {-1, 1, 0, 0, 0}; 
static int Dc[5] = {0, 0, 1, -1, 0};
void move(Interface *intrf, int map_id, Player *pl, int dir){
    int fin_row, fin_col, j, act_row, act_col, go;
    Maps *map=NULL;
    rectangle *aux=NULL;
    
    if(dir != UP && dir != DOWN && dir != LEFT && dir != RIGHT && dir != HERE){
        printf("Error. Interface-F8-1\n");
        return;
    }
    if(intrf==NULL ||pl==NULL){
        printf("Error. Interface-F8-2.\n");
        return;
    }
    act_row = player_getRow(pl);
    act_col = player_getCol(pl);
    go = dir - UP;
    fin_row =  act_row + Dr[go]; 
    fin_col =  act_col + Dc[go];
    
    for(j=0; j<intrf->n_maps; j++){ /* Searching the map */
        if(map_getId(intrf->maps_array[j]) == map_id){
            map = intrf->maps_array[j];
            break;
        }
    }
    if(map == NULL){
        printf("Error. Interface-F8-3.\n");
        return;
    }
    
    for(j=0; j < intrf->n_rectangles; j++){ /*Searching the rectangle */
        if(rectangle_getType(intrf->rect_array[j]) == RECT_BATTLE){
            aux = intrf->rect_array[j];
            break;
        }
    }
    if(aux==NULL){
        printf("Error. Interface-F8-4.\n");
        return;
    }
    
    if(fin_row<=1 || fin_col<=1 || fin_row >= aux->last_row || fin_col >= aux->last_col) return;
    
    
    if(map->field[fin_row-2][fin_col-2] == ' '){
        win_write_char_at(aux, act_row, act_col, ' ');
    
        win_write_char_at(aux, fin_row, fin_col, player_getDisplay(pl));
    
        player_setLocation(pl, fin_row, fin_col);
        
        return;
    }
    return;
}


/*Function that allows the player to shoot*/
void *shoot(void *x){
    shoot_stuff *stst = (shoot_stuff *) x;
    Interface *intrf = stst->intrf;
    Weapon **wp = stst->wp;
    Player *pl = stst->pl;
    Resources **r = stst->r;
    int map_id = stst->map_id;
    int dir = stst->dir;
    int row, col, go, next_row, next_col, r_aux, c_aux, j, flag=0;
    Weapon *w=NULL;
    Maps *map=NULL;
    rectangle *aux=NULL;
    
    /* Checkings */
    if(intrf == NULL || wp == NULL || r == NULL || pl == NULL){
        printf("Error. Interface-F9-1.\n");
        exit(0);
    }
    /*----------------------------*/
    
    if(shot_weapon(wp, r) == FAILED){
        return NULL;
    }
    
    print_resources(intrf, r);
    
    /*Now, if it had enough gunpowder to shoot, we print the bullet */
    
    w = weapon_getEquippedWeapon(wp); /*We get the weapon equipped at this moment*/
    if(w == NULL){
        printf("Error. Interface-F9-2.\n");
        exit(0); 
    }
    
    for(j=0; j<intrf->n_maps; j++){ /* Searching the map */
        if(map_getId(intrf->maps_array[j]) == map_id){
            map = intrf->maps_array[j];
            break;
        }
    }
    if(map == NULL){
        printf("Error. Interface-F9-3.\n");
        exit(0);
    }
    
    for(j=0; j < intrf->n_rectangles; j++){ /*Searching the rectangle */
        if(rectangle_getType(intrf->rect_array[j]) == RECT_BATTLE){
            aux = intrf->rect_array[j];
            break;
        }
    }
    if(aux==NULL){
        printf("Error. Interface-F9-4.\n");
        exit(0);
    }
    
    go = dir-UP;
    row = player_getRow(pl);
    col = player_getCol(pl);
    while(1){
        usleep(weapon_getSpeed(w));
        
        next_row = row + Dr[go];
        next_col = col + Dc[go];
        
        if(next_row<=1 || next_col<=1 || next_row >= aux->last_row || next_col >= aux->last_col){
            r_aux = player_getRow(pl);
            c_aux = player_getCol(pl);
            if(r_aux == row && c_aux == col){
                return NULL;
            }
    
            win_write_char_at(aux, row, col, ' ');
            return NULL;
        } 
        
        
        if(map->field[next_row-2][next_col-2] == ' '){
            if(flag != 0){
            win_write_char_at(aux, row, col, ' ');
            }
        
            flag = 1;
            win_write_char_at(aux, next_row, next_col, 'o');
        
            row = next_row;
            col = next_col;
            continue;
        }
        r_aux = player_getRow(pl);
        c_aux = player_getCol(pl);
        if(r_aux == row && c_aux == col){
            return NULL;
        }
            
        win_write_char_at(aux, row, col, ' ');
            
        return NULL;
    }
}