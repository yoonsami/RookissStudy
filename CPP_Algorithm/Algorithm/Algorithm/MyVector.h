#pragma once



template <typename T>
class MyVector
{
public:
	MyVector();
	~MyVector();
private:
	void reserve(int capacity);
	void push_back(const T& data);
	void pop_back();
	void clear();

	T& operator[](const int index);


	T* _data = nullptr;
private:
	int _capacity = 0;
	int _size = 0;

};

template <typename T>
void MyVector<T>::clear()
{
	_size = 0;
	if (_data)
	{
		delete[] _data;
		_data = new T[_capacity];
	}

}

template <typename T>
T& MyVector<T>::operator[](const int index)
{
	return _data[index];
}

template <typename T>
void MyVector<T>::push_back(const T& data)
{
	if (_size == _capacity)
	{
		int newCapacity = static_cast<int>(_capacity * 1.5);
		if (newCapacity == _capacity)
			newCapacity++;

		reserve(newCapacity);
	}

	_data[_size] = data;
	_size++;
}

template<typename T>
inline void MyVector<T>::pop_back()
{
	
}

template<typename T>
inline MyVector<T>::MyVector()
{
}

template<typename T>
inline MyVector<T>::~MyVector()
{
	if (_data)
		delete[] _data;
}

template<typename T>
inline void MyVector<T>::reserve(int capacity)
{
	if (_capacity < capacity)
	{
		_capacity = capacity;

		T* tmpData = new T[capacity];

		for (int i = 0; i < _size; ++i)
			tmpData[i] = _data[i];
		if (_data)
			delete[] _data;

		_data = tmpData;

	}

}
