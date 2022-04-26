#include "Program.h"

namespace minimum_spanning_tree
{
	Program::Program(const std::string& i_input_file_name, const std::string& i_output_file_name)
	{
		int u = -1, v = -1;
		try
		{
			std::ifstream input_file;
			bool good_input = false;
			input_file.open(i_input_file_name);
			m_graph = new adjacency_list_graph();
			good_input = m_graph->read_adjacency_list_graph(input_file, u, v);
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

		if (!m_graph->is_connected())
		{
			std::cout << "invalid input" << std::endl;
			exit(-1);
		}

		run_program(u, v);
	}

	void Program::run_program(int i_u, int i_v) const
	{
		// kruskal p1
		std::cout << "===================" << std::endl;
		std::cout << " kruskal output : " << std::endl;
		m_graph->quick_sort(m_graph->get_edges(), 0, m_graph->get_edges_amount() - 1);
		const auto list = minimum_spanning_tree_kruskal();
		list->print();
		std::cout << "===================" << std::endl;

		// prim 
		const int* parents = minimum_spanning_tree_prim(1);
		std::cout << "===================" << std::endl;
		std::cout << " prim output : : " << std::endl;
		for (int i = 1; i < m_graph->length(); i++)
		{
			std::cout << " index " << i << " parent " << parents[i] << std::endl;
		}
		std::cout << "===================" << std::endl;
		std::cout << "===================" << std::endl;

		// kruskal p2
		const bool res = m_graph->remove_edge_no_direction(i_u, i_v);
		if (res)
		{
			std::cout << "current graph ,deleted : (" << i_u << " , " << i_v << ")" << std::endl;
			m_graph->print();
			std::cout << "===================" << std::endl;

			if (!m_graph->is_connected())
				std::cout << "supplied edge was a bridge => new graph is not connected " << std::endl;
			else
			{
				std::cout << "===================" << std::endl;
				std::cout << " kruskal(after deleting)  output : " << std::endl;
				m_graph->set_deleted_edge(i_u, i_v);
				const auto list2 = minimum_spanning_tree_kruskal();
				list2->print();
				std::cout << "===================" << std::endl;
			}
		}
		else
		{
			std::cout << "invalid input (supplied wrong edge to delete)" << std::endl;
		}
		delete[] parents;
		delete list;
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
		for (int i = 0; i < i_size - 1; i++)
		{
			array[i] = heap_node(i + 1);
			if (i + 1 == i_source)
			{
				array[i] = heap_node(i + 1, 0);
			}
		}
		return array;
	}

	int* Program::minimum_spanning_tree_prim(int i_source) const
	{
		const int size = m_graph->length();
		const auto queue = new Heap();
		auto parents_array = new int[size];
		auto in_tree = new bool[size];
		int* min_array = initialize_arrays(parents_array, in_tree, m_graph->length());
		heap_node* array = initialize_heap_array(size, i_source);

		min_array[i_source] = 0;
		parents_array[i_source] = i_source;
		queue->build_heap(array, size - 1);

		while (!queue->is_empty())
		{
			const auto u = queue->delete_min();
			in_tree[u->get_vertex_num()] = true;

			const vertex_list* adjacent = m_graph->get_adjacency_list_graph(u->get_vertex_num());
			auto v = adjacent->get_head();

			while (v)
			{
				const int u_num = v->m_edge->get_x();
				const int v_num = v->m_edge->get_y();
				const int weight = v->m_edge->get_weight();

				if (!in_tree[v_num] && weight < min_array[v_num])
				{
					min_array[v_num] = weight;
					parents_array[v_num] = u_num;
					queue->decrease_key(v_num, min_array[v_num]);
				}
				v = v->m_next;
			}
		}
		delete[] min_array;
		delete[] in_tree;

		return parents_array;
	}
	adjacency_list_graph* Program::minimum_spanning_tree_kruskal() const
	{
		const edge_node deleted_edge = m_graph->get_deleted_edge();
		const int size = m_graph->length();
		const auto forest = new adjacency_list_graph(size);
		disjoint_set union_find(size);
		const auto sorted_edges = m_graph->get_edges();

		for (int i = 0; i < m_graph->get_edges_amount(); i++)
		{
			if (deleted_edge.m_x < 1 || !is_edges_equal(deleted_edge, *sorted_edges[i]))
			{
				const int u = sorted_edges[i]->get_x();
				const int v = sorted_edges[i]->get_y();

				const int u_parent = union_find.find(u);
				const int v_parent = union_find.find(v);
				if (u_parent != v_parent)
				{
					forest->add_edge(u, v, sorted_edges[i]->get_weight());
					union_find.Union(u_parent, v_parent);
				}
			}
		}
		return forest;
	}

	bool Program::is_edges_equal(const edge_node i_e1, const edge_node i_e2)
	{
		return
			((i_e1.get_x() == i_e2.get_x() && i_e1.get_y() == i_e2.get_y())
				|| (i_e1.get_x() == i_e2.get_y() && i_e1.get_y() == i_e2.get_x()));
	}

}



