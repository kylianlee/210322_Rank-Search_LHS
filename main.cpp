#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <string>

using namespace std;

vector<int> solution(vector<string> info, vector<string> query);
vector<string> split(string input, char delimiter);
pair<int, int> calcApplicantInfo(vector<string> input);
pair<pair<int, int>, int> calcQueryCondition(vector<string> input);

const int cpp = 1;
const int java = 2;
const int python = 4;
const int backend = 8;
const int frontend = 16;
const int junior = 32;
const int senior = 64;
const int chicken = 128;
const int pizza = 256;

int main() {
    vector<string> info = {"java backend junior pizza 150","python frontend senior chicken 210","python frontend senior chicken 150","cpp backend senior pizza 260","java backend junior chicken 80","python backend senior chicken 50"};
    vector<string> query = {"java and backend and junior and pizza 100","python and frontend and senior and chicken 200","cpp and - and senior and pizza 250","- and backend and senior and - 150","- and - and - and chicken 100","- and - and - and - 150"};
    vector<int> answer;

    answer = solution(info, query);

    for(int i = 0; i < answer.size(); i++){
        cout << answer[i] << endl;
    }


    return 0;
}

vector<int> solution (vector<string> info, vector<string> query){
    vector<int> answer(query.size());
    vector<pair<int, int>> applicantInfo;
    pair<pair<int, int>, int> queryCondition;
    vector<string> input;
    int infoSize = info.size(), querySize = query.size();

    for(int i = 0; i < infoSize; i++){
        input = split(info[i], ' ');
        applicantInfo.push_back(calcApplicantInfo(input));
        input.clear();
        cout << "applicantInfo[" << i << "] : " << applicantInfo[i].first << " , " << applicantInfo[i].second << endl;
    }

    for(int i = 0; i < querySize; i++){
        input = split(query[i], ' ');
        queryCondition = calcQueryCondition(input);


        cout << "queryCondition : <" << queryCondition.first.first << " , " << queryCondition.first.second << "> , " << queryCondition.second << ">" << endl;

        for(int j = 0; j < infoSize; j++){
            if(applicantInfo[j].second >= queryCondition.first.second){
                if(queryCondition.second == 1)
                    if((applicantInfo[j].first & queryCondition.first.first) == queryCondition.first.first)
                        answer[i]++;
                    else
                        continue;
                else
                if(applicantInfo[j].first == queryCondition.first.first)
                    answer[i]++;
                else
                    continue;
            }
            else continue;
        }
        input.clear();
    }

    return answer;
}

vector<string> split(string input, char delimiter) {
    vector<string> answer;
    stringstream ss(input);
    string temp;

    while (getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }

    return answer;
}

pair<int, int> calcApplicantInfo(vector<string> input){
    pair<int, int> p;
    string language = input[0];
    string occupation = input[1];
    string career = input[2];
    string soulFood = input[3];

    p.first = 0;
    p.second = 0;

    if(language == "cpp")
        p.first += cpp;
    else if(language == "java")
        p.first += java;
    else
        p.first += python;

    if(occupation == "backend")
        p.first += backend;
    else
        p.first += frontend;

    if(career == "junior")
        p.first += junior;
    else
        p.first += senior;

    if(soulFood == "chicken")
        p.first += chicken;
    else
        p.first += pizza;

    p.second = stoi(input[4]);

    return p;
}

pair<pair<int, int>, int> calcQueryCondition(vector<string> input){
    pair<pair<int, int>, int> p;
    string language = input[0];
    string occupation = input[2];
    string career = input[4];
    string soulFood = input[6];

    p.first.first = 0;
    p.first.second = 0;
    p.second = 0;

    if(language == "cpp")
        p.first.first += cpp;
    else if(language == "java")
        p.first.first += java;
    else if(language == "python")
        p.first.first += python;
    else p.second = 1;

    if(occupation == "backend")
        p.first.first += backend;
    else if(occupation == "-")
        p.second = 1;
    else
        p.first.first += frontend;

    if(career == "junior")
        p.first.first += junior;
    else if(career == "-")
        p.second = 1;
    else
        p.first.first += senior;

    if(soulFood == "chicken")
        p.first.first += chicken;
    else if(soulFood == "-")
        p.second = 1;
    else
        p.first.first += pizza;

    if(input[7] == "-")
        p.second = 1;
    else
        p.first.second = stoi(input[7]);

    return p;
}
