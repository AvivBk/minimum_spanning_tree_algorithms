#include "adjacency_list_graph.h"

namespace minimum_spanning_tree
{

	adjacency_list_graph::adjacency_list_graph(int i_length) : m_VerticesAmount(i_length + 1), m_EdgesAmount(0),
	                                                   m_verticesArray(make_empty_adjacency_list_graph()),m_edges_array(nullptr)
	{
	}

	int adjacency_list_graph::add_edge(int u, int v, int i_weight)
	{
		m_EdgesAmount+=1;
		return m_verticesArray[u].add_to_list(u,v, i_weight);
	}
	
	int adjacency_list_graph::add_edge_no_direction(int u, int v, int i_weight)
	{
		m_EdgesAmount += 2;
		m_verticesArray[v].add_to_list(v, u, i_weight);
		return m_verticesArray[u].add_to_list(u, v, i_weight);
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
		int size, dest, u, v, weight, edges_amount;
		int idx = 0;
		i_inputFile >> size;
		if (size < 1)
		{
			res = false;
		}
		m_VerticesAmount = size+1;
		i_inputFile >> edges_amount;
		m_verticesArray = make_empty_adjacency_list_graph();
		m_edges_array = new edge_node*[edges_amount];
		while (res && i_inputFile >> u)
		{
			if (is_value_valid(u) && i_inputFile >> v && is_value_valid(v) && i_inputFile >> weight)
			{
				add_edge_no_direction(u, v, weight);
				m_edges_array[idx++] = new edge_node(u, v, weight);
			}
			else
				res = false;
		}
		//check idx == edges amount
		m_EdgesAmount = edges_amount;
		return res;
	}

	int adjacency_list_graph::partition(edge_node* i_arr[], int i_start, int i_end)
	{
		const edge_node* pivot = i_arr[i_start];
		int count = 0;

		for (int k = i_start + 1; k <= i_end; k++)
		{
			if (i_arr[k]->get_weight() <= pivot->get_weight()){ count++; }
		}

		const int pivot_index = i_start + count;
		swap(i_arr, pivot_index, i_start);

		
		int i = i_start;
		int j = i_end;

		while (i < pivot_index && j > pivot_index) 
		{
			while (i_arr[i]->get_weight() <= pivot->get_weight()) 
			{
				i++;
			}
			while (i_arr[j]->get_weight() > pivot->get_weight()) 
			{
				j--;
			}
			if (i < pivot_index && j > pivot_index) 
			{
				swap(i_arr,i++, j--);
			}
		}
		return pivot_index;
	}

	void adjacency_list_graph::swap(edge_node* i_arr[], int a, int b)
	{
		auto temp = i_arr[a];
		i_arr[a] = i_arr[b];
		i_arr[b] = temp;
	}

	void adjacency_list_graph::quick_sort(edge_node* i_arr[], int i_start, int i_end)
	{
		if (i_start >= i_end)
			return;

		const int pivot_index = partition(i_arr, i_start, i_end);

		quick_sort(i_arr, i_start, pivot_index - 1);
		quick_sort(i_arr, pivot_index + 1, i_end);
	}

	void adjacency_list_graph::print() const
	{

		for (int i = 1; i < m_VerticesAmount; i++)
		{
			m_verticesArray[i].print();
		}
		
	}
	int adjacency_list_graph::get_edge_weight(int i_u, int i_v) const
	{
		if(is_value_valid(is_value_valid(i_u) && is_value_valid(i_v) && is_adjacent(i_u,i_v) ))
		{
			return m_verticesArray[i_u].get_node_by_data(i_v)->m_edge->get_weight();
		}
		return -1;
	}


	bool adjacency_list_graph::is_value_valid(int inputValue) const
	{
		bool res = false;
		if (inputValue > 0 && inputValue <= m_VerticesAmount ) {
			res = true;
		}
		return res;
	}
}
