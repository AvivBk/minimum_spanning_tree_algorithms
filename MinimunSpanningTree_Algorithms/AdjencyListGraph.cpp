#include "adjacency_list_graph.h"

namespace minimum_spanning_tree
{

	adjacency_list_graph::adjacency_list_graph(int i_length) : m_VerticesAmount(i_length + 1), m_EdgesAmount(0),
	                                                   m_verticesArray(make_empty_adjacency_list_graph())
	{
	}

	int adjacency_list_graph::add_edge(int u, int v, int i_weight)
	{
		if ((u < 1) || (v < 1) || (u > m_VerticesAmount - 1) || (v > m_VerticesAmount - 1))
			return 0;
		m_EdgesAmount++;
		return m_verticesArray[u].add_to_list(u,v, i_weight);
	}

	vertex_list* adjacency_list_graph::make_empty_adjacency_list_graph() const
	{
		vertex_list* Array = new vertex_list[m_VerticesAmount];
		for (int i = 1; i < m_VerticesAmount; i++) {
			Array[i].make_empty_list();
		}
		return Array;
	}

	bool adjacency_list_graph::read_adjacency_list_graph(std::ifstream& i_inputFile)
	{
		bool res = true;
		int size, dest, u, v, weight;

		i_inputFile >> size;
		if (size < 1) {
			res = false;
		}
		m_VerticesAmount = size + 1;
		m_verticesArray = make_empty_adjacency_list_graph();

		while (res && i_inputFile >> u)
		{
			if (is_value_valid(u) && i_inputFile >> v && is_value_valid(v) && i_inputFile >> weight)
				add_edge(u, v,weight);

			else
				res = false;
		}
		
		return res;
	}

	void adjacency_list_graph::print() const
	{
		for (int i = 1; i < m_VerticesAmount; i++)
		{
			m_verticesArray[i].print(i);
		}
	}
	int adjacency_list_graph::get_edge_weight(int i_u, int i_v) const
	{
		if(is_value_valid(is_value_valid(i_u) && is_value_valid(i_v) && is_adjacent(i_u,i_v) ))
		{
			return m_verticesArray[i_u].get_node_by_data(i_v)->m_edge->get_weight();
		}
	}


	bool adjacency_list_graph::is_value_valid(int inputValue) const
	{
		bool res = false;
		if (inputValue > 0 && inputValue <= m_VerticesAmount - 1) {
			res = true;
		}
		return res;
	}
}
