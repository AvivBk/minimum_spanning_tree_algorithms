#pragma once
#include <cstdlib>
#include <iostream>

namespace minimum_spanning_tree
{
	class vertex_node
	{
	public:
		int m_vertex;
		vertex_node* m_prev;
		vertex_node* m_next;
		int m_weight_to_next;
		void set_node_ptr(vertex_node* i_prev, vertex_node* i_next) { this->m_prev = i_prev; this->m_next = i_next; }
		void set_node_values(int i_vertexNum, int i_weight) { this->m_vertex = i_vertexNum; this->m_weight_to_next = i_weight; }
	};
}