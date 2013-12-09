#include "intervaloperators.hpp"
using namespace std;
 

/**
*   Copie de la valeur de la premiere et deuxieme borne dans la borne res
*/
void put_res(Bound* res, Bound* first, Bound* second = 0, int offset = 2)
{
    copy(first, first + offset, res);
    if(second != 0)
        copy(second, second + offset, res + offset);
}
/**
*   Retourne la valeur maximale entre deux valeurs flottantes
*/
float max(float first, float second)
{
    return (first > second ? first : second);
}
/**
*   Retourne la valeur minimale entre deux valeurs flottantes
*/
float min(float first, float second)
{
    return (first < second ? first : second);
}
/**
*   Retourne la valeur maximale entre deux bornes
*/
Bound max(Bound first, Bound second)
{
    return (first.t > second.t ? first : second);
}
/**
*   Retourne la valeur minimale entre deux bornes
*/
Bound min(Bound first, Bound second)
{
    return (first.t < second.t ? first : second);
}
/**
* Chaque évènements est de type Bound et le champs data doit être manipulé de façon opaque.
* Cette fonction doit remplir le tableau pré-alloué res. Cette pré-allocation assure que la mémoire sera
* suffisante pour stocker le résultat de l'union de a et de b.
*
* Cette fonction doit donner dans size_res le nombre exact d'évènements stockée dans res.
* @todo Fonction à écrire par les étudiants pour le devoir \ref DevoirCSG
*/
void union_of_intervals(Bound *a, int size_a, Bound *b, int size_b, Bound *res, int *size_res){
    *size_res = 0;
 
    if(size_a == 0 || size_b == 0)
    {
        if(size_a == 0 && size_b == 0)
            return;
        else if(size_a == 0)
            put_res(res, b);
        else
            put_res(res, a);
 
        *size_res = 2;
        return;
    }
 
    if( a[1].t < b[0].t )
    {
        put_res(res, a, b);
        *size_res = 4;
        return;
    }
    else if( a[0].t > b[1].t )
    {
        put_res(res, b, a);
        *size_res = 4;
        return;
    }
 
    res[0] = min(a[0], b[0]);
    res[1] = max(a[1], b[1]);
 
    *size_res = 2;
}
/**
* Chaque évènements est de type Bound et le champs data doit être manipulé de façon opaque.
* Cette fonction doit remplir le tableau pré-alloué res. Cette pré-allocation assure que la mémoire sera
* suffisante pour stocker le résultat de l'intersection de a et de b.
*
* Cette fonction doit donner dans size_res le nombre exact d'évènements stockée dans res.
* @todo Fonction à écrire par les étudiants pour le devoir \ref DevoirCSG
*/
void intersection_of_intervals(Bound *a, int size_a, Bound *b, int size_b, Bound *res, int *size_res){
    *size_res = 0;
 
    if( size_a == 0 || size_b == 0 )
    {
        return;
    }
 
    if( a[1].t <= b[0].t || a[0].t >= b[1].t )
    {
        return;
    }
 
    res[0] = max(a[0], b[0]);
    res[1] = min(a[1], b[1]);
 
    *size_res = 2;
}
/**
* Chaque évènements est de type Bound et le champs data doit être manipulé de façon opaque.
* Cette fonction doit remplir le tableau pré-alloué res. Cette pré-allocation assure que la mémoire sera
* suffisante pour stocker le résultat de la différence de a et de b.
*
* Cette fonction doit donner dans size_res le nombre exact d'évènements stockée dans res.
* @todo Fonction à écrire par les étudiants pour le devoir \ref DevoirCSG
*/
void difference_of_intervals(Bound *a, int size_a, Bound *b, int size_b, Bound *res, int *size_res){
    *size_res = 0;
 
    if(size_a == 0)
    {
        return;
    }
 
    if(size_b == 0)
    {
        put_res(res, a);
        *size_res = 2;
        return;
    }
 
    if( a[1].t <= b[0].t || a[0].t >= b[1].t )
    {
        put_res(res, a);
        *size_res = 2;
        return;
    }
 
    if( b[0].t <= a[0].t && b[1].t >= a[1].t )
    {
        return;
    }
 
    if( b[0].t > a[0].t && b[1].t < a[1].t )
    {
        res[0] = a[0];
        res[1] = b[0];
        res[2] = b[1];
        res[3] = a[1];
        *size_res = 4;
 
        return;
    }
 
    if( b[0].t <= a[0].t && b[1].t > a[0].t)
    {
        res[0] = b[1];
        res[1] = a[1];
        *size_res = 2;
        return;
    }
 
    if( b[0].t < a[1].t && b[0].t > a[0].t)
    {
        res[0] = a[0];
        res[1] = b[0];
        *size_res = 2;
        return;
    }
 
}
