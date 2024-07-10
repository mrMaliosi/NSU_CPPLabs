#pragma once
#include <string>
#include <iostream>
#include <memory>
#define VALUE_BITS (CHAR_BIT * sizeof(bitword))
#define NUM_BYTES (num_bits/VALUE_BITS + 1)
#define MAX_BYTE 4294967295
class BitArray
{
	typedef unsigned long bitword;
private:
	
public:
	std::unique_ptr<bitword[]> bits_;
	int size_;
	int maxSize_;
	int bytes_;
	BitArray()
	{
		this->bits_ = std::make_unique<bitword[]>(1);
   	 	this->maxSize_ = 1;
    	this->size_ = 0;
    	this->bytes_ = 1;
	}
	~BitArray()
	{
		std::cout << "1" << std::endl;
	}

	//Конструирует массив, хранящий заданное количество бит.
  	//Первые sizeof(long) бит можно инициализровать с помощью параметра value.
	explicit BitArray(int num_bits, unsigned long value);
	BitArray(const BitArray& b);


	//Обменивает значения двух битовых массивов.
	void swap(BitArray& b);

	BitArray& operator=(const BitArray& b);


	//Изменяет размер массива. В случае расширения, новые элементы 
  	//инициализируются значением value.
	void resize(int num_bits, bool value);
	//Очищает массив.
	void clear();
	//Добавляет новый бит в конец массива. В случае необходимости 
  	//происходит перераспределение памяти.
	void push_back(bool bit);


	//Битовые операции над массивами.
  	//Работают только на массивах одинакового размера.
  	//Обоснование реакции на параметр неверного размера входит в задачу!
	BitArray& operator&=(const BitArray& b);
	BitArray& operator|=(const BitArray& b);
	BitArray& operator^=(const BitArray& b);

	//Битовый сдвиг с заполнением нулями.
	BitArray& operator<<=(int n);
	BitArray& operator>>=(int n);
	BitArray operator<<(int n) const;
	BitArray operator>>(int n) const;


	//Устанавливает бит с индексом n в значение val.
	BitArray& set(int n, bool val);
	//Заполняет массив истиной.
	BitArray& set();

	//Устанавливает бит с индексом n в значение false.
  	BitArray& reset(int n);
  	//Заполняет массив ложью.
  	BitArray& reset();

  	//true, если массив содержит истинный бит.
  	bool any() const;
  	//true, если все биты массива ложны.
  	bool none() const;
  	//Битовая инверсия
  	BitArray operator~() const;
  	//Подсчитывает количество единичных бит.
  	int count() const;


  	//Возвращает значение бита по индексу i.
  	bool operator[](int i) const;

  	int size() const;
  	bool empty() const;
  
  	//Возвращает строковое представление массива.
  	std::string to_string() const;

};

bool operator==(const BitArray& a,const BitArray & b);
bool operator!=(const BitArray& a,const BitArray & b);

BitArray operator&(const BitArray& b1, const BitArray& b2);
BitArray operator|(const BitArray& b1, const BitArray& b2);
BitArray operator^(const BitArray& b1, const BitArray& b2);

