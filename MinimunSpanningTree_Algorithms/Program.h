#pragma once
#include "adjacency_list_graph.h"
#include "Heap.h"
#include "disjoint_set.h"
namespace minimum_spanning_tree
{
	class Program
	{
		adjacency_list_graph* m_graph;
		vertex_node** m_edges_array;
		

	public:
		//Ctor and Dtor
		Program(const std::string&, const std::string&);
		~Program() { delete m_graph; }
		int* minimum_spanning_tree_prim(int i_source) const;
		static heap_node* initialize_heap_array( int i_size, int i_source);
		static int* initialize_arrays(int* i_parents, bool* i_flags, int i_length);

			
	};
}
