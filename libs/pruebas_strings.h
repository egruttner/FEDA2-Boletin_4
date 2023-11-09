#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include "horspool.h"
#include "suffix_array.h"

using namespace std;

string fileName;
claseSuffixArray SuffixArray;
claseHorspool Horspool;

//Para leer archivo de texto
string leearchivo(int id_dataset, int indice_dataset)
{
    //cout<<"id_dataset:"<<id_dataset<<endl;
    //cout<<"indice_dataset:"<<indice_dataset<<endl;

    string fileName = "datasets/input" + to_string(id_dataset) + "/input" + to_string(indice_dataset) + ".txt";
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
    }
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    return text;
}


//PARA TOMAR EL TIEMPO
long long execution_time_ms(int id_proceso_seleccionado, int indice_dataset, int mide_solo_conteo) {

  string patron="";
  string textoArchivo="";
  
  int id_dataset = 1;

  //ASIGNACION DE PATRÓN DE ACUERDO AL EXPERIMENTO
  switch (id_proceso_seleccionado)
  {
  case 1:
  case 2:
    patron="010101"; id_dataset=3;
    break;
  case 3:
  case 4:
    patron="abc"; id_dataset=4;
    break;
  case 5:
  case 6:
    id_dataset=3;
    //PATRON VARIABLE - BINARIO
    switch (indice_dataset)
    {
    case 1:
      patron="0"; indice_dataset=3;
      break;
    case 2:
      patron="01"; indice_dataset=3;
      break;
    case 3:
      patron="010"; indice_dataset=3;
      break;
    case 4:
      patron="0101"; indice_dataset=3;
      break;
    case 5:
      patron="01010"; indice_dataset=3;
      break;
    default:
      break;
    }
    break;

  case 7:
  case 8:
    id_dataset=4;
    //PATRON VARIABLE - LETRAS
    switch (indice_dataset)
    {
    case 1:
      patron="a"; indice_dataset=3;
      break;
    case 2:
      patron="ab"; indice_dataset=3;
      break;
    case 3:
      patron="abc"; indice_dataset=3;
      break;
    case 4:
      patron="abcd"; indice_dataset=3;
      break;
    case 5:
      patron="abcde"; indice_dataset=3;
      break;
    default:
      break;
    }
    break;

  default:
    break;
  }

  auto start_time = chrono::high_resolution_clock::now();
  switch (id_proceso_seleccionado)
  {
   //Boyer-Moore-Horspool
  case 1:
  case 3:
  case 5: 
  case 7:
    //Lee archivo
    textoArchivo=leearchivo(id_dataset, indice_dataset);
    //Precalcula
    Horspool.precalcular(patron);
    //Calcula
    if (mide_solo_conteo==1)
    {
      //Resetea el medidor de tiempo para no considerar el precálculo
      start_time = chrono::high_resolution_clock::now();
    }
    Horspool.contar(textoArchivo,patron);
    break;

  //Suffix Array
  case 2: 
  case 4:
  case 6:
  case 8:
    //Lee archivo
    textoArchivo=leearchivo(id_dataset, indice_dataset);
    //Precalcula
    SuffixArray.precalcular(textoArchivo);
    //Calcula
    if (mide_solo_conteo==1)
    {
      //Resetea el medidor de tiempo para no considerar el precálculo
      start_time = chrono::high_resolution_clock::now();
    }
    SuffixArray.contar(textoArchivo,patron);
    break;
  
  default:
    break;
  }

  auto end_time = chrono::high_resolution_clock::now();
  return chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
}

