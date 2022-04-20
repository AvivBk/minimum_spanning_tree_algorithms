#pragma once
#include "edge_node.h"
namespace minimum_spanning_tree
{
	class vertex_node
	{
	public:
		edge_node* m_edge;
		vertex_node* m_prev;
		vertex_node* m_next;


		vertex_node(int i_source, int i_dest, int i_weight) :m_edge( new edge_node(i_source,i_dest,i_weight)), m_prev(nullptr), m_next(nullptr)
		{
		}

		void set_node_ptr(vertex_node* i_prev, vertex_node* i_next) { this->m_prev = i_prev; this->m_next = i_next; }
		void set_node_values(int i_source, int i_dest, int i_weight) const { m_edge->set_node_values(i_source, i_dest, i_weight); }
	};
}