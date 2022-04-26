#pragma once
#include "adjacency_list_graph.h"
#include "Heap.h"
#include "disjoint_set.h"

namespace minimum_spanning_tree
{
	class Program
	{
		adjacency_list_graph* m_graph;
	public:
		//Ctor and Dtor
		Program(const std::string&, const std::string&);
		~Program() { delete m_graph; }
		void run_program(int, int) const;
		int* minimum_spanning_tree_prim(int i_source) const;
		adjacency_list_graph* minimum_spanning_tree_kruskal() const;
		static heap_node* initialize_heap_array( int i_size, int i_source);
		static int* initialize_arrays(int* i_parents, bool* i_flags, int i_length);
		static bool is_edges_equal(const edge_node, const edge_node);
	};
}
