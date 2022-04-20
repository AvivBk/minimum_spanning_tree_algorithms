#pragma once
#include "adjacency_list_graph.h"
#include "Heap.h"
#include "disjoint_set.h"
namespace minimum_spanning_tree
{
	class Program
	{
		adjacency_list_graph* m_graph;
		Heap* m_heap;
		

	public:
		//Ctors and Dtors
		Program(std::string, std::string);
		~Program() { delete m_graph; delete m_heap; }
		
	};
}
