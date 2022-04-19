#include "Heap.h"


namespace minimum_spanning_tree
{
	
	Heap::Heap() : m_heap(nullptr), m_max_size(0), m_heap_size(0), m_allocated(false)
	{
	}


	void Heap::build_heap(heap_node** i_arr, int i_size)
	{
		allocate_heap(i_size);
		m_heap_size = i_size;
		for (int i = 0; i < i_size; ++i) {
			const auto node = new heap_node(i_arr[i]->m_data, i_arr[i]->m_key);
			m_heap[i] = new heap_node();
			m_heap[i] = node;
		}
		m_allocated = false;
		for (int j = i_size / 2 - 1; j >= 0; --j)
			fix_heap(j);
	}

	void Heap::allocate_heap(int maxSize)
	{
		delete m_heap;

		m_heap = new heap_node*[maxSize];
		m_max_size = maxSize;
		m_heap_size = 0;
		m_allocated = true;
	}


	Heap::~Heap()
	{
		if (m_allocated)
			delete[] m_heap;
		m_heap = nullptr;
	}

	heap_node** Heap::initialize_array_for_heap(int i_source_idx, int i_size)
    {
		heap_node** array = new heap_node*[i_size];

		for(int i=0; i< i_size; i++)
		{
			if(i == i_source_idx)
			{
				array[i] = new heap_node(i, 0);
			}
			else
			{
				array[i] = new heap_node(i);
			}
		}
		return array;
    }

	void Heap::fix_heap(int i_node)
	{
		int min;
		const int left = Left(i_node);
		const int right = Right(i_node);
		if ((left < m_heap_size) && (m_heap[left]->m_key < m_heap[i_node]->m_key))
			min = left;
		else  min = i_node;
		if ((right < m_heap_size) && (m_heap[right]->m_key < m_heap[min]->m_key))
			min = right;

		if (min != i_node) {
			swap(i_node, min);
			fix_heap(min);
		}
	}


	void Heap::swap(int  a, int b) const
	{
		heap_node* temp = m_heap[a];
		m_heap[a] = m_heap[b];
		m_heap[b] = temp;
		temp->set_node_ptrs(nullptr, nullptr);

	}

	heap_node* Heap::delete_min()
	{
		if (m_heap_size < 1)
			return nullptr;

		auto min = new heap_node(*m_heap[0]);


		m_heap_size--;
		m_heap[0]->set_node_values(m_heap[m_heap_size]->m_data, m_heap[m_heap_size]->m_key);
		m_heap[0]->set_node_ptrs(m_heap[m_heap_size]->m_prev, m_heap[m_heap_size]->m_next);
		fix_heap(0);
		return(min);
	}
	
	//inserts to a huffman tree just like learned in class
	void Heap::insert(heap_node*& to_add)
	{
		if (m_heap_size == m_max_size) {
			exit(1);
		}
		int idx = m_heap_size;
		m_heap_size++;
		while ((idx > 0) && (m_heap[Parent(idx)]->m_key > to_add->m_key)) {
			m_heap[idx]->set_node_values(m_heap[Parent(idx)]->m_data, m_heap[Parent(idx)]->m_key);
			m_heap[idx]->set_node_ptrs(m_heap[Parent(idx)]->m_prev, m_heap[Parent(idx)]->m_next);
			idx = Parent(idx);
		}
		m_heap[idx]->set_node_values(to_add->m_data, to_add->m_key);
		m_heap[idx]->set_node_ptrs(to_add->m_prev, to_add->m_next);
	}

	void Heap::decrease_key(int i_place, int i_new_key)
	{
		m_heap[i_place]->m_key = i_new_key;

		while (i_place && m_heap[i_place]->m_key < m_heap[Parent(i_place)]->m_key) {
			swap(i_place, Parent(i_place));
			i_place = Parent(i_place);
		}
	}

	void Heap::print_heap() const
	{
		for (int i = 0; i < m_heap_size; ++i) 
		{
			std::cout << "Vertex Number(data) :  (" << m_heap[i]->m_data<<")" << "  weight(key) :  " << m_heap[i]->m_key << std::endl;
		}

	}

}
