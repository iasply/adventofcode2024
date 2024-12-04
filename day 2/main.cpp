#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
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

int main()
{
	auto start = chrono::high_resolution_clock::now();
	int i = testDay2();
	auto end = chrono::high_resolution_clock::now();

	auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
	cout << "Safe " << i << endl;
	cout << "Time taken  " << duration.count() << " milliseconds" << endl;

	return 0;
}