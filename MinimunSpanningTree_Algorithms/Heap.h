#pragma once
#include "heap_node.h"

namespace minimum_spanning_tree
{
	class Heap
	{
	private: 
		heap_node** m_heap;
		int m_max_size;
		int m_heap_size;
		bool m_allocated;

		static int Left(int i_node) { return (2 * i_node + 1); } //returns index to left
		static int Right(int i_node) { return (2 * i_node + 2); } //returns index to right
		static int Parent(int i_node) { return (i_node - 1) / 2; } //returns index to parent	
		void fix_heap(int i_node); //the algorithm fix heap as learned in class
	public:
		heap_node** initialize_array_for_heap(int i_source_idx, int i_size);
		
		//CTOR
		Heap();
		//allocates memory for heap
		void allocate_heap(int maxSize);

		//DTOR

		~Heap();

		//a method that prepears the forest before huffman code
		void build_heap(heap_node** , int );
		//inserts to a huffman tree
		void insert(heap_node*& );
		//swaps between two items from an array by indexes a and b
		void swap(int  a, int b) const;
		//returns the minimum from the heap
		heap_node* min() const { return m_heap[0]; }
		//deletes the minimum from the heap and deletes it
		heap_node* delete_min();
		//prints the heap
		void print_heap() const;


		heap_node** get_heap_array() const { return m_heap; }
		int length() const { return m_heap_size; }


		void decrease_key(int, int) const;

	};
}
