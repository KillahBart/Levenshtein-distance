#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;


int LevenshteinDistance(const string &source, const string &target) {
    if (source.size() > target.size()) {
        return LevenshteinDistance(target, source);
    }

    const int min_size = (int)source.size();
    const int max_size = (int)target.size();
    
    vector<int> lev_dist(min_size + 1);

    for (int i = 0; i <= min_size; ++i) {
        lev_dist[i] = i;
    }

    for (int j = 1; j <= max_size; ++j) {
        int previous_diagonal = lev_dist[0], previous_diagonal_save;
        ++lev_dist[0];

        for (int i = 1; i <= min_size; ++i) {
            previous_diagonal_save = lev_dist[i];
            if (source[i - 1] == target[j - 1]) {
                lev_dist[i] = previous_diagonal;
            } else {
                lev_dist[i] = min(min(lev_dist[i - 1], lev_dist[i]), previous_diagonal) + 1;
            }
            previous_diagonal = previous_diagonal_save;
        }
    }

    return lev_dist[min_size];
}



void Podobienstwo(int lev){
    int b_podobny;
    int podobny;

    cout << " \n ==== Wpisz ile maksymelnie roznic moga miec zdania aby można było by ich nazwać baradzo podobnymi: ";
    cin >> b_podobny;
    cout << " \n ==== Wpisz ile maksymelnie roznic moga miec zdania aby można było by ich nazwać podobnymi: ";
    cin >> podobny;
    cout << "\n";

    if(lev < b_podobny ){
        cout << "Zdanie w pliku 1 jest bardzo podobne do zdania w pliku 2" << endl;
    }
    else if(lev < podobny){
        cout << "Zdanie w pliku 1 jest podobne do zdania w pliku 2" << endl;
    }
    else {
        cout << "Zdanie w pliku 1 nie jest podobne do zdania w pliku 2" << endl;
    }
}


int main() {
    
    string str1, str2;
    string path1;
    string path2;
    
    
    cout << "Wprowadz sciezke do pliku 1:" << endl;
    cin >> path1;
    cout << "Wprowadz sciezke do pliku 2:" << endl;
    cin >> path2;
    
    
    ifstream fsource1, fsource2;
    fsource1.open(path1);
    fsource2.open(path2);

    if(fsource1.is_open()){

        string temp;
        while(!fsource1.eof()){
            fsource1 >> temp;
            str1 += " " + temp;
        }

    }
    else {
        cout << "Blednie podany path do pliku 1" << endl;
    }
    
    if(fsource2.is_open()){

        string temp;
        while(!fsource2.eof()){
            fsource2 >> temp;
            str2 += " " + temp;
        }
    }
    else {
        cout << "Blednie podany path do pliku 2" << endl;
    }
    
    if(!fsource1.is_open() || !fsource2.is_open()){
        cout << "Sprawdz, czy sciezka jest poprawna i sprobuj ponownie" << endl;
    }

    else {

        
    int lev = LevenshteinDistance(str1, str2);
    Podobienstwo(lev);
    
    
    cout << "Wedlog algorytmu Levenshteina podobienstwo slow jest rowne : " << lev << endl;
    }
    
   
    
    return 0;
}
