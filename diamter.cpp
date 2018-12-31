#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
int array1[100][100];
int no_of_colns, no_of_rows;
int invalid = 0;
string filename;
int Path[101];
int x = 0;//counter for Path
int visited[101] = { 0 };
int predecessor[101] = { -1 };


void readfile()
{
	std::vector<std::vector<int> >     data;
	std::ifstream	file(filename);
	std::string   line;
	// Read one line at a time into the variable line:
	while (std::getline(file, line))
	{
		std::vector<int>   lineData;
		std::stringstream  lineStream(line);

		int value;
		// Read an integer at a time from the line
		while (lineStream >> value)
		{
			// Add the integers from a line to a 1D array (vector)
			lineData.push_back(value);
		}
		//	cout << lineData.size() << "\t";
		// When all the integers have been read, add the 1D array into a 2D array (as one line in the 2D array)
		data.push_back(lineData);
	}

	//system("pause");

	for (int i = 0, m = 0; i < (data.size()); i++, m++)
	{
		for (int j = 0, n = 0; j < (data[i].size()); j++, n++)
		{
			//cout << data[i][j] << " ";
			array1[i][j] = data[i][j];
			if (n > no_of_colns) {
				no_of_colns = n;
			}
		}

		no_of_rows = m;
		//printf("\n");

	}
	no_of_rows += 1;
	no_of_colns += 1;
	printf("R*C=%d*%d\n", no_of_rows, no_of_colns);
	/*	if (no_of_rows != (data.size()))
	{

	printf("size varies coln= %d,size=%d\n",no_of_rows, data.size());
	}*/
	for (int i = 0; i < data.size(); i++)
	{
		if (no_of_colns != (data[i].size()))
		{
			//Set Invalid Input like invalid=1 with reason."
			invalid = 1;
			//printf("at i= %d size varies coln= %d varies\n", i,no_of_colns);
		}
		for (int j = 0; j < data[i].size(); j++)
		{
			cout << array1[i][j] << "\t";
		}
		cout << "\n";
	}

	if (invalid)
	{
		cout << "Invalid Matrix has Empty matrix element\n";
		system("pause");
		exit(1);
	}
	cout << "Matrix has valid entries with out any empty\n";


}

void InitPath()
{
	for (int i = 0; i < 100 + 1; i++)
		Path[i] = -1;
}
int CheckSquare()
{
	printf("CheckSquare-->R*C=%d*%d\n", no_of_rows, no_of_colns);
	if (no_of_rows == no_of_colns)
	{
		cout << "\n Its a Square Matrix";
	}
	else {
		cout << "\n It is not a Square Matrix";
		system("pause");
		exit(1);
	}
}
void CheckBits()
{
	int temp = 0;
	for (int i = 0; i < no_of_rows; i++)
	{
		for (int j = 0; j < no_of_colns; j++)
		{
			if (array1[i][j] != 0 && array1[i][j] != 1)
			{
				temp = 1;
				cout << "\n Error Has invalid bit entry " << array1[i][j] << "at " << i << j << " location\n";
			}

		}
	}
	if (temp == 1)
	{
		cout << "Invalid Graph\n";
		system("pause");
		exit(1);
	}
	else
		cout << "\nGraph has only Bit Valued Entries";

}




int CheckSelfLoop()
{
	int temp = 0;
	for (int i = 0; i < no_of_rows; i++)
	{
		for (int j = 0; j < no_of_colns; j++)
		{
			if (i == j)
			{
				if (array1[i][j] != 0)
				{
					temp = 1;
					cout << "\n Error Has Self Loop at" << i << j << "location\n";
				}
			}
		}
	}
	if (temp == 1)
	{
		cout << "Invalid Graph\n";
		system("pause");
		exit(1);
	}
	else
		cout << "\nGraph has no Self Loops";

}
void CheckSymmetric()
{
	int temp = 0;
	for (int i = 0; i < no_of_rows; i++)
	{
		for (int j = 0; j < no_of_rows; j++)
		{
			if (array1[i][j] != array1[j][i])
			{
				if (j > i) {
					temp = 1;
					cout << "\nNot Symmetric at " << i << j << "and at " << j << i;
				}
			}
		}
	}
	if (temp != 1)
	{
		cout << "\nSymmetric Graph";

	}
	else
	{
		cout << "\nUnsymmetric Graph";
		system("pause");
		exit(1);
	}
}

int countPath()
{
	int temp_var = 0;
	int count = 0;
	printf("\n");
	for (int i = 0; i < no_of_rows; i++)

	{
		if (Path[i] != -1)
			count++;
		else if (Path[i] == -1)//nodes not visited means unconnected
		{
			temp_var = 1;
			cout << i << " ";
		}
	}
	if (temp_var == 1)
	{
		cout << " unconnected with nodes ";
		for (int i = 0; i < no_of_rows; i++)//becz the simple path cant have more than no of nodes in graph
		{
			if (Path[i] != -1)
				cout << i << " ";
		}
		cout << "\nGiven Graph is not connected graph\n";
		system("pause");
		exit(1);

	}
	return count;

}

void printPath(int k)
{
	int len = 0;
	switch (k)
	{
	case 0:printf("\nCycle Exsists in Path :");
		for (int i = 0; i < no_of_rows + 1; i++) //no_of_rows+1 for cycle case
		{
			if (Path[i] != -1)
			{
				printf("%d ", Path[i]);
			}
		}
		cout << "\nGiven Graph is not acyclic\n";
		break;
	case 1:

		printf("\nLength is %d for this Undirected Connected Acyclic Graph\n", (countPath() - 1)); //no of nodes-1 to track edges travelled
		printf("Diameter:\n");
		for (int i = 0; i < no_of_rows; i++)//becz the simple path cant have more than no of nodes in graph
		{
			if (Path[i] != -1)
				printf("%d ", Path[i]);
		}
		break;
	}
}
void CheckDFS(int i)
{
	int j;

	//printf("\n%d \t %d", i, predecessor[i]);
	visited[i] = 1;
	Path[x] = i;
	for (j = 0; j < no_of_colns; j++)
	{
		if (visited[j] == 1 && (((predecessor[j]) != i) && (predecessor[i] != j)) && array1[i][j] == 1)
		{
			//printf("\nPresence of cycle at %d %d\n",i,j);
			x++;
			Path[x] = j;
			printPath(0);
			system("pause");
			exit(1);
		}
		if (!visited[j] && array1[i][j] == 1)
		{
			//printf("\n Inside Node :%d \t Pred :%d", j, i);
			predecessor[j] = i;
			x++;
			CheckDFS(j);
		}
	}


}


int main(int argc, char **argv)
{
	filename = argv[1];
	std::cout << filename << "\n";
	// a vector grows dynamically as required when we get more data.
	readfile();
	InitPath();
	CheckSquare();
	CheckBits();
	CheckSelfLoop();
	CheckSymmetric();
	predecessor[0] = 0;
	CheckDFS(0);//root node
	printPath(1);//when cycle not present
	system("pause");
}