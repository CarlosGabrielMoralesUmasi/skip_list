//https://replit.com/@Carlos_Gabriel1/UnfortunateBitesizedTypes#main.cpp
#include <iostream>
#include <time.h>
#include <ctime>
#include "skip_list.h"
/* el generador de int y char en txt:
https://replit.com/@Carlos_Gabriel1/generate#archivo.txt
*/

int main() {
    /*unsigned t0, t1;
    t0=clock()*/

    SLiist<int, string> da_list_skip(30);//nivel
    da_list_skip.cargar_file();
    /*t1 = clock();
 
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time Load: " << time << endl;*/
    cout << "tamaño list_skip:" << da_list_skip.size() << endl;
    
    da_list_skip.buscar(29928644);
    da_list_skip.buscar(322306595);
    /*t1 = clock();
 
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time Search: " << time << endl;*/
    //da_list_skip.mostrarSkip();

    da_list_skip.borrar(556515363);
    da_list_skip.borrar(764575100);
    /*t1 = clock();
 
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time Delete: " << time << endl;*/

    cout << "tamaño list_skip:" << da_list_skip.size() << endl;

   // da_list_skip.mostrarSkip();

    da_list_skip.file();
}

