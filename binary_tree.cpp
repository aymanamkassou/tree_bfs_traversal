#include<iostream>
#include<vector>
#include<map>

using namespace std;

class binary_tree
{
private:
	map<int, string> tree;

public:

	binary_tree(vector<string> strings)
	{
		for (string str : strings)
		{
			insert_string(str);
		}
	}

	binary_tree(string string)
	{
		tree[0] = string;
	}

	int size() const
	{
		return tree.size();
	}

	int left_child_index(int index) 
	{
		return (index * 2) + 1;
	}

	int right_child_index(int index)
	{
		return (index * 2) + 2;
	}

	string string_at_index(const int index) const
	{
		if (tree.count(index) == 0)
		{
			return "\0";
		}
		return tree.at(index);
	}

	bool is_null_at_index(const int index) const
	{
		if (tree.count(index) == 0)
		{
			return true;
		}
		return false;
	}

	void insert_string(const string& str)
	{	
		int insertion_index = 0;
		char choice;
		bool inserted = false;

		while (!is_null_at_index(insertion_index))
		{
			std::cout << "Would you link to insert " << str << " left (l or L) of " << tree[insertion_index] << " or right (r or R)?\n";
			std::cin >> choice;
			switch (choice)
			{
				case 'l':
				case 'L':
					insertion_index = left_child_index(insertion_index);
					break;
				case 'r':
				case 'R':
					insertion_index = right_child_index(insertion_index);
					break;
				default:
					std::cout << "Invalid choice\n";
					continue;
			}

			if (is_null_at_index(insertion_index))
			{
				tree.insert({insertion_index, str});
				inserted = true;
				break;
			}
		}

		if (!inserted)
		{
			std::cout << "Tree is full\n";
		}
			
	}

				
			
	void bfs_traversal()
	{
		for (auto iter = tree.begin(); iter != tree.end(); iter++)
		{
			std::cout << iter->second << " ";
		}
		std::cout << "\n";
	}



};


int main(int argc, char **argv)
{
	binary_tree hierarchical_map_tree("Africa");
	hierarchical_map_tree.insert_string("Morocco");
	hierarchical_map_tree.insert_string("Grand Casablanca");
	hierarchical_map_tree.insert_string("Benslimane");
	hierarchical_map_tree.insert_string("Mohammedia");
	hierarchical_map_tree.insert_string("Algeria");
	hierarchical_map_tree.insert_string("Constantine");
	hierarchical_map_tree.bfs_traversal();
	return 0;
}

	
