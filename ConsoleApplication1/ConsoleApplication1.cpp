#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

// Функция для определения приоритета операторов
int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Функция для выполнения операций
double applyOperator(char op, double a, double b) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        // Проверяем деление на ноль
        if (b != 0) {
            return a / b;
        }
        else {
            // Выводим ошибку и завершаем программу
            cout << "Ошибка: Деление на ноль." << endl;
            exit(1);
        }

    default:
        // Выводим ошибку и завершаем программу
        cout << "Ошибка: Неизвестный оператор." << endl;
        exit(1);
    }
}

int main() {
    // Устанавливаем локаль для корректного отображения кириллицы
    setlocale(LC_ALL, "RUS");

    do {
        string expression;
        cout << "Введите арифметическое выражение: ";
        cin >> expression;

        stack<char> operators;
        stack<double> operands;

        // Итерируем по символам в выражении
        for (char c : expression) {
            // Пропускаем пробелы
            if (isspace(c)) {
                continue;
            }

            // Если символ - цифра, добавляем число в стек операндов
            if (isdigit(c)) {
                operands.push(c - '0');
            }
            // Если символ - открывающая скобка, добавляем ее в стек операторов
            else if (c == '(') {
                operators.push(c);
            }
            // Если символ - закрывающая скобка
            else if (c == ')') {
                // Выполняем операции до открывающей скобки
                while (!operators.empty() && operators.top() != '(') {
                    char op = operators.top();
                    operators.pop();

                    double b = operands.top();
                    operands.pop();
                    double a = operands.top();
                    operands.pop();

                    // Выполняем операцию и добавляем результат в стек операндов
                    operands.push(applyOperator(op, a, b));
                }
                // Удаляем открывающую скобку из стека операторов
                if (!operators.empty()) {
                    operators.pop();
                }
                else {
                    // Выводим ошибку и завершаем программу
                    cout << "Ошибка: Несбалансированные скобки." << endl;
                    exit(1);
                }
            }
            // Если символ - оператор +, -, *, /
            else if (c == '+' || c == '-' || c == '*' || c == '/') {
                // Выполняем операции с операторами в стеке, имеющими более высокий или равный приоритет
                while (!operators.empty() && operators.top() != '(' &&
                    getPriority(operators.top()) >= getPriority(c)) {
                    char op = operators.top();
                    operators.pop();

                    double b = operands.top();
                    operands.pop();
                    double a = operands.top();
                    operands.pop();

                    // Выполняем операцию и добавляем результат в стек операндов
                    operands.push(applyOperator(op, a, b));
                }
                // Добавляем текущий оператор в стек операторов
                operators.push(c);
            }
            // Если символ - недопустимый символ
            else {
                // Выводим ошибку и завершаем программу
                cout << "Ошибка: Недопустимый символ в выражении." << endl;
                exit(1);
            }
        }

        // Выполняем оставшиеся операции в стеке операторов
        while (!operators.empty()) {
            char op = operators.top();
            operators.pop();

            double b = operands.top();
            operands.pop();
            double a = operands.top();
            operands.pop();

            // Выполняем операцию и добавляем результат в стек операндов
            operands.push(applyOperator(op, a, b));
        }

        // Если в стеке операндов остался один элемент, выводим результат
        if (operands.size() == 1) {
            cout << "Результат: " << operands.top() << endl;
        }
        // Иначе выводим сообщение об ошибке
        else {
            cout << "Ошибка: Некорректное выражение." << endl;
            exit(1);
        }
        
        // Тут идет проверка на завершении работу либо продолжить вычисление 
        int choice;
        cout << "Введите 1 для нового вычисления или 2 для завершения: ";
        cin >> choice;

        // Проверяем выбор пользователя
        if (choice == 2) {
            break;  // Завершаем цикл, если выбрано завершение
        }

    } while (true);  // Повторяем цикл для нового вычисления

    return 0;
}
