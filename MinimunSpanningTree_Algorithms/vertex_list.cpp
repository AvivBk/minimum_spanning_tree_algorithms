#include "vertex_list.h"

#include <iostream>
#include <ostream>

namespace minimum_spanning_tree
{
	vertex_list::vertex_list() : m_head(nullptr), m_tail(nullptr), m_size(0)
	{

	}

	vertex_node* vertex_list::make_new_node(int vertex, int dest, int i_weight_to_next, vertex_node* prev, vertex_node* next)
	{
		vertex_node* newNode = new vertex_node(vertex, dest, i_weight_to_next);
		newNode->set_node_ptr(prev, next);

		return newNode;
	}

	void vertex_list::make_empty_list()
	{
		m_head = m_tail = nullptr;
		m_size = 0;
	}

	void vertex_list::add_to_head(vertex_node* i_newNode)
	{
		i_newNode->m_next = m_head;
		i_newNode->m_prev = nullptr;
		if (!is_empty()) {
			m_head->m_prev = i_newNode;
		}
		if (m_tail == nullptr) {
			m_tail = i_newNode;
		}
		m_head = i_newNode;
		m_size++;
	}

	vertex_node* vertex_list::remove_from_tail()
	{
		vertex_node* node = nullptr;
		if (m_head == nullptr)
		{
			return node;
		}
		else
		{
			node = m_tail;

			if (m_head != m_tail)
			{
				m_tail = m_tail->m_prev;
				m_tail->m_next = nullptr;
			}

			else
			{
				m_head = m_tail = nullptr;
			}
			m_size--;
			return node;
		}
	}
	vertex_node* vertex_list::get_node_by_data(int i_vertexNum) const
	{
		vertex_node* res = nullptr;
		vertex_node* curr = m_head;
		while (curr != nullptr) {
			if (curr->m_edge->get_y() == i_vertexNum)
			{
				res = curr;
				break;
			}
			curr = curr->m_next;
		}
		return res;
	}

	bool vertex_list::is_in_list(int i_vertexNum) const
	{
		bool result = false;
		vertex_node* temp = get_node_by_data(i_vertexNum);
		if (temp != nullptr)
			result = true;
		return result;
	}

	bool vertex_list::remove_from_list(int i_vertexNum)
	{
		bool res = false;
		vertex_node* temp = get_node_by_data(i_vertexNum);
		if (temp == m_tail) {
			temp = remove_from_tail();
			res = true;
		}
		else if (temp == m_head)
		{
			m_head = m_head->m_next;
			m_head->m_prev = nullptr;
			res = true;
		}
		else {
			if (temp->m_next != nullptr)
			{
				temp->m_next->m_prev = temp->m_prev;
			}
			temp->m_prev->m_next = temp->m_next;
			res = true;
		}
		m_size--;
		delete temp;
		return res;
	}

	int vertex_list::add_to_list(int i_vertexNum, int i_dest, int i_weight_to_next)
	{
		constexpr int res = 1;
		vertex_node* newNode = make_new_node(i_vertexNum, i_dest, i_weight_to_next);
		add_to_head(newNode);
		return res;
	}
	int vertex_list::add_to_list(vertex_node* i_to_add)
	{
		constexpr int res = 1;
		add_to_head(i_to_add);
		return res;
	}

	void vertex_list::print() const
	{
		vertex_node* current = m_head;

		while (current != nullptr)
		{
			current->m_edge->print();
			current = current->m_next;
		}
	}

	void vertex_list::free_list()
	{
		vertex_node* node;
		while (m_head != nullptr) {
			node = m_head;
			m_head = node->m_next;


			delete node;
		}
		m_size = 0;
		m_head = m_tail = nullptr;
	}
}
