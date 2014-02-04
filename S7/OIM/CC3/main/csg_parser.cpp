#include "csg_parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
*Enumertion des types d'objets
*/
enum { SPHERE, CYLINDER, CONE, BOX3D };

char* get_token(char* str, char* name)
{
    int i = 0;
 
    while( i < 10 && str[i] != ' ' && str[i] != ')' && str[i] != '\0' )
    {
        name[i] = str[i];
        i++;
    }
    name[i] = '\0';
    if(i >= 10)
        return NULL;
    if( str[i] == '\0' || str[i] == ')' )
        return NULL;
 
    return &(str[i + 1]);
}

/* --------------------------------------------------------------- */
/*						Simple CSG tree parser					   */
/* --------------------------------------------------------------- */

/*
 * Cette fonction est à écrire, pour la question 2 du devoir DevoirCSG.
 */

void msg_error(const char* str){
    printf("Error : %s\n", str);
}

Geometry * csg_parse(char *str){
    int i = 0;
    char* strLeft = NULL;
    char* strRight = NULL;
    float var[12] = {0.f};
    int nbVar = 0;
    int type = -1;
    int cpt = 1;
    char* result;
    int indice;
    char token[10];
    char name[10];
    Geometry * leftObject = NULL;
    Geometry * rightObject = NULL;

    if(str == NULL)
    {
        msg_error("str is NULL");
        return NULL;
    }
    /* debut de la chaine */
    if(str[i] != '(')
    {
        msg_error(" ( is missing");
        return NULL;
    }
    i++;
    /* quel operation veut on effectuer ?*/
    if(str[i] == '+' || str[i] == '*' || str[i] == '-')
    {
        if(str[i] == '\0' || str[i+1] == '\0' || str[i+2] == '\0')
        {
            msg_error("some instructions are missing");
            return NULL;
        }
        strLeft = &(str[i+2]);
        indice = i + 3;
        while(cpt > 0)
        {
            if(str[indice] == '\0')
            {
                msg_error("some instructions are missing");
                return NULL;
            }
            if(str[indice] == '(')
                cpt++;
            if(str[indice] == ')')
                cpt--;
            indice++;
        }
        strRight = &(str[indice + 1]);
        cpt = 1;
        if(str[indice] == '\0' || str[indice+1] == '\0')
        {
            msg_error("some instructions are missing");
            return NULL;
        }
        indice = indice + 2;
        while(cpt > 0)
        {
            if(str[indice] == '\0')
            {
                msg_error("some instructions are missing");
                return NULL;
            }
            if(str[indice] == '(')
                cpt++;
            if(str[indice] == ')')
                cpt--;
            indice++;
        }
        leftObject = csg_parse(strLeft);
        rightObject = csg_parse(strRight);
 
        if(leftObject == NULL || rightObject == NULL)
            return NULL;
        /*
        * generation de l'operation
        */
        switch(str[i]){
            case '+':
                return create_csg_union(leftObject, rightObject);
                break;
            case '*':
                return create_csg_intersection(leftObject, rightObject);
                break;
            case '-':
                return create_csg_difference(leftObject, rightObject);
                break;
            default:
                return NULL;
                break;
        }
    }
    result = &(str[i]);
    if((result = get_token(result, name) ) == NULL )
    {
        msg_error("bad instruction");
        return NULL;
    }
    /* type de l'objet */
    if( strcmp(name, "sp") == 0 )
    {
        type = SPHERE;
        nbVar = 4;
    }
    else if( strcmp(name, "cy") == 0 )
    {
        type = CYLINDER;
        nbVar = 8;
    }
    else if( strcmp(name, "co") == 0 )
    {
        type = CONE;
        nbVar = 7;
    }
    else if( strcmp(name, "bo") == 0 )
    {
        type = BOX3D;
        nbVar = 12;
    }
    else
    {
        printf("wrong operator or object type %s\n", name);
        return NULL;
    }
 
    for(i = 0; i < nbVar; i++)
    {
        if((result = get_token(result, token)) == NULL )
        {
            if( i+1 < nbVar )
            {
                printf("not enough arguments for object %s\n", name);
                return NULL;
            }
        }
        var[i] = atof(token);
    }
    /* creation de l'objet */
    switch(type)
    {
        case SPHERE:
            return create_sphere(var[0], var[1], var[2], var[3]);
        case CYLINDER:
            return create_cylinder(var[0], var[1], var[2], var[3],
                     var[4], var[5], var[6], var[7]);
        case CONE:
            return create_cone(var[0], var[1], var[2], var[3], var[4],
                     var[5], var[6]);
        case BOX3D:
            return create_box(var[0], var[1], var[2], var[3], var[4],
                     var[5], var[6], var[7], var[8], var[9], var[10],
                      var[11]);
    }
    return NULL;
}
