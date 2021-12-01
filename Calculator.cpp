#include "Calculator.h"

string Calculator::reformat(string s){
    string res = "";
    bool changeOccured = false;

    for(int i = 0, j = 1; j < s.length(); i++, j++){
        // i haven't added e+/- yet
        if(s[i] == 'e') throw invalid_argument("'e' feature has not been added yet");

        // multiply from parentheses
        if(((s[i] >= '0' && s[i] <= '9') || (s[i] == ')' ) || (s[i] == '.')) && s[j] == '('){
            res += s[i];
            res += '*';
            changeOccured = true;
        }

        else res += s[i];
    }
    res += s[s.length() - 1];

    if(changeOccured) return reformat(res);
    return res;
}

string Calculator::removeTrailingZeros(string &s){
    int i;
    bool dotted = false;
    for(i = 0; i < s.length(); i++){
        if(s[i] == '.') dotted = true;
    }
    if(dotted){
        for(i = s.length() -1; i >= 0; i--){
            if(s[i] == '.') break;
            if(s[i] != '0') {
                i++;
                break;
            }
        }
        return s.substr(0, i);
    }
    return s;
}

int Calculator::findClosingP(string &s, int l, int r){
    stack<int> pStack;
    while(l < r){

        if(s[l] == '(') pStack.push(l);

        else if(s[l] == ')') pStack.pop();

        if(pStack.empty()) return l;

        l++;
    }
    throw invalid_argument("No mathcing parentheses.");
}

double Calculator::getNextNum(vector<string> v, int &i){
    bool numberFound = false;
    string curStr = "";
    while(i < v.size()){
        // number will be digit or len > 1
        if(v[i].length() > 1 || isdigit(v[i][0])){
            numberFound = true;
            curStr += v[i];
            i++;
        }
        // + - operators
        else if(v[i] == "+"){
            // number has already been found
            if(numberFound) {
                --i;
                return stod(curStr);
            }
            // no number found yet
            return getNextNum(v, ++i);
        }
        else if(v[i] == "-"){
            // number has already been found
            if(numberFound) {
                --i;
                return stod(curStr);
            }
            // no number found yet
            return -getNextNum(v, ++i);
        }
        // other operators
        else {
          --i;
          if(curStr.length() == 0) throw invalid_argument("Syntax Error");
          return stod(curStr);
        }
    }
    if(curStr.length() == 0) throw invalid_argument("Syntax Error");
    return stod(curStr);
}

/******** CALCULATE *********/
string Calculator::calculate(string s){
    s = reformat(s);
    vector<string> curVec, prevVec;
    string prevNum = "";
    string curNum = "";
    string sc;
    double n1, n2;


    // Recursive calls for parentheses
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '('){
            int len = findClosingP(s,i,s.length()) - i;
            curNum = calculate(s.substr(i+1,len-1));
            curVec.push_back(curNum);
            curNum = "";
            i += len;
        }
        else if(isdigit(s[i]) || s[i] == '.' || s[i] == 'e') {
            curNum += s[i];
            if(s[i] == 'e'){
                i++;
                curNum += s[i];
            }
            if(i == s.length()-1) {
                curVec.push_back(curNum);
            }
        }
        else {
            if(curNum.length() != 0) {
                curVec.push_back(curNum);
                curNum = "";
            }
            sc = s[i];
            curVec.push_back(sc);
        }
    }

    // Go through vec for power
    prevVec = curVec;
    curVec.clear();
    curNum = "";
    for(int i = 0; i < prevVec.size(); i++){
        // index is a number
        if(prevVec[i].length() > 1 || isdigit(prevVec[i][0])){
            curNum = prevVec[i];
        }

        // or index is a priority operator
        else if(prevVec[i] == "^"){
            // operator ^
            if(curNum.length() == 0) throw invalid_argument("Syntax Error");
            n1 = pow(stod(curNum), getNextNum(prevVec, ++i));

            curNum = to_string(n1);
        }

        // or index is non-priority operator
        else {
            // update curVec
            if(curNum.length() != 0) curVec.push_back(curNum);
            curNum = "";
            curVec.push_back(prevVec[i]);
        }
    }
    curVec.push_back(curNum);

    // Go through vec for multiply divide
    prevVec = curVec;
    curVec.clear();
    curNum = "";
    for(int i = 0; i < prevVec.size(); i++){
        // index is a number
        if(prevVec[i].length() > 1 || isdigit(prevVec[i][0])){
            curNum = prevVec[i];
        }

        // or index is a priority operator
        else if(prevVec[i] == "*" || prevVec[i] == "/"){
            // operator *
            if(curNum.length() == 0) throw invalid_argument("Syntax Error");
            if(prevVec[i] == "*") n1 = stod(curNum) * getNextNum(prevVec, ++i);
            // operator /
            else if(prevVec[i] == "/") {
              int tempI = i;
              if(curNum.length() == 0) throw invalid_argument("Syntax Error");
              if(getNextNum(prevVec, ++tempI) == 0) throw invalid_argument("Can not divide by zero");
              n1 = stod(curNum) / getNextNum(prevVec, ++i);
            }

            curNum = to_string(n1);
        }

        // or index is non-priority operator
        else {
            // update curVec
            if(curNum.length() != 0) curVec.push_back(curNum);
            curNum = "";
            curVec.push_back(prevVec[i]);
        }
    }
    curVec.push_back(curNum);

    // Go through vec for plus minus
    prevVec = curVec;
    curVec.clear();
    curNum = "0";
    for(int i = 0; i < prevVec.size(); i++){
        // index is number
        if(prevVec[i].length() > 1 || isdigit(prevVec[i][0])){
            curNum = prevVec[i];
        }

        else {
            // or index is operator +
            if(prevVec[i] == "+") n1 = stod(curNum) + getNextNum(prevVec, ++i);

            // or index is operator -
            else if(prevVec[i] == "-") n1 = stod(curNum) - getNextNum(prevVec, ++i);
            curNum = to_string(n1);
        }

    }

    return removeTrailingZeros(curNum);
};

