#include <iostream>
using namespace std;

class MyClass
{
	int n;	
	public:
		MyClass():n(0){}

		void Show()
		{
			cout << n << endl;
		} 
		
		void Set(int n)
		{
			this->n = n;
		}

		int Get()
		{
			return n;
		}
};

class SmartPointer 
{
	// Инкапсулированный указатель
	MyClass *ptr;
	//счётчик копий 
	int count_copy;

public:

	//конструктор
	SmartPointer (MyClass *p = nullptr)
	{
		cout << "Constructor" << endl;
		//записываем 0 -  при создании копий нет
		count_copy = 0;
		ptr = p;
	}

	// конструктор копирования
	SmartPointer(const SmartPointer &obj)
	{
		cout << "Copy-Constructor" << endl;
		//создается копия - увеличиваем счётчик
		ptr = obj.ptr;
		count_copy = obj.count_copy;
		count_copy++;		
	}

	//перегрузка оператора присваивания
	SmartPointer& operator=(const SmartPointer &obj)
	{
		cout << "operator = " << endl;
		//создается копия - увеличиваем счётчик
		ptr = obj.ptr;
		count_copy = obj.count_copy;
		count_copy++;
		//возвращаем сам объект для ситуации a=b=c
		return *this;
	}

	// уничтожение объекта
	~SmartPointer()
	{
		//если объект есть и копий нет
		if(ptr != nullptr && count_copy == 0)
		{
			cout<<"\n~Delete Object\n";
			//уничтожаем объект
			delete ptr;
		}
		//в противном случае(уничтожается копия)
		else
		{
			//уменьшаем счётчик
			count_copy--;
			cout<<"\n~Delete Copy\n";
		}		
	} 
	//перегрузка селектора
	MyClass* operator->()
	{
		return ptr;
	}
};

int main()
{
	//создаем объект
	MyClass *main_ptr = new MyClass;
	//инициализируем этим объектом умный указатель
	SmartPointer PTR(main_ptr), PTR2;
	//проверяем работу умного указателя
	PTR->Set(10);
	PTR->Show();
	// создаем копию (работа конструктора копирования)
	SmartPointer PTR3 = PTR;
	PTR3->Show();
	// создаем копию (работа оператора =)
	PTR2 = PTR3;
	PTR2->Show();
	// delete main_ptr; // ошибка времени выполнения
	// освобождение динамической памяти осуществляется классом SmartPointer

	return 0;
}

