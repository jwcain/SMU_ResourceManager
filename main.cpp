//Author: Justin Cain @AffinityForFun
//11/22/2018
#include "ResourceManager.h"
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "LinkedList.h"

//The default file name to load/save graph from
const char* defaultFileName = "resources.txt";
//The current ResourceManager instance
ResourceManager* rM;

//Function definition, Takes in a list of arguments, returns if the command was successful or not
typedef bool (*CommandFunction)(std::vector<std::string> argv);

//A structure for holding a command line argument
struct Command {
	//The name of this command. Matching this executes the command
	const char* name;
	//The description of this command for assisting the user
	const char* desc;
	//The function to use to execute when this function is called
	CommandFunction execute;
};
//The total number of commands
const int commandCount = 11;
//The list of available commands
Command commands[commandCount];

// <summary>
// Adds a node to the graph
// </summary>
bool Command_Add(std::vector<std::string> argv) {
	//Loop through the arguments
	for (unsigned int i = 0; i < argv.size(); i++) {
		//Attempt to find a resourcec node that matches the argument
		DirectedNode* node = rM->FindResourceNode(argv[i].c_str());
		//check if that node exists
		if (node) {
			//If it does, tell the user it already exists
			std::cout << "Node for resource "<< argv[i] << " already exists." << "\n";
		}
		else {
			//Otherwise create it
			rM->NewNode(argv[i]);
			//Tell the user that it was created
			std::cout << "Node "<< argv[i] << " created." << "\n";
		}
	}
	return true;
}

// <summary>
// Prints out all commands and their descriptions to the user
// </summary>
bool Command_Help(std::vector<std::string> argv) {
	//Loop through all commands
	for (int i = 0; i < commandCount; i++) {
		//print their name and their description
		std::cout << commands[i].name << "\t:  " << commands[i].desc << "\n";
	}
	return true;
}

// <summary>
// Establishes a link between a node and a resource
// </summary>
bool Command_Link(std::vector<std::string> argv) {
	//Return error if size is not exactly 2
	if (argv.size() != 2)
		return false;
	//Attempt to find a node for the first argument
	DirectedNode* node = rM->FindResourceNode(argv[0].c_str());
	//if it exists
	if (node)
		//Add the link
		node->GetLinks()->Add(argv[1].c_str());
	else 
		//Report to user that the first arguemtn does not have a node
		std::cout << "Node for " << argv[0].c_str() << " does not exist.\n";
	return true;
}

// <summary>
// Removes a node from the graph
// </summary>
bool Command_Delete(std::vector<std::string> argv) {
	//Loop through all arguments
	for (unsigned int i = 0; i < argv.size(); i++) {
		//Attempt to find a node for that argumenmt
		DirectedNode* node = rM->FindResourceNode(argv[i].c_str());
		//Check if it exists
		if (node) {
			//If it does, delete it
			rM->DeleteNode(node);
			//Report sucess to the user
			std::cout << "Node "<< argv[i] << " deleted." << "\n";
		}
		else {
			//Let the user know that this node does not exist
			std::cout << "Node "<< argv[i] << " note found." << "\n";
		}
	}
	
	return true;
}

// <summary>
//	Exits the manager. Saves on exit.
// </summary>
bool Command_Exit(std::vector<std::string> argv) {
	std::cout << "Exit..." << "\n";
	rM->Save(defaultFileName);
	delete rM;
	exit(1);
	return true;
}

// <summary>
// Saves the current manager state to a file. Default file name if no arguments passed, otherwise uses the argument as a filename
// </summary>
bool Command_Save(std::vector<std::string> argv) {
	//check if we have an argument
	if (argv.size())
		//If we do, save it to that file
		rM->Save(argv[0].c_str());
	else
		//Otherwise save to default
		rM->Save(defaultFileName);
	return true;
}
// <summary>
// Removes a link from a node to a resource
// </summary>
bool Command_Unlink(std::vector<std::string> argv) {
	//Check if we have exactly two errors
	if (argv.size() != 2)
		return false;
	
	//Find a node for the first argument
	DirectedNode* node = rM->FindResourceNode(argv[0].c_str());
	//Check to see if node exists
	if (node) {
		//Search for the link
		Node<std::string>* link = node->GetLinks()->Find(argv[1]);
		//Check to see if it exists
		if (link) {
			//If it does, remove it
			node->GetLinks()->Remove(link);
			//Let the user know
			std::cout << "Link "<<argv[0].c_str()<<" to "<<argv[1].c_str()<<" removed \n";
		}
		else
			//Otherwise tell the user that the link does note exist
			std::cout << "Link did not exist." << "\n";
	}
	else 
		std::cout << "Node for " << argv[0].c_str() << " does not exist.\n";
	return true;
}

// <summary>
// Checks the integrity of the graph. Can be used on the whole graph or a selection 
// of nodes. Checks if a node is orphaned (has no nodes linking to it, or no nodes linked 
// from it), or if it is self referential recursively along links
// </summary>
bool Command_Integrity(std::vector<std::string> argv) {
	//Create a list of nodes to check
	LinkedList<DirectedNode*>* nodesToCheckList;
	//If we have no input, assume we are to check each node, otherwise only check the listed nodes
	if (argv.size() == 0) {
		//assign the nodes to check to all nodes
		nodesToCheckList = rM->GetNodes();
	}
	else {
		//make a new list
		nodesToCheckList = new LinkedList<DirectedNode*>();
		//loop through the arguments
		for (unsigned int i = 0; i < argv.size(); i++) {
			//Attempt to find a node for the argument
			DirectedNode* node = rM->FindResourceNode(argv[i]);
			//Check if we found one
			if (node) {
				//Add it if we did
				nodesToCheckList->Add(node);
			}
			else {
				std::cout << "Node "<< argv[i] <<" does not exist." << "\n";
			}
		}
	}
	//Get an iterable array from that list
	DirectedNode** nodesToCheck = nodesToCheckList->GetValueArray();
	//Loop through the array
	for (unsigned int i = 0; i < nodesToCheckList->GetSize(); i++) {
		//Count links leading to this node
			//Go through all other nodes
			//if they link this, increase count
		int linkInCount = 0;
		{
			//Get an array of all nodes
			DirectedNode** allNodes = rM->GetNodes()->GetValueArray();
			//Loop through all the nodes
			for (unsigned int j = 0; j < rM->GetNodes()->GetSize(); j++) {
				//Check that nodes links for the main node we are looking for
				Node<std::string>* link = allNodes[j]->GetLinks()->Find(nodesToCheck[i]->GetResource());
				//If it is there, increment the count
				if (link)
					linkInCount++;
			}
			
			delete[] allNodes;
		}
		//Count links leading out of this node
		int linkOutCount = nodesToCheck[i]->GetLinks()->GetSize();
		//Do flood search across links, and if we appear in that search we are recursive
		//Create a list of expanded and to expand nodes
		LinkedList<DirectedNode*>* toExpand = new LinkedList<DirectedNode*>();
		LinkedList<DirectedNode*>* expanded = new LinkedList<DirectedNode*>();
		//Add this node's links as to expand
		{
			//Get a list of all links
			std::string* links = nodesToCheck[i]->GetLinks()->GetValueArray();
			//Loop through the links
			for (unsigned int j = 0; j < nodesToCheck[i]->GetLinks()->GetSize(); j++) {
				//Get the node for this link
				DirectedNode* node = rM->FindResourceNode(links[j]);
				//If the node exists
				if (node) {
					if ( toExpand->Contains(node) == false) {
						//Add it to the to Expand list.
						toExpand->Add(node);
					}
				}
			}
			delete[] links;
		}
		while (toExpand->GetSize() > 0) {
			//Store the head of the toExpand
			Node<DirectedNode*>* c = toExpand->Peek();
			//Store its value
			DirectedNode* n = c->value;
			//Add it to the expanded list
			expanded->Add(n);
			//Remove it from the list
			toExpand->Remove(c);
			
			//Get the links from this node
			std::string* links = n->GetLinks()->GetValueArray();
			for (unsigned int j = 0; j < n->GetLinks()->GetSize(); j++) {
				//Get the node for this link
				DirectedNode* node = rM->FindResourceNode(links[j]);
				//If the node exists
				if (node) {
					//If we have not looked at this node yet
					if (expanded->Contains(node) == false && toExpand->Contains(node) == false) {
						//Add it to the to Expand list.
						toExpand->Add(node);
					}
				}
			}
			delete[] links;
		}
		//Print the report of the node
		std::cout << "Node:" << nodesToCheck[i]->GetResource() << "\n";
		std::cout << "\t links inward:\t"<< linkInCount << "\n";
		std::cout << "\t links outward:\t"<< linkOutCount << "\n";
		if (linkInCount + linkOutCount == 0)
			std::cout << "\t Warning: This node has no links and will be discarded on save. \n";
		if (expanded->Contains(nodesToCheck[i]))
			std::cout << "\t Warning: Recursive link, somewhere this resource depends on itself. \n";
		delete toExpand;
		delete expanded;
	}
	delete[] nodesToCheck;
	//Only delete the nodes list if it is pointing to one we made
	if(argv.size() != 0) {
		std::cout << "Deleting nodes." << "\n";
		delete nodesToCheckList;
	}
	return true;
}

// <summary>
// Merges resource file(s) into this one.
// </summary>
bool Command_Merge(std::vector<std::string> argv) {
	//Loop through all the arguments and attempt a merge
	for (unsigned int i = 0; i < argv.size(); i++) 
		rM->Load(argv[i].c_str(), false);
	return true;
}

// <summary>
// deletes and remakes the resource manager
// </summary>
bool Command_Clear(std::vector<std::string> argv) {
	delete rM;
	rM = new ResourceManager();
	return true;
}


//Create structures for all of the commands
struct Command command_delete = {"delete", "Deletes node(s) from the graph", Command_Delete};
struct Command command_q = {"q", "Alias for Exit.", Command_Exit};
struct Command command_exit = {"exit", "Exits the manager", Command_Exit};
struct Command command_help = {"help", "Prints descriptions for all commands", Command_Help};
struct Command command_add = {"add", "Add node(s) to the graph", Command_Add};
struct Command command_link = {"link", "Links a node a->n", Command_Link};
struct Command command_unlink = {"unlink", "Unlinks a node a->n", Command_Unlink};
struct Command command_save = {"save", "saves the graph to a file (resources.txt if no file path specified)", Command_Save};
struct Command command_integrity = {"check", "Checks if node(s) link or are linked to, and for recursive dependency.", Command_Integrity};
struct Command command_merge = {"merge", "Merges other resource file(s) into this one", Command_Merge};
struct Command command_clear = {"newGraph", "Clears this graph and starts a new one. Does not save current to file.", Command_Clear};



// <summary>
// Executes a resource manager sim
// </summary>
int main() {
	//Place the commands into the command array. This is done here to ease scope/compilation issues.
	commands[0] = command_delete;
	commands[1] = command_exit;
	commands[2] = command_help;
	commands[3] = command_add;
	commands[4] = command_link;
	commands[5] = command_unlink;
	commands[6] = command_save;
	commands[7] = command_integrity;
	commands[8] = command_q;
	commands[9] = command_merge;
	commands[10] = command_clear;
	
	//Load a resource manager instance
	rM = new ResourceManager();
	rM->Load(defaultFileName, true);
	
	//Enter execution loop
	while (1) {
		//Display the links
		rM->VisualizeAsText();
		//Display usability
		rM->DisplayUsability();
		std::cout <<"---\t---\t---\t---\t---\t---\t\n";
		std::cout << "Enter a command: ";
		//Get a line of user input
		std::string input;
		getline(std::cin, input);
		//Split the line into individual tokens
		std::vector<std::string> splitInput;
		std::istringstream iss(input);
		for(std::string s; iss >> s; ) {
			//std::cout << s << "\n";
			splitInput.push_back(s);
		}
		//Loop through all commands to see if the first token matches
		bool foundFlag = false;
		for (int i = 0; i < commandCount; i++) {
			//Compare the first token to the command name
			if (strcmp(splitInput[0].c_str(), commands[i].name) == 0) {
				//Mark that we found a command
				foundFlag = true;
				//Pop off the first token so it is not used in the arguments
				splitInput.erase(splitInput.begin());
				//Execute the command
				commands[i].execute(splitInput);
				break;
			}
		}
		//If we have not found a command, let the user know their input was invalid
		if (foundFlag == false)
			std::cout << "Unrecognized command. Type help for a list of commands." << "\n";
		std::cout <<"---\t---\t---\t---\t---\t---\t\n";
	}
}