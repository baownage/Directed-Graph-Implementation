#ifndef Node_H
#define Node_H
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Node
{
	public:
		//Constructor for the class
		Node(string newName);
		
		//Will return the active status of the Node
		bool GetActive();
		
		//Adds a new node to the list of nodes
		void AddNewNode(Node *newNode);
		
		//Checks if tempNode is present in the list of nodes, will return true or false
		bool IsNodePresent(string nodeName);
		
		//Prints all the nodes in the list and also the node that owns the list
		void PrintNodes();
		
		//Gets the name of the node
		string GetName();
		
		//Activates node (sets boolean flag to true)
		void Activate();
		
		//Deactivates node (sets boolean flag to false)
		void Deactivate();
		
		//Checks if node is usable
		bool GetUsable();
		
		//Sets "usable" property
		void SetUsable(bool usable);
		
		vector<Node*> GetAdjacencyList();
	
	private:
		bool IsActive;
		bool IsUsable;
		vector<Node*> adjList;
		string Name;
		
};

#endif
