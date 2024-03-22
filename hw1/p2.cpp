#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <array>
#include <vector>

#define MAX_NUM 100

using namespace std;

struct Row {
    array<string, MAX_NUM> values;

    // 비교 함수를 작성합니다.
    static bool compare(const Row& a, const Row& b, const vector<string>& col_rules) {
        for (const auto& rule : col_rules) {
            // 각 규칙에 따라 열을 비교합니다.
            // 여기서는 간단히 문자열 비교를 사용합니다.
            int col_index = stoi(rule) - 1; // 규칙은 1부터 시작하지만 배열 인덱스는 0부터 시작합니다.
            if (a.values[col_index] != b.values[col_index]) {
                return a.values[col_index] < b.values[col_index];
            }
        }
        return false; // 모든 열에 대해 동일한 경우 정렬 순서를 변경하지 않습니다.
    }
};

int main() {
    // 파일에서 데이터를 읽어와 저장할 벡터를 선언합니다.
    vector<Row> rows;
    
    // 열의 정렬 규칙을 저장할 벡터를 선언합니다.
    vector<string> col_rules;

    string line;
    ifstream fin("input.txt");
    
    if (!fin) {
        cout << "file open Failed" << endl;
        return 0;
    }

    // 첫 번째 줄은 열의 이름입니다.
    getline(fin, line);
    istringstream issC(line);
    string col_name;
    while (issC >> col_name && col_rules.size() < MAX_NUM) {
        col_rules.push_back(col_name);
        cout << col_name << "\n";
    }

    // 두 번째 줄은 정렬 규칙입니다.
    getline(fin, line);
    istringstream issR(line);
    string col_rule;
    while (getline(issR, col_rule, ',')) {
        col_rules.push_back(col_rule);
        cout << col_rule << "\n";
    }

    // 나머지 줄은 데이터 행입니다.
    while (getline(fin, line)) {
        istringstream issD(line);
        Row row;
        string value;
        int index = 0;
        while (issD >> value && index < MAX_NUM) {
            row.values[index++] = value;
        }
        rows.push_back(row);
    }

    // 데이터를 정렬합니다.
    sort(rows.begin(), rows.end(), [&col_rules](const Row& a, const Row& b) {
        return Row::compare(a, b, col_rules);
    });

    // 정렬된 결과를 출력합니다.
    for (const auto& row : rows) {
        for (const auto& value : row.values) {
            cout << value << " ";
        }
        cout << endl;
    }

    return 0;
}
