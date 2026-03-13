***Type Casting & Static Classes***
===================================
	- это способ сообщить программе, что произошла ошибка.

**Static Class (Non-instantiable Class)**
-----------------------------------------

 *Задача:*
   - создать класс, к-рый *НЕЛЬЗЯ* создать (нельзя сделать объект)

 *Решение:*
   - сделать конструктор *ПРИВАТНЫМ*

 ```c++
		class ScalarConverter {
			private:
					// Private constructors - cannot instantiate
					ScalarConverter();
					ScalarConverter(const ScalarConverter& other);
					ScalarConverter& operator=(const ScalarConverter& other);
					~ScalarConverter();

			public:
					// Only static method
					static void convert(const std::string& literal);
		};
 ```

 *Почему это работает:*
   - Конструкторы приватные -> нельзя создать объект извне
   - Метод `convert()` - *static* -> вызывается без объекта:
		`ScalarConverter::convert("42")`

**Type Casting**
----------------

 1. **static_cast** - безопасное приведение между совместимыми типами:

 ```c++
		int i = 42;
		float f = static_cast<float>(i);	// int → float
		char c = static_cast<char>(65);		// int → char ('A')
 ```

 2. **dynamic_cast** - для полиморфных классов (проверка во время выполнения):

 ```c++
		Base* base = new Derived();
		Derived* derived = dynamic_cast<Derived*>(base);
 ```

 3. **const_cast** - снимает const:

 ```c++
		const int* constPtr = &value;
		int* ptr = const_cast<int*>(constPtr);
 ```

 4. **reinterpret_cast** - "грубое" приведение (переинтерпретация битов):

 ```c++
		int* ptr = reinterpret_cast<int*>(0x12345678);
 ```

 *Для этого задания используем:* - `static_cast`

 *Определение типа литерала*

 *Правила распознавания:*
   1. `char: 'c'` - одиночный символ в одинарных кавычках
   2. `int: 42, -42, 0` - целое число без точки
   3. `float: 42.0f, -4.2f, nanf, +inff` - с точкой и суффиксом `f`
   4. `double: 42.0, -4.2, nan, +inf` - с точкой, без суффикса

 *Алгоритм:*

 ```c++
		// Псевдокод
		if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
			type = CHAR;
		else if (literal == "nanf" || literal == "+inff" || literal == "-inff")
			type = FLOAT;
		else if (literal == "nan" || literal == "+inf" || literal == "-inf")
			type = DOUBLE;
		else if (literal.find('.') != std::string::npos && literal.back() == 'f')
			type = FLOAT;
		else if (literal.find('.') != std::string::npos)
			type = DOUBLE;
		else
			type = INT;
 ```

 *Специальные значения - inf, NaN*

 1. *Infinity (бесконечность)*
   
 ```c++
		#include <cmath>
		#include <limits>

		float f = std::numeric_limits<float>::infinity();	// +inf
		float f2 = -std::numeric_limits<float>::infinity();	// -inf

		// Проверка
		if (std::isinf(value))  // true если бесконечность
 ```

 2. *NaN (Not a Number)*
   
 ```c++
		float f = std::numeric_limits<float>::quiet_NaN();   // nan

		// Проверка
		if (std::isnan(value))  // true если NaN
 ```

 *ВАЖНО:* NaN != NaN (даже сам с собой)

 *String to Number конверсия*

 ```c++
		#include <cstdlib>  // atoi, atof
		#include <sstream>  // stringstream

		// atoi - string to int
		int i = std::atoi("42");		// returns 42

		// atof - string to double
		double d = std::atof("42.5");	// returns 42.5

		// strtod - более гибкая версия
		char* end;
		double d = std::strtod("42.5f", &end);  // end указывает на 'f'
 ```

 *Проверка на displayable char*

   *Displayable* - символ, к-рый можно напечатать(32-126 в ASCII)

   ```c++
		bool isDisplayable(char c) {
    		return (c >= 32 && c <= 126);
		}
   ```
