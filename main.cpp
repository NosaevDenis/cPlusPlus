//
//  main.cpp
//  calc
//
//  Created by Денис on 15.02.15.
//  Copyright (c) 2015 Денис. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <vector>
#include <stdlib.h>



using namespace std;

void calculation ( string expression ) {

    vector<string>RPN_expression (1); //Reverse Polish notation

    string texas;

    int i = 0;

    int g = 0;

    while (i < expression.length()) {

        if ((expression[i] >= 48) && (expression[i] <= 57)) {

                RPN_expression[g].push_back (expression[i]);

                i++;

        }

        else

            if (expression[i] == '+') {

                if ((texas.length() == 0) || (texas[texas.length() - 1] == '(')) {

                    texas.push_back (expression[i]);

                    i++;

                    g++;

                    RPN_expression.push_back ("");

                }

                else  {

                    g++;

                    RPN_expression.push_back("");

                        RPN_expression[g].push_back (texas[texas.length() - 1]);

                        g++;

                    RPN_expression.push_back ("");

                    texas.pop_back();

                }

                }

            else

                if (expression[i] == '-') {

                    if ((texas.length() == 0) || (texas[texas.length() - 1] == '(')) {

                        texas.push_back (expression[i]);

                        i++;

                        g++;

                        RPN_expression.push_back ("");

                    }

                    else {

                        g++;

                        RPN_expression.push_back ("");

                        RPN_expression.push_back ("");

                        RPN_expression[g].push_back (texas[texas.length() - 1]);

                        g++;

                        RPN_expression.push_back ("");

                        texas.pop_back();}

                    }

                else

                    if (expression[i] == '*') {

                        if ((texas[texas.length() - 1] == '+') || (texas[texas.length() - 1] == '-') ||
                                (texas[texas.length() - 1] == '(') || (texas.length() == 0)) {

                            texas.push_back (expression[i]);

                            i++;

                            g++;

                            RPN_expression.push_back ("");

                        }

                        else {

                            g++;

                            RPN_expression.push_back ("");

                            RPN_expression[g].push_back (texas[texas.length() - 1]);

                            g++;

                            RPN_expression.push_back ("");

                            texas.pop_back();

                        }

                        }

                    else

                        if (expression[i] == '/') {

                            if ((texas[texas.length() - 1] == '+') || (texas[texas.length() - 1] == '-') || (texas[texas.length() - 1] == '(') || (texas.length() == 0)) {

                                texas.push_back (expression[i]);

                                i++;

                                g++;

                                RPN_expression.push_back ("");

                            }

                            else {

                                g++;

                                RPN_expression.push_back ("");

                                RPN_expression[g].push_back (texas[texas.length() - 1]);

                                g++;

                                RPN_expression.push_back ("");

                                texas.pop_back();

                            }

                            }

                        else

                            if (expression[i] == '%') {

                                if ((texas[texas.length() - 1] == '+') || (texas[texas.length() - 1] == '-') || (texas[texas.length() - 1] == '(') || (texas.length() == 0)) {

                                    texas.push_back (expression[i]);

                                    i++;

                                    g++;

                                    RPN_expression.push_back ("");

                                }

                                else {

                                    g++;

                                    RPN_expression.push_back ("");

                                    RPN_expression[g].push_back (texas[texas.length() - 1]);

                                    g++;

                                    RPN_expression.push_back ("");

                                    texas.pop_back();
                                }

                                }



                            else

                                if (expression[i] == '(') {

                                    texas.push_back (expression[i]);

                                    i++;

                                }

                                else

                                    if (expression[i] == ')') {

                                        if (texas[texas.length() - 1] == '(') {

                                            texas.pop_back();

                                            i++;

                                        }

                                        else {

                                            g++;

                                            RPN_expression.push_back ("");

                                            RPN_expression[g].push_back (texas[texas.length() - 1]);

                                            g++;

                                            RPN_expression.push_back ("");

                                            texas.pop_back();

                                        }

                                        }

    }

    while (texas.length() > 0) {

            g++;

        RPN_expression.push_back ("");

        RPN_expression[g].push_back (texas[texas.length() - 1]);

        g++;

        RPN_expression.push_back ("");

        texas.pop_back();

    }

    for (g = 0; g < RPN_expression.size(); g++)

        if (RPN_expression[g].size() == 0) {

            RPN_expression.erase(RPN_expression.begin() + g);

        }

    int lk = RPN_expression.size();

    vector <int> stek(0);

    for (g = 0; g < RPN_expression.size(); g++) {

        if (RPN_expression[g] == "") {

        }

        else

            if (RPN_expression[g] == "+") {

                int res = stek[stek.size() - 2] + stek[stek.size() - 1];

                stek.pop_back();

                stek[stek.size() - 1] = res;

                }

            else

                if (RPN_expression[g] == "*") {

                    int res = stek[stek.size() - 2] * stek[stek.size() - 1];

                    stek.pop_back();

                    stek[stek.size() - 1] = res;

                    }

                else

                    if (RPN_expression[g] == "/") {

                        if (stek[stek.size()-1] == 0) {

                            cout << "division by zero";

                            stek.clear();

                            break;

                        }

                                else {

                                int res = stek[stek.size() - 2] / stek[stek.size() - 1];

                                stek.pop_back();

                                stek[stek.size() - 1] = res;

                            }

                        }

                    else

                        if (RPN_expression[g] == "%")

                            {

                            int res = stek[stek.size() - 2] / stek[stek.size() - 1];

                            stek.pop_back();

                                stek[stek.size()-1] = res;

                            }

                        else

                            if (RPN_expression[g] == "-") {

                                int res = stek[stek.size() - 2] - stek[stek.size() - 1];

                                stek.pop_back();

                                stek[stek.size() - 1] = res;

                                }

                            else {

                                stek.push_back ( stoi (RPN_expression[g]));

                            }

        }

    if (stek.size() > 0) {


        cout << stek[0];

    }

}
string proceesing (string s) {

    string expression;

    int balance = 0;

    for (int i = 0; i < s.length(); i++) {

        if ((s[i] >= 48) && (s[i] <= 57)) {

            expression.push_back(s[i]);
        }

        else

            if (s[i] == '(') {

                expression.push_back (s[i]);

                balance++;
            }

            else

                if (s[i] == ')') {

                    expression.push_back (s[i]);

                    balance--;
                }
                else

                    if ((s[i] == '+') || (s[i] == '-') || (s[i] == '/') || (s[i] == '*') || (s[i] == '%')) {

                        expression.push_back (s[i]);

                    }

                    else

                        if (s[i] == ' ') {

                        }

                        else {

                            cout << "wrong symbol";

                            expression = "stop";

                            break;

                            }
        }

    if (balance != 0) {

        cout << "wrong brackets";

        expression = "stop";

        }

    return expression;
}




int main() {

    string s;

    std::getline ( std::cin, s );

    string expression = proceesing(s);

    if (expression == "stop") {

    }

    else

        calculation(expression);


    return 0;
}
