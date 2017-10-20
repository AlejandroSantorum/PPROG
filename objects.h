#ifndef OBJECTS_H
#define OBJECTS_H

#include "defines.h"
#include "resources.h"

#define MAXNAME 64
/* In the following structure:
        object_type: depending on the number received it is one type or another; resource(ammo as well), enemy, weapons, usables.
        name: name as the objects is know in the game.
        
        

*/

typedef struct _object Object;


/*Function that load all the objects from a file*/
Object** load_objects(char *filename);
  
  
/*Function that receives the name, the serial number, the type and creates an object (used mainly in "load_objects" function)*/
Object* create_object(char *name, int type, int value, int amount);
  
  
/*Function that receives an object and destroys it*/
void destroy_object(Object *ob);
 
/*Function that generates an enemy whose name is given*/
Object* generate_object(Object **po, char *name);
  
/*Function that uses an object*/
Status use_object(Object *ob, Resource **r);
  

/*Function that returns the amount of an object*/
int object_getAmount(Object *ob);

/*Function that */



#endif /* OBJECTS_H */  