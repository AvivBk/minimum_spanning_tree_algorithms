#pragma once
#include <fstream>
#include "vertex_list.h"

namespace minimum_spanning_tree
{
	class adjacency_list_graph
	{
	private:
		int m_VerticesAmount;
		int m_EdgesAmount;
		vertex_list* m_verticesArray;
		edge_node** m_edges_array;
		edge_node m_deleted_edge;

	public:
		explicit adjacency_list_graph(int);
		//ctor dtor
		~adjacency_list_graph() { delete[] m_verticesArray; delete[] m_edges_array; }
		adjacency_list_graph() :m_VerticesAmount(0), m_EdgesAmount(0), m_verticesArray(nullptr), m_edges_array(nullptr) {}

		// This method create empty adjacent list 
		vertex_list* make_empty_adjacency_list_graph() const;

		//init by input
		bool read_adjacency_list_graph(std::ifstream&, int&, int&);

		//getters
		vertex_list* get_adjacency_list_graph(const int i_vertex) const { return &(m_verticesArray[i_vertex]); }
		int get_edge_weight(int i_u, int i_v) const;
		int length() const { return m_VerticesAmount; }
		int get_edges_amount() const { return m_EdgesAmount; }
		int get_vertex_degree(const int i_idx) const { if (is_value_valid(i_idx))return m_verticesArray[i_idx].length(); return 0; }
		vertex_list* get_vertices_array() const { return m_verticesArray; }
		edge_node** get_edges() const { return m_edges_array; }
		edge_node get_deleted_edge() const { return m_deleted_edge; }

		void set_deleted_edge(const int i_x, const int i_y) { m_deleted_edge.set_node_xy(i_x, i_y); }

		bool is_adjacent(const int u, const int v) const { return m_verticesArray[u].is_in_list(v); }
		bool is_value_valid(int) const;
		int is_empty() const { return m_VerticesAmount == 0; }

		// add and remove
		int add_edge(int, int, int);
		int add_edge_no_direction(int u, int v, int i_weight);
		bool remove_edge(const int u, const int v) const { return m_verticesArray[u].remove_from_list(v); }
		bool remove_edge_no_direction(int u, int v);



		void find_bridges_aux(int u, bool visited[], int disc[], int low[], int parent[]);
		void find_bridges();

		bool is_connected() const;
		int* run_bfs(int) const;

		static int partition(edge_node* i_arr[], int i_start, int i_end);
		static void swap(edge_node* i_arr[], int a, int b);
		static void quick_sort(edge_node* i_arr[], int i_start, int i_end);

		void print() const;
		void print_edges() const { for (int i = 0; i < m_EdgesAmount; i++) m_edges_array[i]->print(); }
	};
}
