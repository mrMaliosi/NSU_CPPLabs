#include "bitset.h"
#include <string>
#include <iostream>

typedef unsigned long bitword;
#define VALUE_BITS (CHAR_BIT * sizeof(bitword))
#define NUM_BYTES (num_bits/VALUE_BITS + 1)
#define MAX_BYTE 4294967295

typedef unsigned long ul;

//Конструирует массив, хранящий заданное количество бит.
//Первые sizeof(long) бит можно инициализровать с помощью параметра value.
BitArray::BitArray(int num_bits, unsigned long value = 0)
{
    bits_ = std::make_unique<bitword[]>(NUM_BYTES);
    bits_[0] = value;
    maxSize_ = NUM_BYTES * VALUE_BITS;
    if (num_bits < VALUE_BITS)
    {
        size_ = num_bits;
    }
    else{
        size_ = VALUE_BITS; 
    }
    bytes_ = NUM_BYTES;
}

BitArray::BitArray(const BitArray& b)
{
    int num_bits = b.size_;
    bits_ = std::make_unique<bitword[]>(NUM_BYTES);
    maxSize_ = NUM_BYTES * VALUE_BITS;
    if (num_bits < VALUE_BITS)
    {
        size_ = num_bits;
    }
    else{
        size_ = VALUE_BITS; 
    }
    bytes_ = NUM_BYTES; 
    for (int i = 0; i < NUM_BYTES; ++i)
    {
        bits_[i] = b.bits_[i];
    }  
}

void BitArray::swap(BitArray& b)
{
    //swap(this->bytes_, b.bytes_);
    int c = this->bytes_;
    this->bytes_ = b.bytes_;
    b.bytes_ = c;
    //swap(this->size_, b.size_);
    c = this->size_;
    this->size_ = b.size_;
    b.size_ = c;
    //swap(this->maxSize_, b.maxSize_);
    c = this->maxSize_;
    this->maxSize_ = b.maxSize_;
    b.maxSize_ = c;
    //swap(this->bits_, b.bits_);
    std::unique_ptr<bitword[]>p = move(this->bits_);
    this->bits_ = move(b.bits_);
    b.bits_ = move(p);
}

BitArray& BitArray::operator=(const BitArray& b)
{
	int num_bits = b.size_;
    bits_ = std::make_unique<bitword[]>(NUM_BYTES);
    maxSize_ = NUM_BYTES * VALUE_BITS;
    if (num_bits < VALUE_BITS)
    {
        size_ = num_bits;
    }
    else{
        size_ = VALUE_BITS; 
    }
    bytes_ = NUM_BYTES; 
    for (int i = 0; i < NUM_BYTES; ++i)
    {
        bits_[i] = b.bits_[i];
    }  
	return *this;
}

void BitArray::resize(int num_bits, bool value = false)
{
    if (num_bits > this->maxSize_)
    {
        int l = this->size_;
        int s = this->bytes_;
        this->maxSize_ = NUM_BYTES * VALUE_BITS;
        std::unique_ptr<bitword[]>p = std::make_unique<bitword[]>(NUM_BYTES);
        for (int i = 0; i < s; ++i)
        {
            p[i] = this->bits_[i];
        }
        this->bits_.reset();
        this->bits_ = move(p);
        for (int i = l; i < num_bits; ++i)
        {
            this->push_back(value);
        }
        this->bytes_ = NUM_BYTES;
    }
    else if (num_bits < this->maxSize_)
    {
        this->size_ = num_bits; 
        this->maxSize_ = NUM_BYTES * VALUE_BITS;
        this->bytes_ = NUM_BYTES;
        std::unique_ptr<bitword[]>p = std::make_unique<bitword[]>(NUM_BYTES);
        for (int i = 0; i < NUM_BYTES; ++i)
        {
            p[i] = this->bits_[i];
        }
        
        this->bits_.reset();
        this->bits_ = move(p);
        int ma = MAX_BYTE;
        ma <<= VALUE_BITS - num_bits % VALUE_BITS - 1;
        this->bits_[NUM_BYTES - 1] & ma;
    }
}

void BitArray::clear()
{
    this->bits_.reset();
    this->size_ = 0;
    this->maxSize_ = 0;
    this->bytes_ = 0;
}

void BitArray::push_back(bool bit)      //Обработай расширение
{
    int i = this->size_ / VALUE_BITS;
	int j = this->size_ % VALUE_BITS;
    this->size_ += 1;
    int Bit;
	if (bit == 1)
	{
		Bit = 1 << (VALUE_BITS - 1 - j);
		this->bits_[i] |= Bit;
	}
	else
	{
		Bit = 1;
		Bit = Bit << (VALUE_BITS - 1 - j);
		Bit = ~Bit;
		this->bits_[i] &= Bit;
	}
}

BitArray& BitArray::operator&=(const BitArray& b)
{
	if (this->size_ == b.size_)
	{
		int l = b.size_;
		for (int i = 0; i < l; ++i)
		{
			this->bits_[i] &= b.bits_[i]; 
		}
		return *this;
	}
	else
	{
		std::cout << "Arrays are not equal. Operator &=" << std::endl;
		exit(1);
	}
}

BitArray& BitArray::operator|=(const BitArray& b)
{
    if (this->size_ == b.size_)
    {
        int l = b.size_;
        for (int i = 0; i < l; ++i)
        {
            this->bits_[i] |= b.bits_[i];
        }
        return *this;
    }
    else
    {
        std::cout << "Arrays are not equal. Operator |=" << std::endl;
        exit(2);
    }
}
BitArray &BitArray::operator^=(const BitArray &b)
{
    if (this->size_ == b.size_)
    {
        int l = b.bytes_;
        for (int i = 0; i < l; ++i)
        {
            this->bits_[i] ^= b.bits_[i];
        }
        return *this;
    }
    else
    {
        std::cout << "Arrays are not equal. Operator ^=" << std::endl;
        exit(3);
    }
}


BitArray& BitArray::operator<<=(int n)
{
    std::unique_ptr<bitword[]> p = std::make_unique<bitword[]>(this->bytes_);
    bitword byte = 0;
    int count = 0;
    int count1;
    for (int i = n; i < this->size_; ++i)
    {
        int k = n / VALUE_BITS;
        int j = n % VALUE_BITS;
        count1 = count % VALUE_BITS;
        int bit = (((1) & this->bits_[k]) << (VALUE_BITS - 1 - count1));
        p[count / VALUE_BITS] |= bit;
        ++count;
    }
    this->bits_ = move(p);
    return *this;
}

BitArray &BitArray::operator>>=(int n)
{
    std::unique_ptr<bitword[]> p = std::make_unique<bitword[]>(this->bytes_);
    bitword byte = 0;
    int count = 0, count1 = 0;
    for (int i = 0; (i < n / VALUE_BITS) &&(i < this->bytes_); ++i)
    {
        p[i] = 0;
    }
    for (int i = n; i < this->size_; ++i)
    {
        int k = count / VALUE_BITS;
        int j = count % VALUE_BITS;
        count1 = i % VALUE_BITS;
        int bit = (1 << (VALUE_BITS - 1 - count1)) & this->bits_[k];
        p[i / VALUE_BITS + 1] |= bit;
        ++count;
    }
    this->bits_ = move(p);
    return *this;
}
BitArray BitArray::operator<<(int n) const
{
    std::unique_ptr<bitword[]> p = std::make_unique<bitword[]>(this->bytes_);
    bitword byte = 0;
    int count = 0;
    int count1;
    for (int i = n; i < this->size_; ++i)
    {
        int k = n / VALUE_BITS;
        int j = n % VALUE_BITS;
        count1 = count % VALUE_BITS;
        int bit = (1 << (VALUE_BITS - 1 - j)) & this->bits_[k];
        p[count / VALUE_BITS] |= bit;
        ++count;
    }
    BitArray q(this->size_, 0);
    q.bits_ = move(p);
    return q;
}
BitArray BitArray::operator>>(int n) const
{
    std::unique_ptr<bitword[]> p = std::make_unique<bitword[]>(this->bytes_);
    bitword byte = 0;
    int count = 0, count1 = 0;
    for (int i = 0; i < n / VALUE_BITS; ++i)
    {
        p[i] = 0;
    }
    for (int i = n; i < this->size_; ++i)
    {
        int k = count / VALUE_BITS;
        int j = count % VALUE_BITS;
        count1 = i % VALUE_BITS;
        int bit = (1 << (VALUE_BITS - 1 - count1)) & this->bits_[k];
        p[i / VALUE_BITS + 1] |= bit;
        ++count;
    }
    BitArray q(this->size_, 0);
    q.bits_ = move(p);
    return q;
}

//Устанавливает бит с индексом n в значение val.
BitArray& BitArray::set(int n, bool val = true)         //добавь обработку случая n > maxSize_
{
    int i = n / VALUE_BITS;
	int j = n % VALUE_BITS;
	if (val == 1)
	{
		val = val << (VALUE_BITS - 1 - j);
		this->bits_[i] |= val;
	}
	else
	{
		val = 1;
		val = val << (VALUE_BITS - 1 - j);
		val = ~val;
		this->bits_[i] &= val;
	}

    return *this;
}
//Заполняет массив истиной.
BitArray& BitArray::set()
{
    for (int i = 0; i < this->bytes_; ++i)
    {
        this->bits_[i] = MAX_BYTE;
    }
    return *this;
}

//Устанавливает бит с индексом n в значение false.
BitArray& BitArray::reset(int n)
{
    int i = n / VALUE_BITS;
	int j = n % VALUE_BITS;
	int val = 1;
	val = val << (VALUE_BITS - 1 - j);
	val = ~val;
	this->bits_[i] &= val;
    return *this;
}
//Заполняет массив ложью.
BitArray& BitArray::reset()
{
    for (int i = 0; i < this->bytes_; ++i)
    {
        this->bits_[i] = 0;
    }
    return *this;
}

//true, если массив содержит истинный бит.
bool BitArray::any() const
{
    for (int i = 0; i < this->bytes_; ++i)
    {
        if (this->bits_[i] > 0)
        {
            return 1;
        }
    }
    return 0;
}
//true, если все биты массива ложны.
bool BitArray::none() const
{
    for (int i = 0; i < this->bytes_; ++i)
    {
        if (this->bits_[i] > 0)
        {
            return 0;
        }
    }
    return 1;
}

BitArray BitArray::operator~() const
{
    for (int i = 0; i < this->bytes_; ++i)
    {
        this->bits_[i] = ~this->bits_[i];
    }
    return *this;
}

//Подсчитывает количество единичных бит.
int BitArray::count() const
{
        int left = 0;
        int right = this->bytes_ * VALUE_BITS;
        int ans = 0, value;
		int i = left / VALUE_BITS;
		int j = left % VALUE_BITS;
		unsigned int b = 1, m;
		while (i*VALUE_BITS + j < right)
		{
			b = 1 << (VALUE_BITS - 1 - j);
			if (this->bits_[i] & b)
			{
				++ans;
			}
			else
			{
				m = this->bits_[i];
				b = ~b;
				m &= b;
				if (m == 0)
				{
					j = 31;
				}
			}
			++j;

			if (j == VALUE_BITS)
			{
				j = 0;
				++i;
				while (this->bits_[i] == 0)
				{
					++i;
					if (i*VALUE_BITS >= right)
					{
						return ans;
					}
				}

				while (i*VALUE_BITS + VALUE_BITS <= right)
				{
					value = this->bits_[i];
					value = (value & 0x55555555) + ((value >> 1) & 0x55555555);
					value = (value & 0x33333333) + ((value >> 2) & 0x33333333);
					value = (value & 0x0f0f0f0f) + ((value >> 4) & 0x0f0f0f0f);
					value = (value & 0x00ff00ff) + ((value >> 8) & 0x00ff00ff);
					value = (value & 0x0000ffff) + ((value >> 16) & 0x0000ffff);
					ans += value;
					++i;
				}

				if ((this->bits_[i] < 256) && (i*VALUE_BITS + 24 < right))				//2^24 (оптимизация)
				{
					j += 24;
				}
				else if ((this->bits_[i] < 65536) && (i*VALUE_BITS + 16 < right))				//2^16 (оптимизация)
				{
					j += 16;
				}
				else if ((this->bits_[i] < 16777216) && (i*VALUE_BITS + 8 < right))				//2^8 (оптимизация)
				{
					j += 8;
				}

			}
		}

		return ans;
}


//Возвращает значение бита по индексу i.
bool BitArray::operator[](int i) const
{
    int k = i / VALUE_BITS;
    int j = i % VALUE_BITS;
    int b = 1 << (VALUE_BITS - 1 - j);
    try
    {
        bits_[k];
    }
    catch (...)
    {
        throw "Error, empty BitArray.";
    }
    return b & this->bits_[k] ? 1 : 0;
}

int BitArray::size() const
{
    return this->size_;
}
bool BitArray::empty() const
{
    if(this->bytes_ == 0)
    {
        return 1;
    }
    return 0;
}
  
//Возвращает строковое представление массива.
std::string BitArray::to_string() const
{
    std::string s;
    for (int i = 0; (i < this->bytes_); ++i)
    {
        for (int j = 0; (j < VALUE_BITS) && (i*VALUE_BITS + j < this->size_); ++j)
        {
            auto a = (this->bits_[i] >> (VALUE_BITS - 1 - j)) & 1;
            if (a == 1)
            {
                s += '1';
            }
            else{
                s += '0';
            }
            
        }
    }

    return s;
}

bool operator==(const BitArray& a,const BitArray & b)
{
	if(a.to_string() == b.to_string())
 	{
 		return 1;
 	}
	return 0;
}

bool operator!=(const BitArray& a,const BitArray & b)
{
	if(a.to_string() == b.to_string())
 	{
 		return 0;
 	}
	return 1;
}

BitArray operator&(const BitArray& b1, const BitArray& b2)
{
    if (b1.size() == b2.size())
	{
		int l = b1.size();
        BitArray q(b1.size(), 0);
		std::unique_ptr<bitword[]>p = std::make_unique<bitword[]>(b1.size() / VALUE_BITS + 1);
		for (int i = 0; i < l; ++i)
		{
			p[i] = b1[i] & b2[i]; 
		}
		q.bits_ = move(p);
		return q;
	}
	else
	{
		std::cout << "Arrays are not equal. Operator &" << std::endl;
		exit(4);
	}
}

BitArray operator|(const BitArray& b1, const BitArray& b2)
{
    if (b1.size() == b2.size())
	{
		int l = b1.size();
        BitArray q(b1.size(), 0);
		std::unique_ptr<bitword[]>p = std::make_unique<bitword[]>(b1.size() / VALUE_BITS + 1);
		for (int i = 0; i < l; ++i)
		{
			p[i] = b1[i] | b2[i]; 
		}
		q.bits_ = move(p);
		return q;
	}
	else
	{
		std::cout << "Arrays are not equal. Operator |" << std::endl;
		exit(5);
	}
}

BitArray operator^(const BitArray& b1, const BitArray& b2)
{
    if (b1.size() == b2.size())
	{
		int l = b1.size();
        BitArray q(b1.size(), 0);
		std::unique_ptr<bitword[]>p = std::make_unique<bitword[]>(b1.size() / VALUE_BITS + 1);
		for (int i = 0; i < l; ++i)
		{
			p[i] = b1[i] ^ b2[i]; 
		}
		q.bits_ = move(p);
		return q;
	}
	else
	{
		std::cout << "Arrays are not equal. Operator ^" << std::endl;
		exit(6);
	}
}

