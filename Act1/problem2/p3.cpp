#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int maxRowValue(int length, vector<char>& facing, int k) {
    int maxVal = 0;
    int currVal = 0;
    int num_change = 0;
    int order = 0;
    
    for (int i = 0; i < length; i++) {
        if (order < length / 2) {
            if (facing[i] == 'L') {
                currVal++;
            } else {
                currVal--;
                num_change++;
                if (num_change > k) {
                    currVal++;
                    num_change--;
                }
            }
        } else {
            if (facing[i] == 'R') {
                currVal++;
            } else {
                currVal--;
                num_change++;
                if (num_change > k) {
                    currVal++;
                    num_change--;
                }
            }
        }
        
        maxVal = max(maxVal, currVal);
        order += currVal;
    }
    
    return maxVal;
}

vector<int> maxRowValues(int length, vector<char>& facing) {
        vector<int> maxValues(length, 0);
        
        for (int k = 1; k <= length; k++) {
            vector<int> values(length, 0);
            bool left_side = true;
            int num_change = 0;
            int order = 0;
            
            for (int i = 0; i < length; i++) {
                if (order < length / 2) {
                    if (facing[i] == 'L') {
                        values[i] = 1;
                    } else {
                        values[i] = -1;
                        num_change++;
                        if (num_change > k) {
                            values[i] = 1;
                            num_change--;
                        }
                    }
                } else {
                    if (facing[i] == 'R') {
                        values[i] = 1;
                    } else {
                        values[i] = -1;
                        num_change++;
                        if (num_change > k) {
                            values[i] = 1;
                            num_change--;
                        }
                    }
                }
                
                order += values[i];
            }
            
            int maxVal = 0;
            int currVal = 0;
            for (int i = 0; i < length; i++) {
                currVal += values[i];
                maxVal = max(maxVal, currVal);
            }
            
            maxValues[k - 1] = maxVal;
        }
        
        return maxValues;
    }

    int main() {
        ifstream fin("input.txt");
        if (!fin) {
            cout << "file open Failed" << endl;
            return 0;
        }
        
        string firstLine;
        getline(fin, firstLine);
        int length = stoi(firstLine);
        
        string secondLine;
        getline(fin, secondLine);
        vector<char> facing(secondLine.begin(), secondLine.end());
        
        vector<int> maxValues = maxRowValues(length, facing);
        
        ofstream fout("output.txt");
        for (int i = 0; i < length; i++) {
            fout << maxValues[i] << " ";
        }
        fout.close();
        
        return 0;
    }
