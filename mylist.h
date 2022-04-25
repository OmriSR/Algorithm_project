#pragma once
template<class item>
class mylist
{
	class m_node
	{
		friend class mylist;
		item* node_data;
		m_node* next;
	public:
		m_node(const item& ITEM)
		{
			node_data = new item(ITEM);
			next = nullptr;
		}
		~m_node() { delete node_data; }
	};
	static m_node* head;
	static m_node* tail;
public:
	class iterator
	{
		friend class mylist;
		m_node* m_ptr;
	public:
		iterator(m_node* i_ptr)
		{
			m_ptr = i_ptr;
		}
		iterator(const iterator&)
		{
			m_ptr = i_ptr;
		}
		~iterator(){}
		iterator& operator=(const iterator&)
		{
			m_ptr = i_ptr;
		}
		iterator& operator++()
		{
			return ++m_ptr;
		}
		item operator*() const
		{
			return *m_ptr;
		}
		bool operator!=(const iterator& other) { return m_ptr != other.m_ptr; }

	};
	
};

