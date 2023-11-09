#include <chrono>
#include "libs/pruebas_strings.h"
#include <cstring> 
#include <fstream>

using namespace std;

int main(int argv, char* argc[]) {
  srand(time(NULL)); 

  long n;
  string dir_csv;
  string proceso_selecionado;
  int id_proceso_selecionado;
  string nombre_archivo_salida;
  int indice_dataset;
  int mide_solo_conteo;

  int numero_de_experimentos = 30; //Deben ser 30

  cout<<"INICIO"<<endl;

  //TIPOS DE PRUEBAS
  switch(atoi(argc[1]))
  {
    case 1: proceso_selecionado = "Binario-Texto_Variable-Boyer-Moore-Horspool"; break;
    case 2: proceso_selecionado = "Binario-Texto_Variable-SuffixArray"; break;

    case 3: proceso_selecionado = "Letras-Texto_Variable-Boyer-Moore-Horspool"; break;
    case 4: proceso_selecionado = "Letras-Texto_Variable-SuffixArray"; break;

    case 5: proceso_selecionado = "Binario-Patron_Variable-Boyer-Moore-Horspool"; break;
    case 6: proceso_selecionado = "Binario-Patron_Variable-SuffixArray"; break;

    case 7: proceso_selecionado = "Letras-Patron_Variable-Boyer-Moore-Horspool"; break;
    case 8: proceso_selecionado = "Letras-Patron_Variable-SuffixArray"; break;


    default: proceso_selecionado = ""; break;
  }


  //SI VIENE CON PARÁMETRO "head" entonces solamente crea la cabecera del archivo CSV
  if((strcmp(argc[2],"--head") == 0))
  {
    //DEFINE DIRECTORIO DE CSV
    if (atoi(argc[3]) == 1)
    {
      //Mide solamente cálculo sin considerar pre-procesamiento
      dir_csv = "csv_solo_contar/";
    }
    else
    {
      //Procesamiento completo
      dir_csv = "csv/";
    }

    nombre_archivo_salida = dir_csv + proceso_selecionado + "_results.csv";
    ofstream outfile(nombre_archivo_salida);
    outfile << "n,tiempo[ms]\n";

    return 0;
  }
  else
  {

    //BUSQUEDA SELECCIONADA COMO PARAMETRO
    id_proceso_selecionado = atoi(argc[1]);
    indice_dataset = atoi(argc[3]);
    mide_solo_conteo = atoi(argc[4]);

    //DEFINE DIRECTORIO DE CSV
    if (mide_solo_conteo == 1)
    {
      //Mide solamente cálculo sin considerar pre-procesamiento
      dir_csv = "csv_solo_contar/";
    }
    else
    {
      //Procesamiento completo
      dir_csv = "csv/";
    }

    nombre_archivo_salida = dir_csv + proceso_selecionado + "_results.csv";
    ofstream outfile(nombre_archivo_salida,std::ios::app);

    double mm_total_time = 0;
    for(int j = 0; j < numero_de_experimentos; j++){ 
      
      long long single_execution_time = execution_time_ms(id_proceso_selecionado, indice_dataset, mide_solo_conteo);
      
      mm_total_time += single_execution_time;
    }
    double mm_avg_time = mm_total_time / numero_de_experimentos;

    //Para dar valores a n
    switch(atoi(argc[1]))
    {
      case 1:
      case 2:
      case 3:
      case 4:
        switch(indice_dataset)
        {
          case 1: n=200; break;
          case 2: n=400; break;
          case 3: n=600; break;
          case 4: n=800; break;
          case 5: n=1000; break;
          //n=200, 400, 600, 800, 1000
          default: n = 0; break;
        }
        break;
      case 5:
      case 6:
      case 7:
      case 8:
        switch(indice_dataset)
        {
          case 1: n=1; break;
          case 2: n=2; break;
          case 3: n=3; break;
          case 4: n=4; break;
          case 5: n=5; break;
          //n=1,2,3,4,5
          default: n = 0; break;
        }
        break;
      default: proceso_selecionado = ""; break;
    }


    outfile << n << "," << mm_avg_time <<endl;
    outfile.close(); 
    
    return 0;
  }



}
