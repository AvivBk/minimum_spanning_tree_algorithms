#pragma once
#include <iostream>


namespace minimum_spanning_tree
{
	class edge_node
	{
	private:
		int m_x;
		int m_y;
		int m_weight;
	public:
		edge_node(const int i_x, const int i_y , const  int i_weight) : m_x(i_x), m_y(i_y), m_weight(i_weight) {  }
		edge_node(const int i_x) : m_x(i_x), m_y(0), m_weight(0) {}


		int get_x() const { return m_x; }
		int get_y() const { return m_y; }
		int get_weight() const { return m_weight; }
		

		void set_node_values(const int i_x,const int i_y,const int i_weight) { m_x = i_x; m_y = i_y; m_weight = i_weight; }
		void print() const
		{
			std::cout << "(" << m_x << "," << m_y << ")" << std::endl;
			std::cout << "weight : " << m_weight << std::endl;
		}
	};
}
