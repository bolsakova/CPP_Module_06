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


***Serialization***
====================
 Обычно сериализация = сохранить объект в строку/байты/файл.
 Но в задании нужно сделать только:
   - `Data*` -> `uintptr_t`
   - `uintptr_t` -> `Data*`

 т.е. просто "упаковать адрес в число" и обратно "распаковать число в адрес"

 **Ключевая идея**
   - указатель `Data*` это адрес в памяти, например условно `0x7ffee3ab20`.

   `uintptr_t` - это целое число, которое гарантированно вмещает адрес. Поэтому:
      - `serialize(ptr)` возвращает числовое представление адреса `ptr`
      - `deserialize(raw)` возвращает указатель из этого числа

 **Почему именно `uintptr_t`**

   `uintptr_t` из `<cstdint>`:
      - `u` = unsigned
      - `ptr` = pointer-sized
	  - гарантированно подходит для зранения адреса
	
   Нельзя надежно использовать просто `unsigned int/int`, потому что размер может быть меньше размера адреса.

 **Какой `cast` использовать и почему**

   Для этого задания нужен `reinterpret_cast`
   ```c++
		uintptr_t raw = reinterpret_cast<uintptr_t>(ptr);
		Data* restored = reinterpret_cast<Data*>(raw);
   ```

   Почему не `static_cast`:
   - `static_cast` не предназначен для такого "сыро-битового" преобразования адреса <-> числа.
   - `reinterpret_cast` как раз для низкоуровневой переинтерпретации битов.

 **Что обязательно должно быть в `Data`**

   По условию `Data` должна быть non-empty.
   Т.е. не пустая строка, а с полями:

   ```c++
		struct Data {
			int id;
			std::string name;
			double score;
		};
   ```

   Это нужно, чтобы доказать, что мы работаем с реальным объектом, а не с "пустышкой".

 **Что значит "ensure compares equal"**

   В `main` нужно проверить:

   1. Создать объект `Data data;`
   2. Взять адрес `Data* original = &data;`
   3. Сделать `uintptr_t raw = Serializer::serialize(original);`
   4. Сделать `Data* restored = Serializer::deserialize(raw);`
   5. Проверить: `restored == original` -> должно быть `true`

   Если равны, значит адрес "туда-обратно" сохранился.
   `restore->id` - они должны совпадать с `data`.

 **Почему класс `Serializer` нельзя инстанцировать**

   По условию: “will not be initializable by user in any way”.
   Значит:
   - приватный default ctor
   - приватный copy ctor
   - приватный operator=
   - приватный dtor
   - толко `public static` методы

   Тогда можно вызвать только так:

   ```c++
		Serializer::serialize(ptr);
		Serializer::deserialize(raw);
   ```

   И нельзя сделать:

   ```c++
		Serializer s; // должно быть запрещено
   ```

 **Важный момент про память**

   `serialize` и `deserialize` *не копируют объект* и не создают новй объект.
   Они только преобразуют тип представления адреса.

   Т.е. `restored` указывает на тот же самый объект, что и `original`.

 **Мини-ментальная модель**

   Представим:
   - Указатель = бумажка с адресом дома
   - `uintptr_t` = этот же адрес, но записан в виде числа
   - Мы не переносим дом, не создаем дом заново
   - мы просто записываем/читаем один и тот же адрес в другом формате


***Identify Real Type***
=========================

 **Goal**
   - implement  runtime type identification without using <typeinfo>. Create Base with virtual dtor; classes A, B, C inherit from Base.
  
  Provide:
	- `Base* generate();` - случайно создает А, В или С и возвращает как `Base*`
  - `void identify(Base* p);` - определяет реальный тип по указателю и печатает "А", "В" или "С"
  - `void identify(Base& p);` - определяет реальный тип по ссылке (нельзя использовать указатель внутри этой функции) и печатает "А", "В" или "С"

 **Базовая идея**

   У нас есть общий базовый тип `Base`, и три наследника `A`, `B`, `C`. Во время выполнения у нас ест указатель или ссылка типа `Base` на объект одного из наследников. Нужно определить, какого конкретного класса этот объект.

 **Почему нельзя использовать `typeinfo`**

   Условие запрещает `std::type_info` / `typeid`. Вместо этого используем механизм RTTI, к-рый предоставляет `dynamic_cast`.

   `dynamic_cast` - безопасно проверяет реальный тип и возвращает `nullptr` для указателя, если привидение не прошло, или бросает исключение `std::bad_cast` при приведении ссылок.

 **Как реализовать `generate()`**

   - Сделать случайный выбор между А, В, С (например, `rand() % 3` или `<random>`).
   - Создать объект через `new` и вернуть `Base*`.
   - В тесте не забыть `delete` для предотвращения утечек.

 **Как реализовать `identify(Base* p)`**

   Для указателя просто попробовать `dynamic_cast` к каждому наследнику (просто и эффективно):
   - если `dynamic_cast<A*>(p) != nullptr` -> `A`.
   - иначе проверить `B`, `C`.

 **Как реализовать `identify(Base& p)`**

   Нельзя использовать указатель внутри функции (по условию).

   Решение: попытки безопасно выполнить `dynamic_cast` к ссылочному типу в `try`/`catch`:
   - `dynamic_cast<A&>(p)` - если не ьросило исключение, это `A`.
   - если бросило, ловим исключение (можно `catch(...)`) и пробуем следующий класс.

   Важно: мы не используем `typeid`, и не объявляем/используем `std::bad_cast` явно (чтобы не подключать `<typeinfo>`). Достаточно `try` + `catch(...)` или `catch(std::exception&)`.

 **Тонкости**

   - Проверка по указателю обычно предпочтительнее, так как не бросает исключений.
   - Для `identify(Base& p)` использовать `try`/`catch` и последовательные `dynamic_cast<T&>`
   - Не вводить дополнительные указатели в теле `identify(Base& p)` по условию.
   - Вывод без лишних символов


