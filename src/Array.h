#ifndef ARRAY_H
#define ARRAY_H

#include "Globals.h"
#include <SFML/Graphics.hpp>

template <class T> class Array
{
protected:
	T *arr;
	int size;

	float h;
	float w;
public:
	Array(int size);
	virtual ~Array();

	void FillNatural();
	bool RandomSwaps(int count);
	void setRenderScale(sf::VideoMode);
	void render(sf::RenderTarget &window, int a, sf::Color ca, int b, sf::Color cb, int c = -1, sf::Color cc = sf::Color::White);
	void renderRainbow(sf::RenderTarget &window, int a, sf::Color ca, int b, sf::Color cb, int c = -1, sf::Color cc = sf::Color::White);

	void recreateArray(int size);

	T getArr(int i);
	int & getSize();

	void setArr(int i, T element);
	void swapArr(int i, int j);
	void copyFill(Array<T> *a, int a_firstpos, Array<T> *b = nullptr, int b_firstpos = -1);

	T& operator[](int i);
};

template <class T> Array<T>::Array(int size) : size(size), h(2.f), w(4.f)
{
	this->arr = new T[size];
}

template <class T> Array<T>::~Array()
{
	delete [] this->arr;
}

template <class T> void Array<T>::FillNatural()
{
	for (int i = 0; i < size; i++)
		arr[i] = i + 1;
}

template <class T> bool Array<T>::RandomSwaps(int count)
{

	while (count--)
		for (int i = 0; i < size; i++)
		{
			T temp = arr[i];
			int j = random(size) - 1;
			arr[i] = arr[j];
			arr[j] = temp;
		}
	return 1;
}

template<class T>
inline void Array<T>::setRenderScale(sf::VideoMode video)
{
	this->w = (float)((video.width / size) - 1);
	this->h = w / 2;
}


template <class T> void Array<T>::render(sf::RenderTarget &window, int a, sf::Color ca, int b, sf::Color cb, int c, sf::Color cc)
{
	sf::RectangleShape rect(sf::Vector2f(w, h));
	rect.setFillColor(sf::Color::White);
	rect.setPosition(sf::Vector2f(0.f, 710.f));
	for (int i = 0; i < size; i++)
	{
		rect.setPosition(sf::Vector2f(0.f + i * (w + 1), 720.f - arr[i] * h));
		rect.setSize(sf::Vector2f(w, h * arr[i]));
		if (i == a)
			rect.setFillColor(ca);
		else if (i == b)
			rect.setFillColor(cb);
		else if (i == c)
			rect.setFillColor(cc);
		else
			rect.setFillColor(sf::Color::White);
		window.draw(rect);
	}
}

//template <class T> void Array<T>::renderRainbow(sf::RenderTarget &window, int a, sf::Color ca, int b, sf::Color cb)
//{
//	sf::RectangleShape rect(sf::Vector2f(w, h));
//	rect.setFillColor(sf::Color::White);
//	rect.setPosition(sf::Vector2f(0.f, 710.f));
//	/*float*/ int step = 765 / (size - 1);
//	while (step * (size - 1) > 255)
//		step--;
//	for (int i = 0; i < size; i++)
//	{
//		rect.setPosition(sf::Vector2f(0.f + i * (w + 1), 720.f - arr[i] * h));
//		rect.setSize(sf::Vector2f(w, h * arr[i]));
//		if (i == a)
//			rect.setFillColor(ca);
//		else if (i == b)
//			rect.setFillColor(cb);
//		else
//		{
//			if (arr[i] - 1 <= size / 3)
//				rect.setFillColor(sf::Color(255 - step * (arr[i] - 1), step * (arr[i] - 1), 0, 255));
//			else if (arr[i] - 1 > size / 3 && arr[i] - 1 <= (size / 3) * 2)
//				rect.setFillColor(sf::Color(0, 255 - step * (arr[i] - 1), step * (arr[i] - 1), 255));
//			else
//				rect.setFillColor(sf::Color(step * (arr[i] - 1), 0, 255 - step * (arr[i] - 1), 255));
//		}
//		window.draw(rect);
//	}
//}

template <class T> void Array<T>::renderRainbow(sf::RenderTarget &window, int a, sf::Color ca, int b, sf::Color cb, int c, sf::Color cc)
{
	sf::RectangleShape rect(sf::Vector2f(w, h));
	rect.setFillColor(sf::Color::White);
	rect.setPosition(sf::Vector2f(0.f, 710.f));
	/*float*/ int step = 768 / size;
	//while (step * (size - 1) > 255)
	//	step--;
	for (int i = 0; i < size; i++)
	{
		rect.setPosition(sf::Vector2f(0.f + i * (w + 1), 720.f - arr[i] * h));
		rect.setSize(sf::Vector2f(w, h * arr[i]));
		if (i == a)
			rect.setFillColor(ca);
		else if (i == b)
			rect.setFillColor(cb);
		else if (i == c)
			rect.setFillColor(cc);
		else
		{
			if (arr[i] - 1 <= size / 3)
				rect.setFillColor(sf::Color(255 - step * (arr[i] - 1), step * (arr[i] - 1), 0, 255));
			else if (arr[i] - 1 > size / 3 && arr[i] - 1 <= (size / 3) * 2)
				rect.setFillColor(sf::Color(0, 255 - step * (arr[i] - 1), step * (arr[i] - 1), 255));
			else
				rect.setFillColor(sf::Color(step * (arr[i] - 1), 0, 255 - step * (arr[i] - 1), 255));
		}
		window.draw(rect);
	}
}

template<class T>
inline void Array<T>::recreateArray(int size)
{
	delete this->arr;
	this->size = size;
	this->arr = new T[this->size];
}

template <class T> T Array<T>::getArr(int i)
{
	return this->arr[i];
}

template <class T> int & Array<T>::getSize()
{
	return this->size;
}

template<class T>
inline void Array<T>::setArr(int i, T element)
{
	this->arr[i] = element;
}

template<class T>
inline void Array<T>::swapArr(int i, int j)
{
	T temp = this->arr[i];
	this->arr[i] = this->arr[j];
	this->arr[j] = temp;
}

template<class T>
inline void Array<T>::copyFill(Array<T> *a, int a_firstpos, Array<T> *b, int b_firstpos)
{
	int i = 0;
	for (; i < this->size; i++)
	{
		if (i + a_firstpos < a->size)
		{
			this->arr[i] = a->arr[i + a_firstpos];
		}
	}
	if (b_firstpos != -1)
		for (int j = 0; this->size; j++)
		{
			if (j + b_firstpos < b->size)
			{
				this->arr[i++] = b->arr[j + b_firstpos];
			}
			else
				this->arr[i++] = 0;
		}
	else
		for (; i < this->size; i++)
		{
			this->arr[i] = 0;
		}
}

template<class T>
inline T & Array<T>::operator[](int i)
{
		try
		{
			if (i < this->size)
			{
				return this->arr[i];
			}
			else
				throw "Error Array[i], i > size!";
		}
		catch (char *str)
		{
			cerr << str << endl;
		}
		return NULL;
}


#endif