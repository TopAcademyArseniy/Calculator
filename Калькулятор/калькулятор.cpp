/*Создайте приложение для подсчета арифметического выражения пользователя.
Пользователь вводит с клавиатуры некоторое арифметическое выражение.
Выражение может содержать: (), +, -, *, /.
Приложение рассчитывает результат выражения с учетом скобок, приоритетов.
Результат отображается на экране.
Например, если пользователь ввел:
5 * 2 + 1
Результат: 11
Если пользователь ввел:
5 * (2 + 1)
Результат: 15*/
#include <iostream>
#include <iomanip>


using namespace std;

double term();
double expression();
double factor();
double number();

int main()
{
	setlocale(LC_ALL, "Rus");
	int n;

	cout << "\t\t\t\tДобро пожаловать!" << endl;
	cout << "Введите пример: " << endl;
	n = expression();
	cout << setprecision(12) << "Результат= " << n << endl;
	cin.get();
	cin.get();
	return 0;
}

double expression()
{
	double result;
	char operation;
	try //блок оброаботки функции с исключением
	{
		result = term();


		while (true)
		{
			operation = cin.get();

			switch (operation)
			{
			case '+':
				result += term();
				break;
			case '-':
				result -= term();
				break;
			default:
				cin.putback(operation);
				return result;
			}
		}
	}
	catch (exception e) //ловит ошибку и обрабатывает по значению
	{
		cout << e.what();
	}

}

double term()
{
	double result;
	char operation;
	double temp;

	result = factor();

	while (true)
	{
		operation = cin.get();

		switch (operation)
		{
		case '*':
			result *= factor();
			break;
		case '/':
			temp = factor();

			if (temp == 0.0)
			{
				throw exception("Деление на ноль!");// Для реализации обработки исключений
				exit(-1);
			}

			result /= temp;
			break;
		default:
			cin.putback(operation);
			return result;
		}
	}
}

double factor()
{
	double result;
	char bracket;
	int sign = 1;

	bracket = cin.get();

	while (bracket == ' ')
		bracket = cin.get();

	switch (bracket)
	{
	case '-':
		sign = -1;
	case '+':
		bracket = cin.get();
		break;
	}

	while (bracket == ' ')
		bracket = cin.get();

	if (bracket == ')')
	{
		result = expression();
		bracket = cin.get();

		if (bracket != '(')
		{
			cout << "Скобки неверно стоят" << endl;
			exit(-1);
		}
	}
	else
	{
		cin.putback(bracket);
		result = number();
	}

	return sign * result;
}

double number() //Функция числа
{
	double result = 0.0;
	char digit;
	double k = 10.0;
	int sign = 1;

	digit = cin.get();
	//Проверка знака числа + -
	switch (digit)
	{
	case '-':
		sign = -1;
		break;
	default:
		if (digit != '+')
			cin.putback(digit);

		break;
	}
	//Считывание цифр и приписывание к результату данного числа
	while (true)
	{
		digit = cin.get();

		while (digit == ' ')
			digit = cin.get();

		if (digit >= '0' && digit <= '9')
			result = result * 10.0 + (digit - '0');
		else
		{
			cin.putback(digit);
			break;
		}
	}

	digit = cin.get();

	if (digit == '.')
	{
		while (true)
		{
			digit = cin.get();

			while (digit == ' ')
				digit = cin.get();

			if (digit >= '0' && digit <= '9')
			{
				result += (digit - '0') / k;
				k *= 10.0;
			}
			else
			{
				cin.putback(digit);
				break;
			}
		}
	}
	else
		cin.putback(digit);

	return sign * result;
}
