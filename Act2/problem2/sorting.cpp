#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    //read input.txt
    ifstream fin("input.txt");

    if(!fin){
        cout << "file open Failed" << endl;
        return 0;
    }
    //read the first line as number of student and number of subjects divied by space " "
    int n, m;
    fin >> n >> m;
    cout << n << " " << m << endl;

    cout << "reading student data" << endl;

    //read the rest of lines, as subject number and level
    //Divide into groups based on their subject number
    int num_rows = 0;
    vector<vector<int>> data(m);
    while(!fin.eof()){
        int subject;
        int level;
        fin >> subject >> level;
        cout << subject << " " << level << endl;
        
        data[subject-1].push_back(level);
        num_rows++;
    }

    // In each group, sort the students as descending based on their skill levels
    for(int i = 0; i < m; i++){
        sort(data[i].begin(), data[i].end(), greater<int>());
    }

    //print the data
    for(int i = 0; i < m; i++){
        cout << "rows: ";
        for(int j = 0; j < data[i].size(); j++){
            cout << data[i][j] << " ";
        }
        cout << endl;
    }

    //더했을 때 가장 큰 값이 나오는 조합을 찾아라
    //input에 마이너스 값이 있을 수 있음
    
    //find the largest sized group
    int max_size = 0;
    for (int i = 0; i < m; i++) {
        if (data[i].size() > max_size) {
            max_size = data[i].size();
        }
    }

    cout << "max_size: " << max_size << endl;

    //원소의 수가 가장 큰 그룹의 사이즈를 기준으로 iteration을 했을 때, 
    //각 iteration마다 각 그룹의 i번째 원소까지의 합을 구하고 다른 그룹의 합 값을 비교하여 가장 큰 두 값을 저장한다
    vector < vector <int> > sums(m,vector <int>(max_size, 0));
    for(int i = 0; i < max_size; i++){
        for(int j = 0; j < m; j++){
            if(i < data[j].size()){
                if(i == 0){
                    sums[j][i] = data[j][i];
                }
                else{
                    sums[j][i] = sums[j][i-1] + data[j][i];
                }
            }
            else{
                continue;
            }

        }
    }

    //print the sums
    for(int i = 0; i < m; i++){
        for(int j = 0; j < max_size; j++){
            cout << sums[i][j] << " ";
        }
        cout << endl;
    }

    //각 column마다 두 개의 행을 선택하여 더한 값 중 가장 큰 값을 찾는다
    int max_sum = 0;
    for(int i = 0; i < max_size; i++){
        for(int j = 0; j < m; j++){
            for(int k = j+1; k < m; k++){
                int temp_sum = sums[j][i] + sums[k][i];
                //if temp_sum < 0, then temp_sum = -1
                if(temp_sum < 0){
                    temp_sum = -1;
                    continue;
                }
                if(temp_sum > max_sum){
                    max_sum = temp_sum;
                }
            }
        }
    }

    cout << "max_sum: " << max_sum << endl;

    //make output.txt
    ofstream fout("output.txt");
    if (!fout) {
        cout << "file open Failed" << endl;
        return 0;
    }
    fout << max_sum << endl;

    return 0;
}