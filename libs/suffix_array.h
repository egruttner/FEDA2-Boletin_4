#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Estructura para almacenar los sufijos y sus índices originales
struct Suffix {
    string suffix;
    int index;
};

//Función de comparación custom
bool compareSuffix(const Suffix &a, const Suffix &b) {
    return a.suffix < b.suffix;
}

class claseSuffixArray {
public:
    claseSuffixArray() {}

    void precalcular(const string &text) {
        suffixArray_.clear();
        for (int i = 0; i < text.length(); i++) {
            Suffix suffix;
            suffix.suffix = text.substr(i);
            suffix.index = i;
            suffixArray_.push_back(suffix);
        }

        // Ordenar el vector de sufijos lexicográficamente
        sort(suffixArray_.begin(), suffixArray_.end(), compareSuffix);
    }

    void contar(const string &text, const string &pattern) {
        int left = 0;
        int right = suffixArray_.size() - 1;
        int count = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int cmp = pattern.compare(0, pattern.length(), suffixArray_[mid].suffix, 0, pattern.length());

            if (cmp == 0) {
                count++;
                // Buscar más ocurrencias del patrón en la izquierda
                int i = mid - 1;
                while (i >= 0 && pattern.compare(0, pattern.length(), suffixArray_[i].suffix, 0, pattern.length()) == 0) {
                    count++;
                    i--;
                }
                // Buscar más ocurrencias del patrón en la derecha
                i = mid + 1;
                while (i < suffixArray_.size() && pattern.compare(0, pattern.length(), suffixArray_[i].suffix, 0, pattern.length()) == 0) {
                    count++;
                    i++;
                }
                break;
            } else if (cmp < 0) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        cout << "SuffixArray: El patrón '" << pattern << "' aparece " << count << " veces en el archivo." << endl;

    }

private:
    vector<Suffix> suffixArray_;
};

