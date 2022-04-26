#include "adjacency_list_graph.h"

namespace minimum_spanning_tree
{
	adjacency_list_graph::adjacency_list_graph(const int i_length) : m_VerticesAmount(i_length + 1), m_EdgesAmount(0),
		m_verticesArray(make_empty_adjacency_list_graph()), m_edges_array(nullptr), m_deleted_edge(-1, -1, 0)
	{
	}

	int adjacency_list_graph::add_edge(const int u, const int v, const int i_weight)
	{
		m_EdgesAmount += 1;
		return m_verticesArray[u].add_to_list(u, v, i_weight);
	}

	int adjacency_list_graph::add_edge_no_direction(const int u, const int v, const int i_weight)
	{
		m_EdgesAmount += 2;
		m_verticesArray[v].add_to_list(v, u, i_weight);
		return m_verticesArray[u].add_to_list(u, v, i_weight);
	}

	bool adjacency_list_graph::remove_edge_no_direction(const int u, const int v)
	{
		bool res = false;
		if (is_value_valid(u) && is_value_valid(v))
			res = remove_edge(u, v);
		res = remove_edge(v, u);
		if (res) m_EdgesAmount--;
		return res;
	}

	vertex_list* adjacency_list_graph::make_empty_adjacency_list_graph() const
	{
		const auto array = new vertex_list[m_VerticesAmount];
		for (int i = 1; i < m_VerticesAmount; i++) {
			array[i].make_empty_list();
		}
		return array;
	}

	bool adjacency_list_graph::read_adjacency_list_graph(std::ifstream& i_input_file, int& i_u, int& i_v)
	{
		bool res = true;
		int size, dest, u, v, weight, edges_amount = 0;
		int idx = 0;
		u = v = -1;
		i_input_file >> size;
		if (size < 1)
		{
			res = false;
		}
		m_VerticesAmount = size + 1;
		if (!i_input_file.eof())
			i_input_file >> edges_amount;
		else res = false;
		m_verticesArray = make_empty_adjacency_list_graph();
		m_edges_array = new edge_node * [edges_amount];
		while (res && i_input_file >> u)
		{
			if (is_value_valid(u) && i_input_file >> v && is_value_valid(v))
			{
				if (!i_input_file.eof())
				{
					i_input_file >> weight;
					add_edge_no_direction(u, v, weight);
					m_edges_array[idx++] = new edge_node(u, v, weight);
				}
				else
				{
					i_u = u;
					i_v = v;
				}
			}
			else
				res = false;
		}
		if (idx != edges_amount)
		{
			res = false;
		}
		m_EdgesAmount = edges_amount;
		return res;
	}

	bool adjacency_list_graph::is_connected() const
	{
		const int* distances = run_bfs(1);
		for (int i = 1; i < m_VerticesAmount; i++)
		{
			if (distances[i] == INT_MAX) { return false; }
		}
		return true;
	}

	void adjacency_list_graph::find_bridges_aux(int u, bool visited[], int disc[], int low[], int parent[])
	{
		static int counter = 0;
		visited[u] = true;
		disc[u] = low[u] = ++counter;

		vertex_node* adjacent = m_verticesArray[u].get_head();

		while (adjacent)
		{
			int v = adjacent->m_edge->get_y();

			if (!visited[v])
			{
				parent[v] = u;
				find_bridges_aux(v, visited, disc, low, parent);
				low[u] = std::min(low[u], low[v]);

				if (low[v] > disc[u])
					adjacent->m_edge->mark_as_bridge();
			}
			else if (v != parent[u])
				low[u] = std::min(low[u], disc[v]);
			adjacent = adjacent->m_next;
		}
	}

	void adjacency_list_graph::find_bridges()
	{
		const auto size = m_VerticesAmount;
		const auto visited = new bool[size];
		const auto disc = new int[size];
		const auto low = new int[size];
		const auto parent = new int[size];

		for (int i = 0; i < size; i++)
		{
			parent[i] = -1;
			visited[i] = false;
		}
		for (int i = 1; i < size; i++)
			if (visited[i] == false)
				find_bridges_aux(i, visited, disc, low, parent);
	}

	int* adjacency_list_graph::run_bfs(int i_source) const
	{
		const auto queue = new vertex_list();
		const auto distance_array = new int[m_VerticesAmount + 1];

		distance_array[i_source] = 0;
		for (int i = 1; i <= m_VerticesAmount; i++)
		{
			if (i != i_source) {
				distance_array[i] = INT_MAX;
			}
		}
		const auto source_vertex = new vertex_node(i_source);

		queue->enqueue(source_vertex);

		while (!queue->is_empty())
		{
			const vertex_node* current_vertex = queue->dequeue(); // currentVertex  = u
			const int current_vertex_value = current_vertex->m_edge->get_x();
			vertex_node* current_neighbor = m_verticesArray[current_vertex_value].get_head();

			while (current_neighbor != nullptr) { // currentNeighbor = v 
				if (distance_array[current_neighbor->m_edge->get_y()] == INT_MAX) {
					distance_array[current_neighbor->m_edge->get_y()] = distance_array[current_vertex_value] + 1;
					auto u = m_verticesArray[current_neighbor->m_edge->get_y()].get_head();
					auto cpy = new vertex_node(u->m_edge->get_x());
					queue->enqueue(cpy);
				}
				current_neighbor = current_neighbor->m_next;
			}
			delete current_vertex;
		}
		delete queue;
		return distance_array;
	}

	int adjacency_list_graph::partition(edge_node* i_arr[], const int i_start, const int i_end)
	{
		const edge_node* pivot = i_arr[i_start];
		int count = 0;

		for (int k = i_start + 1; k <= i_end; k++)
		{
			if (i_arr[k]->get_weight() <= pivot->get_weight()) { count++; }
		}

		const int pivot_index = i_start + count;
		swap(i_arr, pivot_index, i_start);
		int i = i_start;
		int j = i_end;

		while (i < pivot_index && j > pivot_index)
		{
			while (i_arr[i]->get_weight() <= pivot->get_weight())
			{
				i++;
			}
			while (i_arr[j]->get_weight() > pivot->get_weight())
			{
				j--;
			}
			if (i < pivot_index && j > pivot_index)
			{
				swap(i_arr, i++, j--);
			}
		}
		return pivot_index;
	}

	void adjacency_list_graph::swap(edge_node* i_arr[], const int a, const int b)
	{
		const auto temp = i_arr[a];
		i_arr[a] = i_arr[b];
		i_arr[b] = temp;
	}

	void adjacency_list_graph::quick_sort(edge_node* i_arr[], const int i_start, const int i_end)
	{
		if (i_start >= i_end)
			return;

		const int pivot_index = partition(i_arr, i_start, i_end);

		quick_sort(i_arr, i_start, pivot_index - 1);
		quick_sort(i_arr, pivot_index + 1, i_end);
	}

	void adjacency_list_graph::print() const
	{
		for (int i = 1; i < m_VerticesAmount; i++)
		{
			m_verticesArray[i].print();
		}
	}

	int adjacency_list_graph::get_edge_weight(const int i_u, const int i_v) const
	{
		if (is_value_valid(is_value_valid(i_u) && is_value_valid(i_v) && is_adjacent(i_u, i_v)))
		{
			return m_verticesArray[i_u].get_node_by_data(i_v)->m_edge->get_weight();
		}
		return -1;
	}

	bool adjacency_list_graph::is_value_valid(const int input_value) const
	{
		bool res = false;
		if (input_value > 0 && input_value <= m_VerticesAmount)
			res = true;
		return res;
	}
}
