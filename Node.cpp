#include "Node.h"
#include <iostream>

Node::Node(string newName)
{
	IsUsable = true;
	IsActive = true;
	Name = newName;
}

bool Node::GetActive()
{
	return IsActive;
}

string Node::GetName()
{
	return Name;
}

void Node::AddNewNode(Node *newNode)
{
	
	adjList.push_back(newNode);
}

bool Node::IsNodePresent(string nodeName)
{
	
	for(int i=0; i<adjList.size(); i++)
	{
		if(adjList[i]->GetName() == nodeName) return true;
	}
	return false;
}

void Node::PrintNodes()
{
	cout<<"Node\tLinks to\n-----\t--------\n";
	cout<<GetName();
	for(int i=0; i<adjList.size(); i++)
	{
		if(adjList[i]->GetActive())
		{
			cout<<"\t"<<adjList[i]->GetName()<<endl;
		}		
	}	
	cout<<endl;	
	
}

void Node::Activate()
{
	IsActive = true;
}

void Node::Deactivate()
{
	IsActive = false;
}

bool Node::GetUsable()
{
	return IsUsable;
}

void Node::SetUsable(bool usable)
{
	IsUsable = usable;
}

vector<Node*> Node::GetAdjacencyList()
{
	return adjList;
}
