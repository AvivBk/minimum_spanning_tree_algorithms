#pragma once
#include "vertex_node.h"
namespace minimum_spanning_tree
{
	class vertex_list
	{

	private:
		vertex_node* m_head;
		vertex_node* m_tail;
		int m_size;

	public:

		// This function creates new Vertex node 
		vertex_node* make_new_node(int vertex, int i_weight_to_next, vertex_node* prev = nullptr, vertex_node* next = nullptr);

		// Ctors and Dtors
		vertex_list();
		~vertex_list() { free_list(); };

		// This function check if the list is empty 
		// This method returns bool value 
		bool is_empty() const { return m_size == 0; };
		// This function free the list 
		void free_list();
		// This function create empty list 
		void make_empty_list();

		// This method add vertex node to list head 
		// This method gets Vertex 
		void add_to_head(vertex_node* i_newNode);
		//This method remove list's tail 
		vertex_node* remove_from_tail();

		//This function checks if vertex in list
		//the method get value ( int ) and returns bool value if exist 
		bool is_in_list(int) const;

		//This method remove from list vertex
		//The method gets value and remove the vertex from list 
		//The method return boolean value 
		bool remove_from_list(int);
		//This method add new vertex node to list
		//The method gets value ( int )
		int add_to_list(int, int);

		// Getters
		vertex_node* get_head() const { return m_head; }
		vertex_node* get_tail() const { return m_tail; }
		int length() const { return m_size; }
		// This method return vertex node
		// the method gets value ( int ) and return vertex
		vertex_node* get_node_by_data(int) const;


		// Setters
		void set_head(vertex_node* newHead) { m_head = newHead; }
		void set_tail(vertex_node* newTail) { m_tail = newTail; }
		void print(int) const;

	};
}
