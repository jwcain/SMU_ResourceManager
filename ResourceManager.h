//Represents a resource graph as per the SMU Graduate programming assignment
//Author: Justin Cain @AffinityForFun
//11/22/2018

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>
#include "LinkedList.h"

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

// <summary>
// A directed node that contains a string value and one directional links to other nodes stored as string references to the values stored in other nodes
// </summary>
class DirectedNode {
private:
	//Name of the resource this node represents
	std::string resource;
	//Links, stored as strings references
	LinkedList<std::string>* links;
public:
	// <summary>
	// Returns the resource value of this node
	// </summary>
	std::string GetResource() {return resource; }
	// <summary>
	// Returns the internal link list of this node
	// </summary>
	LinkedList<std::string>* GetLinks() {return links; }
	
	// <summary>
	// Constructor
	// </summary>
	DirectedNode(std::string resourceName) {
		resource = resourceName;
		links = new LinkedList<std::string>(); 
	}
	
	// <summary>
	// Deconstructor
	// </summary>
	~DirectedNode() {
		delete links;
	}
};

// <summary>
// A directed node that contains a string value and one directional links to other nodes stored as string references to the values stored in other nodes
// A resource name cannot be longer than 255 characters.
// </summary>
class ResourceManager {
private:
	//The current open file, stored on the class level so building a file reading operations can be abstracted into methods
	FILE* openFile = NULL;
	//The resources that exist within this resource manager
	LinkedList<DirectedNode*>* nodes;
	
	void BuildGraphFromOpenFile();
	std::string GetNextStringFromOpenFile();
public:
	LinkedList<DirectedNode*>* GetNodes();
	void Load(const char* filename, bool deleteNodes);
	void Save(const char* filename);
	void CloseFile();
	void VisualizeAsText();
	void DisplayUsability();
	void NewNode(std::string resource);
	LinkedList<std::string>* CheckMissingLinks(DirectedNode* resource);
	void DeleteNode(DirectedNode* node);
	DirectedNode* FindResourceNode(std::string resource);
	~ResourceManager();
};

#endif