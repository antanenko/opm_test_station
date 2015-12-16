//---------------------------------------------------------------------------
#ifndef tarrayH
#define tarrayH

#if defined(__ANDROID__) || defined(__APPLE__)
#if !defined(NULL)
#define NULL 0
#endif
#else
#include <cstdlib> // for NULL define
#endif

template <class T, class HT>
class TOxArray
{
	HT* Data;
	int Size;

public:
	bool AutoDelete;
	TOxArray();
	TOxArray(int size);
	~TOxArray();
	TOxArray& operator=(TOxArray& array);
	HT operator[](int i) const;

	void Clear();
	void SetSize(int size);
	int  GetSize() const {return Size;};
	HT   GetData(int i) const;
	void AddData(HT item);
	void InsData(HT item, int i);
	void DelData(int i);
	void SetData(HT item, int i);
	void DelEntry(int i);
	int Find(HT item, int startIndex = 0);
};
//---------------------------------------------------------------------------
// Implementation
//---------------------------------------------------------------------------
template <class T, class HT>
TOxArray<T, HT>::TOxArray()
{
	AutoDelete = true;
	Size = 0;
	Data = NULL;
}
//---------------------------------------------------------------------------
template <class T, class HT>
TOxArray<T, HT>::TOxArray(int size)
{
	AutoDelete = true;
	Size = size;
	Data = new HT[Size];
	for(int i = 0; i < Size; i++)
		Data[i] = NULL;
}
//---------------------------------------------------------------------------
template <class T, class HT>
TOxArray<T, HT>::~TOxArray()
{
	Clear();
}
//---------------------------------------------------------------------------
template <class T, class HT>
inline HT TOxArray<T, HT>::operator[](int i) const
{
	if (Size == 0)
		return (HT)NULL;
	if (i >= Size)
		i = Size - 1;
	return Data[i];
}
//---------------------------------------------------------------------------
template <class T, class HT>
TOxArray<T, HT>& TOxArray<T, HT>::operator=(TOxArray<T, HT>& array)
{
	if (this == &array)
		return *this;
	Clear();
	AutoDelete = array.AutoDelete;
	Size = array.Size;
	Data = new HT[Size];
	for (int i = 0; i < Size; i++)
		Data[i] = array.Data[i];
	return *this;
}
//---------------------------------------------------------------------------
template <class T, class HT>
void TOxArray<T, HT>::Clear()
{
	if (Data != NULL)
	{
		for (int i = 0; i < Size; i++)
			if((AutoDelete)&&(Data[i] != NULL))
				delete Data[i];
		delete[] Data;
		Data = NULL;
	}
	Size = 0;
}
//---------------------------------------------------------------------------
template <class T, class HT>
void TOxArray<T, HT>::SetSize(int size)
{
	HT* data;   
	int i;
	data = new HT[size];
	for(i = 0; i < size; i++)
		data[i] = NULL;
	for(i = 0; i < Size; i++)
		if(i < size)
			data[i] = Data[i];
		else if((AutoDelete)&&(Data[i] != NULL))
			delete Data[i];
	if (Data != NULL)
		delete[] Data;
	Data = data;
	Size = size;
}
//---------------------------------------------------------------------------
template <class T, class HT>
inline HT TOxArray<T, HT>::GetData(int i) const
{
	if (Size == 0)
		return (HT)NULL;
	if (i >= Size)
		i = Size - 1;
	return Data[i];
}
//---------------------------------------------------------------------------
template <class T, class HT>
void TOxArray<T, HT>::AddData(HT item)
{
	SetSize(Size + 1);
	Data[Size-1] = item;
}
//---------------------------------------------------------------------------
template <class T, class HT>
void TOxArray<T, HT>::InsData(HT item, int i)
{
	if (i > Size)
		i = Size;
	Size++;
	HT* data = new HT[Size];
	int j;
	for (j = 0; j < i; j++)
		data[j] = Data[j];
	data[i] = item;
	for (j = i + 1; j < Size; j++)
		data[j] = Data[j - 1];
	if (Data != NULL)
		delete[] Data;
	Data = data;
}
//---------------------------------------------------------------------------
template <class T, class HT>
void TOxArray<T, HT>::DelData(int i)
{
	if (Size == 0)
		return;
	if (i >= Size)
		i = Size - 1;
	Size--;
	HT* data = new HT[Size];
	int j;
	for (j = 0; j < i; j++)
		data[j] = Data[j];
	if((AutoDelete)&&(Data[i] != NULL))
		delete Data[i];
	for (j = i; j < Size; j++)
		data[j] = Data[j + 1];
	if (Data != NULL)
		delete[] Data;
	Data = data;
}
//---------------------------------------------------------------------------
template <class T, class HT>
void TOxArray<T, HT>::SetData(HT item, int i)
{
	if(Size == 0)	return;
	if (i > Size)
		i = Size-1;
	if((AutoDelete)&&(Data[i] != NULL))
		delete Data[i];
	Data[i] = item;
}
//---------------------------------------------------------------------------
template <class T, class HT>
void TOxArray<T, HT>::DelEntry(int i)
{
	bool oldValue = AutoDelete;
	AutoDelete = false;
	DelData(i);  
	AutoDelete = oldValue;
}
//---------------------------------------------------------------------------
template <class T, class HT>
int TOxArray<T, HT>::Find(HT item, int startIndex /*= 0*/)
{
	for(int i = startIndex; i < Size; i++)
		if(Data[i] == item)
			return i;
	return -1;
}
//---------------------------------------------------------------------------
#endif

