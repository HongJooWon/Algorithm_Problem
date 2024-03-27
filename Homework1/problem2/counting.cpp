#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


//function to search from the left and right edge of the vector
//



int main() {
    
    //reading an input.txt file
    ifstream fin("input.txt");
    
    //exit if failed reading input.txt
    if(!fin){
        cout << "file open Failed" << endl;

        return 0;
    }

    //read the first line as the length of the line
    string firstLine;
    getline(fin, firstLine); // read the first line from the file
    int length = stoi(firstLine); // convert the string to an integer
    cout << length << endl;

    //read the second line from the file and store each letter in the vector
    string secondLine;
    getline(fin, secondLine); // read the second line from the file
    vector<char> facing(secondLine.begin(), secondLine.end()); // store each letter in the vector
    for (int i = 0; i < length; i++) {
        cout << facing[i] << " ";
    }

    cout << endl;


    //if the element is L, count the number of other elements that are located in the left side of the element
    //if the element is R, count the number of other elements that are located in the right side of the element
    
    vector <int> values(length, 0);
    bool left_side = true;
    int location = 0;
    //iteratate facing vector
    for (int i = 0; i < length; i++) {
        int num_people = 0;
        for (int k = 0; k < length; k++) {
            cout << facing[k] << " ";
            if(facing[k] == 'L') {
                num_people += k;
            } else if (facing[k] == 'R') {
                num_people += length - k - 1;
            }
        }
        
        values[i] = num_people;

        cout << endl;

        cout << "location: " << location << endl;

        if (left_side==true) {
            if(facing[location] == 'L') {
                facing[location] = 'R';
            }
            left_side = false;
            location++;
        } else if(left_side==false) {
            if(facing[length-location] == 'R') {
                facing[length-location] = 'L';
            }
            left_side = true;
        }
    }

    //make "output.txt" file including values
    ofstream fout("output.txt");
    if (!fout) {
        cout << "file open Failed" << endl;
        return 0;
    }

    for (int i = 0; i < length; i++) {
        cout << "output: " << values[i] << " ";
        fout << values[i] << " ";
    }

    return 0;



}