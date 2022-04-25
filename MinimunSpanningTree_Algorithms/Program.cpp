#include "Program.h"


namespace minimum_spanning_tree
{

	Program::Program(const std::string& i_input_file_name, const std::string& i_output_file_name)
	{
		int size;
		std::ifstream input_file;
		try {
			bool good_input = false;
			input_file.open(i_input_file_name);
			m_graph = new adjacency_list_graph();
			good_input = m_graph->read_adjacency_list_graph(input_file);
			if (!good_input)
			{
				std::cout << "invalid input" << std::endl;
				exit(-1);
			}
		}
		catch (std::exception ex)
		{
			std::cout << "invalid input" << std::endl;
			exit(-1);
		}
		
		m_graph->quick_sort(m_graph->get_edges(), 0, m_graph->get_edges_amount() - 1);
		m_graph->print_edges();
		std::cout << "++++++++++" << std::endl;
		int* parents = minimum_spanning_tree_prim(1);
		for (int i = 1; i < m_graph->length(); i++)
		{
			std::cout << " index " << i << " parent " << parents[i] << std::endl;
		}

		delete[] parents;
	}

	int* Program::initialize_arrays(int* i_parents, bool* i_flags, int i_length)
	{
		int* arr = new int[i_length];
		for (int i = 0; i < i_length; i++)
		{
			arr[i] = INT_MAX;
			i_parents[i] = -1;
			i_flags[i] = false;
		}
		return arr;
	}

	heap_node* Program::initialize_heap_array(int i_size, int i_source)
	{
		auto* array = new heap_node[i_size];

		for (int i = 0; i < i_size-1; i++)
		{
			array[i] = heap_node(i+1);
			if(i+1 == i_source)
			{
				array[i] = heap_node(i+1, 0);
			}
		}
		return array;
	}

	int* Program::minimum_spanning_tree_prim(int i_source) const
	{
		int size = m_graph->length();
		auto queue = new Heap();
		int* parents_array = new int[size];
		bool* in_tree = new bool[size];
		int* min_array = initialize_arrays( parents_array, in_tree,m_graph->length());
		heap_node* array = initialize_heap_array(size, i_source);

		min_array[i_source] = 0;
		parents_array[i_source] = i_source;
		queue->build_heap(array, size-1);

		while (!queue->is_empty())
		{
		
			auto u = queue->delete_min();
			in_tree[u->get_vertex_num()] = true;

			vertex_list* adjacents = m_graph->get_adjacency_list_graph(u->get_vertex_num());
			auto v = adjacents->get_head();
			
			while (v)
			{
				int u_num = v->m_edge->get_x();
				int v_num = v->m_edge->get_y();
				int weight = v->m_edge->get_weight();
				
				
				if (!in_tree[v_num] && weight < min_array[v_num])
				{
					min_array[v_num] = weight;
					parents_array[v_num] = u_num;
					queue->decrease_key(v_num , min_array[v_num]);
					
				}
				v = v->m_next;
				
			}
		}
		delete[] min_array;
		delete[] in_tree;

		return parents_array;
	}

}



