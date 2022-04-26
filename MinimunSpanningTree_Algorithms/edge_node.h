#pragma once
#include <iostream>
namespace minimum_spanning_tree
{
	class edge_node
	{
	public:
		int m_x;
		int m_y;
		int m_weight;
		bool m_is_edge;
	public:
		edge_node() :m_x(0), m_y(0), m_weight(0), m_is_edge(false) {}
		edge_node(const int i_x, const int i_y, const  int i_weight) :
			m_x(i_x), m_y(i_y), m_weight(i_weight), m_is_edge(false) {  }
		explicit edge_node(const int i_x) : m_x(i_x), m_y(0), m_weight(0), m_is_edge(false) {}

		int get_x() const { return m_x; }
		int get_y() const { return m_y; }
		int get_weight() const { return m_weight; }
		bool is_edge_bridge() const { return m_is_edge; }

		void set_node_xy(const int i_x, const int i_y) { m_x = i_x; m_y = i_y; }
		void set_node_values(const int i_x, const int i_y, const int i_weight) { m_x = i_x; m_y = i_y; m_weight = i_weight; }
		void mark_as_bridge() { m_is_edge = true; }

		void print() const
		{
			std::cout << "(" << m_x << "," << m_y << ")" << std::endl;
			std::cout << "weight : " << m_weight << std::endl;
			if (m_is_edge)
				std::cout << "is bridge ! : " << std::endl;
		}
	};
}
