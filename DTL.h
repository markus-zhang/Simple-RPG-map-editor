/*	Dragonlance Template Library
	2016-12-08 First Edition
*/

#ifndef DTL_H_
#define DTL_H_

// Introduce Node
template<class T>
class cNode
{
public:
	T	m_Data;
	cNode<T>* m_Next;
	cNode<T>* m_Previous;
};

// Introduce Double Link List
template<class T>
class cDLink
{
public:
	cNode<T>* m_Head;
	cNode<T>* m_Tail;
	int		   m_Count;
public:
	cDLink();
	~cDLink();

	// Data Add/Remove
	void Append(T new_data);
	void Remove()
};


#endif
