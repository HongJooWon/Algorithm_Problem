#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>

using namespace std;

//struct that include value and index of the element
struct Element {
    int value;
    int index;
};

bool compare(Element a, Element b) {
    return a.value > b.value; 
}

vector<int> getOrder(const vector<int>& arr) {
    int n = arr.size();
    
    //Element
    vector<Element> indexedArr(n);
    for (int i = 0; i < n; ++i) {
        indexedArr[i].value = arr[i];
        indexedArr[i].index = i;
    }

    //descending order
    sort(indexedArr.begin(), indexedArr.end(), compare);
    
    vector<int> result(n);
    for (int i = 0; i < n; ++i) {
        // 정렬된 배열의 인덱스를 사용하여 결과 배열에 저장
        result[indexedArr[i].index] = i + 1; // 0-based 인덱스를 1-based로 변환
    }

    return result;
}


int main() {
    //read input.txt
    ifstream fin("input.txt");

    if(!fin){
        cout << "file open Failed" << endl;
        return 0;
    }
    //read the first line as number of pairs and number of elements in each line divied by space " "
    int m, n;
    fin >> m >> n;
    //print the number of pairs and number of elements in each line
    cout << m << " " << n << endl;

    //read the rest of lines, as every two lines check whether uniform or not
    int num_rows = 0;
    int num_uniform = 0;
    //two vectors of a pair
    vector<int> row1(n);
    vector<int> row2(n);
    while (!fin.eof()) {

        //read and get_order and check whether uniform or not
        for (int i = 0; i < n; i++) {
            fin >> row1[i];
        }
        for (int i = 0; i < n; i++) {
            fin >> row2[i];
        }
        vector<int> order1 = getOrder(row1);
        vector<int> order2 = getOrder(row2);
        if (order1 == order2) {
            num_uniform++;
            cout << num_uniform << endl;
            
            cout << "1st: ";
            for (int i = 0; i < n; i++) {
                cout << row1[i] << " ";
            }
            cout << endl;
            cout << "2nd: ";
            for (int i = 0; i < n; i++) {
                cout << row2[i] << " ";
            }
            cout << endl;

            //print the order of the elements in the array
            cout << "order1: ";
            for (int i = 0; i < n; i++) {
                cout << order1[i] << " ";
            }
            cout << endl;
            cout << "order2: ";
            for (int i = 0; i < n; i++) {
                cout << order2[i] << " ";
            }
            cout << endl;
        }

        num_rows++;
        cout << endl;
    }
    
    //print the number of uniform pairs
    cout << num_uniform << endl;

    //make output.txt
    ofstream fout("output.txt");
    if (!fout) {
        cout << "file open Failed" << endl;
        return 0;
    }
    fout << num_uniform << endl;
    fout.close();
    fin.close();

    return 0;
}