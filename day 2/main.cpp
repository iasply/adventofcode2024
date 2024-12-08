#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <chrono>

using namespace std;
// my eyes burn

int testDay2()
{
	ifstream file("inputDay2.txt");

	if (!file)
	{
		return -1;
	}

	string line;
	string token;
	int safe = 0;
	while (getline(file, line))
	{

		bool isSafe = true;
		stack<int> stack{};
		istringstream stream(line);
		while (stream >> token)
		{
			int n = stoi(token);
			if (stack.empty())
			{
				stack.push(n);
			}
			else if (stack.size() == 1)
			{
				int gap = stack.top() - n;
				int absGap = abs(gap);
				if (absGap > 3 || absGap == 0)
				{
					isSafe = false;
					break;
				}
				stack.push(n);
			}
			else
			{
				int firtsTop = stack.top();
				int gap = firtsTop - n;

				int absGap = abs(gap);
				if (absGap > 3 || absGap == 0)
				{
					isSafe = false;
					break;
				}

				stack.pop();

				int secondTop = stack.top();
				int gapOfTops = secondTop - firtsTop;

				if (gapOfTops > 0 && gap > 0)
				{
					stack.push(firtsTop);
					stack.push(n);
				}
				else if (gapOfTops < 0 && gap < 0)
				{
					stack.push(firtsTop);
					stack.push(n);
				}
				else
				{
					isSafe = false;
					break;
				}
			}
		}
		if (isSafe)
		{
			safe++;
		}
	}
	file.close();
	return safe;
}

bool validade(vector<int> *v)
{
	for (int i = 0; i < v->size(); i++)
	{

		if (i == 0)
		{
			continue;
		}
		else if (i == 1)
		{
			int gap = (*v)[i - 1] - (*v)[i];
			int absGap = abs(gap);
			if (absGap > 3 || absGap == 0)
			{
				return false;
			}
		}
		else
		{
			int firtsTop = (*v)[i - 1];
			int gap = firtsTop - (*v)[i];

			int absGap = abs(gap);
			if (absGap > 3 || absGap == 0)
			{
				return false;
			}
			int secondTop = (*v)[i - 2];
			int gapOfTops = secondTop - firtsTop;

			if (!((gapOfTops > 0 && gap > 0) || (gapOfTops < 0 && gap < 0)))
			{
				return false;
			}
		}
	}
	return true;
}

bool branch(vector<int> *v)
{
	if (validade(v))
	{
		return true;
	}

	for (int i = 0; i < v->size(); i++)
	{
		vector<int> newVector;

		for (int j = 0; j < v->size(); j++)
		{
			if (i != j)
			{
				newVector.push_back((*v)[j]);
			}
		}
		if (validade(&newVector))
		{
			return true;
		}
	}

	return false;
}

// ok this is a piece of shit but it's mine
// i really got stuck on this one so i used good (non-performing) and old (go horse) brute force

int testDay2Pt2()
{
	ifstream file("inputDay2.txt");

	if (!file)
	{
		return -1;
	}

	string line;
	string token;
	int safe = 0;
	while (getline(file, line))
	{
		vector<int> v{};
		bool isSafe = true;
		bool errorMargin = false;
		istringstream stream(line);
		while (stream >> token)
		{
			int n = stoi(token);
			v.push_back(n);
		}

		if (branch(&v))
		{
			safe++;
		}
	}
	file.close();
	return safe;
}


//In the first impl i got like 1.5 ms on avg
//In the second one, it’s like 3.2 ms (brute force)
int main()
{
	auto start = chrono::high_resolution_clock::now();
	int i = testDay2();
	auto end = chrono::high_resolution_clock::now();

	auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
	cout << "Safe " << i << endl;
	cout << "Time taken  " << duration.count() << " nanoseconds" << endl;

	start = chrono::high_resolution_clock::now();
	i = testDay2Pt2();
	end = chrono::high_resolution_clock::now();

	duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
	cout << "Safe " << i << endl;
	cout << "Time taken  " << duration.count() << " nanoseconds" << endl;

	return 0;
}