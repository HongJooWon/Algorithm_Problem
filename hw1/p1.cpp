#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <array>

#define MAX_NUM 100

using namespace std;

//store sorting rules in a linked list
struct Node {
	string key; //colunm name
	int value; //whether ASC or DESC
	Node * next;
};

//multi factor compare function
bool compare(vector<string> a, vector<string> b) {

    // if (a.name == b.name) { // 이름이 같은 경우
    //     return a.age < b.age; // 나이를 비교
    // } else { // 이름이 다른 경우
    //     return a.name < b.name; // 이름을 비교
    // }
}

int main () {
    array<string, MAX_NUM> cols;//The number of rows and columns is between 1 and 100
    int col_num = 0;
    int rule_num = 0;
    string line;
    vector<vector<string>> drs;//The entire data set
    Node* head = nullptr; // Head pointer for the linked list

    //reading an input.txt file
    ifstream fin("input.txt");
    
    //exit if failed reading input.txt
    if(!fin){
        cout << "file open Failed" << endl;

        return 0;
    }

    int num_words = 0;

    //reading the first line as columns
    getline(fin, line);
    istringstream issC(line);
    string col_name;

    while (issC >> col_name && num_words < MAX_NUM) {
            col_num++;
            cols[num_words] = col_name;
            cout << col_name << "\n";
    }

    //reading the second line as sorting rules
    getline(fin, line);
    istringstream issR(line);
    string col_rule;
    while(getline(issR, col_rule, ',')){
        if(rule_num != 0){
            col_rule = col_rule.substr(1);
        }
        cout << col_rule << "\n";
        //col_rule을 또 공백으로 열과 조건을 분리하여 순서대로 linked list에 저장
        vector<string> result;
        stringstream ss(col_rule);
        string temp;

        while(getline(ss, temp, ' ')){
            result.push_back(temp);
        }

        // Create new nodes
        Node* newNode = new Node;
        newNode->key = result[0];
        if(result[1] == "ASC"){
            newNode->value = 0;
        } else {
            newNode->value = 1;
        }
        newNode->next = nullptr;

        // If list is empty, make newNode the head
        if (head == nullptr) {
            head = newNode;
        } else {
            // Find the last node and append newNode
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        
        rule_num++;
    }


    //reading data rows
    // 데이터 행을 쪼개서 벡터 배열로 받은 후, 각 요소 값을 비교할 수 있도록 만든다
    string data_row;
    while (!fin.eof()) {
        vector<string> dr;
        getline(fin, line);
        istringstream issD(line);
        while(getline(issD, data_row, ' ')){
            dr.push_back(data_row);          
        }

        drs.push_back(dr);
    }

    // vector<vector<string>>::iterator iter;
    // for(iter = drs.begin(); iter != drs.end(); iter++){
    //     cout << *iter  << '\n';
    // }

    // sort(drs.begin(), drs.end(), compare);
    Node* temp = head;
    while (temp != nullptr) {
        cout << "Column: " << temp->key << ", Order: " << temp->value << endl;
        temp = temp->next;
    }


}

//우선 정렬 조건 값이 같은 행은 따로 후순위 조건에 따라 따로 정렬하여 배치한다
//현재 값을 카운터 하는 변수를 만들어 카운트가 
//어차피 1차 정렬을 통해 첫번째 조건 정렬 완료됐으니, col탐색을 통해 중복된 값이 있는지 확인 후