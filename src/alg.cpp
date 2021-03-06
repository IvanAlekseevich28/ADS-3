#include <iostream>
#include "tstack.h"


using namespace std;


int getPriority(char ch) {
    switch (ch) {
    case '(': return 0;
    case ')': return 1;
    case '+': return 2;
    case '-': return 2;
    case '*': return 3;
    case '/': return 3;
    default: return -1;
    }
}


string infx2pstfx(string inf) {
    TStack<char> stack;
    string answer;

    for (char ch : inf) {
        int priority = getPriority(ch);

        if ( priority == -1)
            answer.append(string(1,ch));
        else
            if( stack.isEmpty() or priority == 0 or priority > getPriority(stack.get()) )
                stack.push(ch);
            else {
                if ( ch == ')')
                    while(true) {
                        char lastStackElement = stack.get();
                        stack.pop();
                        if (lastStackElement != '(')
                            answer.append(string(1,lastStackElement));
                        else
                            break;
                    } else {
                    while(!stack.isEmpty()) {
                        char lastStackElement = stack.get();
                        stack.pop();
                        if (getPriority(lastStackElement) >= priority)
                            answer.append(string(1,lastStackElement));
                    }
                    stack.push(ch);
                }
            }
    }
    while(!stack.isEmpty()) {
        char lastStackElement = stack.get();
        stack.pop();
        answer.append(string(1,lastStackElement));
  }
    return answer;
}


int calculate(int number1, int number2, char operation) {
    switch (operation) {
    case '+': return number1 + number2;
    case '-': return number1 - number2;
    case '*': return number1 * number2;
    case '/': return number1 / number2;
    default: return -1;
    }
}


int eval(string pst) {
    TStack<int> stack;
    for (char ch : pst) {
        int priority = getPriority(ch);

        if ( priority == -1)
            stack.push(ch - 48);
        else {
            int  number1=stack.get();
            stack.pop();

            int number2 = stack.get();
            stack.pop();

            int result = calculate(number2, number1, ch);
            stack.push(result);
        }

    }
    return stack.get();
}
