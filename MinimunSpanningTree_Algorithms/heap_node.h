#pragma once
#include <climits>
#include <cstdlib>
#include <iostream>

namespace minimum_spanning_tree
{
	class heap_node
	{
	public:
		int m_data;
		int m_key;
		heap_node* m_prev;
		heap_node* m_next;
		heap_node():m_data(0),m_key(0), m_prev(nullptr), m_next(nullptr){}
		heap_node(const int i_vertexNum):  m_data(i_vertexNum), m_key(INT_MAX), m_prev(nullptr), m_next(nullptr) {}
		heap_node(const int i_vertexNum, const int i_key) : m_data(i_vertexNum), m_key(i_key), m_prev(nullptr), m_next(nullptr) {}
		static heap_node* create_new_heap_node(const int i_vertexNum,const int i_key) { return new heap_node(i_vertexNum, i_key); }
		void set_node_values(const int i_data, const int i_key) { m_data = i_data; m_key = i_key; }
		void set_node_ptrs(heap_node* i_prev, heap_node* i_next) { m_prev = i_prev; m_next = i_next; }

		


		int get_vertex_num() const { return m_data; }
		int get_vertex_key() const { return m_key; }
	};




}
