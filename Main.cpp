#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Node.h"
using namespace std;

//Checks if the given string exists in the given vector.
bool ExistsInVector(string, vector<Node*>);

/** First prints the graph. Shows each node and which node it links to.
	Then it shows a table which states each nodes' usability status. */
void PrintGraph(vector<Node*>);

/** In this assignment, instead of deleting nodes I have given all nodes a boolean variable
	and if they are active, it means they exist. When the boolean variable is set to false,
	the node is not shown in any graphs and also usability table is updated according to it.
	This method is more memory consuming but could give the programmer a chance to implement re-enabling of nodes.
*/

int main()
{
	
	stringstream *ss;	
	string line;
	ifstream myFile;
	string fileName;
	
	string firstWord;
	string secondWord;
	
	
	myFile.open("resource.txt");
	
	
	
	vector<Node*> nodeList;
	Node *temp;
	Node *temp2;
	
	//Continue only if file is open
	if(myFile.is_open())
	{
		//loop while line is not NULL
		while( getline(myFile, line) )
		{
			//Creating a new string stream which will help in spliting the line from the white space
			ss = new stringstream(line);
			
			/**	firstWord is the first word in the line and secondWord is the second word in the line
				so if the line is "handgun bullets" then firstWord = "handgun"
												     	secondWord = "bullets"
		    */
			*ss >> firstWord;
			*ss >> secondWord;
			
			/** Checking if the second word exists in the nodeList. 
			    If it doesn't exist, we'll create a new node and add it to the list of nodes 
			*/
			   
			if(ExistsInVector(secondWord, nodeList) == false)
			{
				temp = new Node(secondWord);
				nodeList.push_back(temp);
			}			
			/** If it exists, we'll loop through the nodeList and find the node. After we find it, we'll point temp to that node.
			    This will be used later on where we add that node which "temp" variable is pointing to the adjacency list 
			*/			
			else
			{
				for(int i=0; i<nodeList.size(); i++)
				{
					if(secondWord == nodeList[i]->GetName())
					{
						temp = nodeList[i];
					}
				}
			}
			/** If the first word doesn't exist in the nodeList, create a new node,
				add it to the list of nodes and then add the second word into the adjacency list of the first word.
				To do this we use the variable "temp" which was initialized in the above if-else statements
			*/
			if(ExistsInVector(firstWord, nodeList) == false)
			{
				temp2 = new Node(firstWord);
				nodeList.push_back(temp2);
				temp2->AddNewNode(temp);
			}
			/** If the first word exists, find it in the nodeList and add the second word to its adjacency list.
			*/
			else
			{
				for(int i=0; i<nodeList.size(); i++)
				{
					if(firstWord == nodeList[i]->GetName())
					{
						nodeList[i]->AddNewNode(temp);
					}
				}
			}
			//free the memory
			delete ss;
			
		}
		myFile.close();
	}
	//If file is not open, then exit the program!
	else
	{
		cout<<"recourse.txt file not found!\n";
		cin.ignore();
		exit(1);
	}
	
	/** Now the creation of the list of nodes and their adjacency lists are done and we can continue
		with the next step which is deleting nodes and checking usability.
	*/
	cout<<endl<<endl;
	//Prints the graph showing each node and which node they link to. Then shows another list where it states each nodes usability.	
	PrintGraph(nodeList);
	cout<<endl;
	
	//Get the command
	string command;	
	cout<<"Enter node name to delete or q to quit:";
	cin>>command;
	
	//Variable initializations
	bool complete = false;
	bool foundNode = false;
	string nodeCheck;
	int index;
	
	//Program will continue until q is entered
	while(command != "q")
	{
		/** This for loop will search the node in the list and after it finds it,
			it will deactivate it, setting its boolean IsActive to false. 
			After that, it will check all other nodes' adjacency list and try to find 
			the node it disabled. If it finds it, it will make that node which links to the deactivated node
			unusable. This is also done via a boolean variable.
		*/
		for(int i = 0; i < nodeList.size(); i++)
		{
			if(nodeList[i]->GetName() == command)
			{
				foundNode = true;
				nodeList[i]->Deactivate();
				for(int j = 0; j < nodeList.size(); j++)
				{
					//After disabling the node and finding it in another nodes adjacency list, it will set the usability of that node to false
					if(ExistsInVector(command, nodeList[j]->GetAdjacencyList())==true)
					{
						
						nodeList[j]->SetUsable(false);
					}
					
				}
						
			}
			//If the node is not found, tell the user.
			if(i == nodeList.size()-1 && foundNode == false)
			{
				cout<<"Node not found!\n";
			}
		}
		
		
		//Print the graph with the new nodes and links, then print the updated usability table of the nodes
		PrintGraph(nodeList);
		cout<<endl;
		//Get new command
		cout<<"Enter node name to delete or q to quit:";
		cin>>command;
	} //end while loop
	
	//Free the memory
	for(int i = 0; i < nodeList.size(); i++)
	{
		delete nodeList[i];
	}
	//vector<Node*> nodeList;	
	return 0;
}


//Checks if the given string exists in the given vector.
bool ExistsInVector(string nodeName, vector<Node*> nodeList)
{
	for(int i = 0; i < nodeList.size(); i++)
	{
		if(nodeName == nodeList[i]->GetName())
		{
			return true;
		}
	}
	return false;
}

/** First prints the graph. Shows each node and which node it links to.
	Then it shows a table which states each nodes' usability status.
*/
void PrintGraph(vector<Node*> nodeList)
{
	cout<<endl;
	for(int i = 0; i < nodeList.size(); i++)
	{
		if(nodeList[i]->GetActive())
		{
			nodeList[i]->PrintNodes();
			cout<<endl;
		}
		
	}
	
	cout<<"Nodes\tUsable\n";
	cout<<"-----\t------\n";
	for(int i = 0; i < nodeList.size(); i++)
	{
		if(nodeList[i]->GetActive())
		{
			cout<<nodeList[i]->GetName()<<"\t";
			if(nodeList[i]->GetUsable()) cout<<"True\n";
			else cout<<"False\n";
			
		}
	}
}
