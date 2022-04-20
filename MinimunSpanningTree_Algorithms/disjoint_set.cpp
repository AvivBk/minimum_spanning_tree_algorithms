#include "disjoint_set.h"

#include <iostream>
#include <string>

namespace minimum_spanning_tree
{
	disjoint_set::disjoint_set(const int i_size): m_size(i_size + 1)
	{
		m_ranks_array = new int[m_size];
		m_parents_array = new int[m_size];
		make_set();
	}
	void disjoint_set::make_set() const
	{
		for (int i = 0; i < m_size; i++) { m_parents_array[i] = i; m_ranks_array[i] = 1; }
	}

	int disjoint_set::find(const int i_x)
	{
		if (m_parents_array[i_x] != i_x) {
			m_parents_array[i_x] = find(m_parents_array[i_x]);
		}
		return m_parents_array[i_x];
	}
	void disjoint_set::Union(int i_x, int i_y)
	{
		const int x_rep = find(i_x);
		const int y_rep = find(i_y);

		if (x_rep == y_rep)
			return;

		
		if (m_ranks_array[x_rep] < m_ranks_array[y_rep])
		{
			m_parents_array[x_rep] = y_rep;
		}
		else if (m_ranks_array[x_rep] > m_ranks_array[y_rep])
		{
			m_parents_array[y_rep] = x_rep;
		}
		else 
		{
			m_parents_array[y_rep] = x_rep;
			m_ranks_array[x_rep] = m_ranks_array[x_rep] + 1;
		}
	}
	void disjoint_set::print() const
	{
		for(int i = 0; i < m_size; i++)
		{
			std::cout << "====================" << std::endl;
			std::cout << "index : " + std::to_string(i) << std::endl;
			std::cout << "parent : " << m_parents_array[i] << std::endl;
			std::cout << "rank : " << m_ranks_array[i] << std::endl;
			if(m_parents_array[i] == i)
			{
				std::cout << "Rep" << std::endl;
			}
			std::cout << "====================" << std::endl;
		}
	}

}
