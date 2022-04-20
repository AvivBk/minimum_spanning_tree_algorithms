#include "Program.h"


namespace minimum_spanning_tree
{

	Program::Program(std::string i_inputFileName, std::string i_outputFileName)
	{
	
		bool goodInput = false;
	
		int size;
		std::ifstream inputFile;
		try {
			inputFile.open(i_inputFileName);
			m_graph = new adjacency_list_graph();
			goodInput = m_graph->read_adjacency_list_graph(inputFile);
			if (!goodInput)
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
		m_graph->print();
		m_heap = new Heap();
		std::cout << std::endl;
		heap_node** array = m_heap->initialize_array_for_heap(2, m_graph->length());
		m_heap->build_heap(array, m_graph->length());
		
		m_heap->print_heap();
		std::cout << std::endl;
		m_heap->decrease_key(3, 6);
		
		std::cout << std::endl;
		m_heap->print_heap();
		m_heap->decrease_key(3, 5);
		m_heap->print_heap();
		auto min = m_heap->delete_min();
		std::cout << min->m_data << min->m_key << std::endl;

		/*auto sets = new disjoint_set(m_graph->length() - 1);
		sets->print();
		std::cout << "====================" << std::endl;
		sets->Union(1, 2);
		sets->Union(3, 5);
		sets->Union(6, 3);
		sets->Union(5, 2);
		sets->print();
		std::cout << "====================" << std::endl;
		if(sets->find(1) == sets->find(5))
		{
			std::cout << "TRUE" << std::endl;
		}
		else
		{
			std::cout << "false" << std::endl;
		}*/
	}
	
}
