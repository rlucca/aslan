#pragma once

#include "AllSymbol.hpp"

#include <vector>
using namespace std;

template<typename T>
class TableChain
{
	public:
		typedef typename vector<T*>::iterator iter_t;

		TableChain()
		{
			data.clear();
			marks.clear();
			push();
		}

		virtual ~TableChain()
		{
			for (iter_t it = begin(); it != end(); it++)
			{
				delete *it;
			}
		}

		void push()
		{
			marks.push_back(data.size());
		}

		void pop()
		{
			if (marks.size() > 0)
			{
				data.erase(begin() + lastIndex(), end());
				marks.erase(marks.begin() + marks.size() - 1);
			}
		}

		void add(T *symbol)
		{
			if (marks.size() == 0)
				return ;

			data.push_back(symbol);
		}

		void del(iter_t it)
		{
			data.erase(it);
		}

		iter_t end()
		{
			return data.end();
		}

		iter_t find(unsigned line, const char *lexema, bool recursive = false)
		{
			typedef typename vector<T*>::reverse_iterator riter_t;
			unsigned last = data.size() - lastIndex();
			riter_t rend = (recursive) ? data.rend() : data.rbegin() + last;

			(void) line; (void) lexema;
			for (riter_t it = data.rbegin(); it != rend; it++)
			{
				if (line >= (*it)->firstLine() && line <= (*it)->lastLine()
						&& !strcmp((*it)->lexema(), lexema))
				{
					return (it+1).base();
				}
			}

			return end();
		}

		/* All this is just for test proposes */
		/* { */
		unsigned n_tokens() const
		{ return data.size(); }

		unsigned n_sections() const
		{ return marks.size(); }
		/* } */

	protected:
		vector<T*> data;
		vector<unsigned> marks;

		iter_t begin()
		{
			return data.begin();
		}

		unsigned lastIndex()
		{
			return marks[marks.size() - 1];
		}
};
