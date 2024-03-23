#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <array>
#include <tuple>

#define MAX_NUM 100

using namespace std;

//store sorting rules in a linked list
struct Node {
	string key; //colunm name
	int value; //0 == ASC else 1 == DESC
    int col_key; //location of column element in the column array
	Node * next;
};

//multi factor compare function
// linked list의 
bool compare(const vector<string>& a, const vector<string>& b, int col_num) {

}

vector<vector<string>> merge(const vector<vector<string>>& left, const vector<vector<string>>& right, Node* sorting_rules) {
    vector<vector<string>> result;

    cout << "merging" << endl;

    size_t i = 0, j = 0;

    while (i < left.size() && j < right.size()) {
        vector<string> row1 = left[i];
        vector<string> row2 = right[j];
        bool swap_needed = false;
        Node* temp = sorting_rules;
        
        // Check sorting rules one by one
        while (temp != nullptr) {
            int col_index = temp->col_key;
            cout << "sorting" << endl;
            cout << temp->key << endl;
             cout << temp->col_key << endl; //인덱스 값이 이상함
            // Compare columns based on sorting order
            if (row1[col_index] != row2[col_index]) {
                if (temp->value == 0) {
                    swap_needed = row1[col_index] > row2[col_index]; // ASC
                } else {
                    swap_needed = row1[col_index] < row2[col_index]; // DESC
                }
                break;
            }
            
            // Move to the next sorting rule
            temp = temp->next;
        }

        if (swap_needed) {
            result.push_back(row2);
            j++;
        } else {
            result.push_back(row1);
            i++;
        }
    }

    // Append remaining elements
    while (i < left.size()) {
        result.push_back(left[i]);
        i++;
    }

    while (j < right.size()) {
        result.push_back(right[j]);
        j++;
    }

    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << endl; // 각 행이 끝날 때마다 개행
    }

    return result;
}

// Merge sort implementation
vector<vector<string>> merge_sort(vector<vector<string>>& data, Node* sorting_rules) {
    if (data.size() <= 1){
        return data;
    }
    cout << data.size() << endl;
    size_t middle = data.size() / 2;
    vector<vector<string>> left(data.begin(), data.begin() + middle);
    vector<vector<string>> right(data.begin() + middle, data.end());

    left = merge_sort(left, sorting_rules);
    right = merge_sort(right, sorting_rules);

    return merge(left, right, sorting_rules);
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
        cout << "rule: " <<col_rule << "\n";
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

        cout << "node key : " << newNode->key << endl;
        
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

    for (int i = 0; i < drs.size(); i++) {
        for (int j = 0; j < drs[i].size(); j++) {
            cout << drs[i][j] << " ";
        }
        cout << endl; // 각 행이 끝날 때마다 개행
    }

    // vector<vector<string>>::iterator iter;

    // sort(drs.begin(), drs.end(), compare);

    //find which columns to sort and store the index
    Node* node_itr = head;
    vector<int> sorted_col;
    while (node_itr != nullptr) {
        cout << "Column: " << node_itr->key << ", Order: " << node_itr->value << endl;
        for(int i = 0; i<col_num; i++){
            if(cols[i] == node_itr->key){
                cout << node_itr->key << endl;
                node_itr->col_key = i;
                cout << node_itr->col_key << endl;
            }
        }
        node_itr = node_itr->next;
    }

    //병합정렬로
    // Sort data rows using merge sort based on sorting rules
    drs = merge_sort(drs, head);

    //Print sorted data rows
    vector<vector<string>>::iterator iter;

    for (int i = 0; i < drs.size(); i++) {
        for (int j = 0; j < drs[i].size(); j++) {
            cout << drs[i][j] << " ";
        }
        cout << endl; // 각 행이 끝날 때마다 개행
    }
}

//우선 정렬 조건 값이 같은 행은 따로 후순위 조건에 따라 따로 정렬하여 배치한다
//현재 값을 카운터 하는 변수를 만들어 카운트가 
//어차피 1차 정렬을 통해 첫번째 조건 정렬 완료됐으니, col탐색을 통해 중복된 값이 있는지 확인 후