#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


class claseHorspool {
public:
    claseHorspool() {}

    void precalcular(const string& pattern) {

        //Crea la estructura de desplazamientos
        int m = pattern.length();
        shiftTable_.assign(256, m); //Reasigna memoria

        for (int i = 0; i < m - 1; i++) {
            shiftTable_[static_cast<unsigned char>(pattern[i])] = m - 1 - i;
            cout<<shiftTable_[static_cast<unsigned char>(pattern[i])]<<endl;
        }
    }
    

    //Cuenta cuantas veces aparece el patrón buscado en el texto
    void contar(const string& text, const string& patron) {

        int n = text.length();
        int m = patron.length();

        int i = 0;
        int count = 0;

        while (i <= n - m) {
            int j = m - 1;
            while (j >= 0 && patron[j] == text[i + j]) {
                j--;
            }

            if (j < 0) {
                count++;
                i += shiftTable_[static_cast<unsigned char>(text[i + m - 1])];
            } else {
                i += shiftTable_[static_cast<unsigned char>(text[i + m - 1])];
            }
        }
        
        cout << "Horspool: El patrón '" << patron << "' aparece " << count << " veces en el archivo." << endl;

    }

private:
    vector<int> shiftTable_;
};

