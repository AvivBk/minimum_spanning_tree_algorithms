#pragma once


namespace minimum_spanning_tree
{
	class disjoint_set
	{
	private:
		int* m_ranks_array;
		int* m_parents_array;
		int m_size;
		void make_set() const;
	public:
		explicit disjoint_set(int);
		int find(int);
		void Union(int,int);

		void print() const;
		
	};
}
