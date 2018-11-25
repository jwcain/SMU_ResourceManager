//Author: Justin Cain @AffinityForFun
//11/22/2018
#include "ResourceManager.h"


// <summary>
// Builds a graph by reading in pairs of strings at a time. A node is found/created for the first one, and then a link is set to the second one.
// </summary>
void ResourceManager::BuildGraphFromOpenFile() {
	while (1) {
		//Read resources in pairs
		std::string resource1 = GetNextStringFromOpenFile();
		std::string resource2 = GetNextStringFromOpenFile();
		//Perform checks for EOF
		if (resource1 == "")
			//If the first one is EOF, we assume we have reached EOF properly
			break;
		else if (resource2 == "") {
			//If our first one was not EOF, but the second one is, we have improper input
			std::cerr << "Malformed input file. Error after resource "<< resource1 <<"\n";
			break;
		}
		//Check if nodes exists for resource1 and resource2
		//Create them if they do not.
		DirectedNode* firstNode = FindResourceNode(resource1);
		DirectedNode* secondNode = FindResourceNode(resource2);
		if (firstNode == 0) {
			firstNode = new DirectedNode(resource1);
			nodes->Add(firstNode);
		}
		if (secondNode == 0) {
			nodes->Add(new DirectedNode(resource2));
		}
		//Establish Link
		if (firstNode->GetLinks()->Contains(resource2) == false)
			firstNode->GetLinks()->Add(resource2);
		else
			std::cerr << "Duplicate resource link in file. " << resource1 << " >> " << resource2 << "\n""\n";
	}
	
}

// <summary>
// Reads in a properly formatted string from the file, with the correct sizing. Returns empty on end of file and error.
// </summary>
std::string ResourceManager::GetNextStringFromOpenFile() {
	//Return EOF if we have reached the end of the file
	if (feof(openFile)) {
		return ""; // Return Empty
	}
	
	//Buffer to read the next string into
	char readBuffer[256]; //README: Character limit of resource set to 255
	//Read the next string
	int readInfo = fscanf(openFile, "%s", readBuffer);
	//If we have hit an error, return the EOF character to properly close out
	if (readInfo <= 0) {
		//No further strings read
		return ""; // Return empty
	}
	
	//Count the size of the string
	int stringLen = 0; while (readBuffer[stringLen++] != '\0');
	//Create a properly sized string pointer based on the number of chars we read (+1 for null terminator)
	char* properString = (char*) malloc(sizeof(char)*(stringLen + 1));
	//Copy from the buffer to the string pointer
	for (short i = 0; i < stringLen; i++) {
		properString[i] = readBuffer[i];
	}
	//delete readBuffer;
	//Set the last position as the null terminator
	properString[stringLen] = '\0';
	
	std::string returnString(properString);
	free(properString);
	return returnString;
}

// <summary>
// Returns the internal node list
// </summary>
LinkedList<DirectedNode*>* ResourceManager::GetNodes() {
	return nodes;
}

// <summary>
// Loads a graph from a file
// </summary>
void ResourceManager::Load(const char* filename, bool deleteNodes) {
	//Free any data we may have already loaded.
	if (deleteNodes || nodes == 0) {
		if (nodes != 0)
			delete nodes;
		nodes = new LinkedList<DirectedNode*>();
	}
	//Open the file
	openFile = fopen(filename, "r");

	//Check if we opened the file
	if (openFile != NULL) {
		fseek(openFile, 0, SEEK_END);
		//Check if there are contents in the file to avoid empty file read errors
		if (ftell(openFile) > 0) {
			//Rewind to the beginnning
			rewind(openFile);
			//Build the Directed Graph
			BuildGraphFromOpenFile();
		}
		//Close the file
		CloseFile();
	}
	else
		//Report the error
		std::cerr << "Unable to located the file " << filename << ". Operation will continue without. \n";
}


// <summary>
// Saves a graph to the file name
// </summary>
void ResourceManager::Save(const char* filename) {
	std::cout << "Saving...\n";
	//Open the file with truncation
	openFile = fopen(filename, "w+");
	//Get an array of the directed nodes
	DirectedNode** resources = nodes->GetValueArray();
	//Loop through all nodes
	for (unsigned int i = 0; i < nodes->GetSize(); i++) {
		//Get its array of links
		std::string* links = resources[i]->GetLinks()->GetValueArray();
		//Loop through all links
		for (unsigned int j = 0; j < resources[i]->GetLinks()->GetSize(); j++) {
			//Let the user know this link was saved.
			std::cout << resources[i]->GetResource() << " -> " << links[j] << "\n";
			//Print this link to the file on its own line.
			fprintf(openFile, "%s %s\n", resources[i]->GetResource().c_str(), links[j].c_str());
		}
		delete[] links;
	}
	delete[] resources;
	//Close the file
	CloseFile();
	
	//Let the user know saving is complete
	std::cout << "Saving complete\n";
}

// <summary>
// Closes the open file file.
// </summary>
void ResourceManager::CloseFile() {
	if (openFile != NULL)
		fclose(openFile);
	else
		std::cerr << "Attempted to close unopened file.";
}


// <summary>
// Shows the graph and its links in a text, tree-like structure
// </summary>
void ResourceManager::VisualizeAsText() {
	//Display the total number of resources
	std::cout << nodes->GetSize() << " Resources Loaded: \n";
	//Get the array of resources
	DirectedNode** resources = nodes->GetValueArray();
	//Loop through all resources
	for (unsigned int i = 0; i < nodes->GetSize(); i++) {
		
		//Print out the name of this resource and how many links it has
		std::cout << "\t"<<resources[i]->GetResource() << ": "<<  resources[i]->GetLinks()->GetSize() << " links\n";

		//Get the list of links
		std::string* links = resources[i]->GetLinks()->GetValueArray();
		//Loop through all links
		for (unsigned int j = 0; j < resources[i]->GetLinks()->GetSize(); j++) {
			//Print a line and its name
			std::cout << "\t\t|"<< links[j] << "\n";
		}
		delete[] links;
	}
	delete[] resources;
}


// <summary>
// Displays the usability status of all nodes. A node is unusable if it has a link but the node for that link does not exist
// </summary>
void ResourceManager::DisplayUsability() {
	std::cout <<"Resource Usability: \n";
	//Get the list of resources as an array
	DirectedNode** resources = nodes->GetValueArray();
	//Loop through all resources
	for (unsigned int i = 0; i < nodes->GetSize(); i++) {
		//Get a list of all missing links
		LinkedList<std::string>* missing = CheckMissingLinks(resources[i]);
		//Check if the pointer is null
		if (missing) {
			//If it isnt, we have at least on missing link
			//Tell the user that this is missing links
			std::cout <<"\t"<< resources[i]->GetResource() << ": Unusable, Missing " << missing->GetSize() << " links\n";
			//Get the strings as an array
			std::string* missingText = missing->GetValueArray();
			//Loop through the missing link strings
			for (unsigned int j = 0; j < missing->GetSize(); j++) {
				//Print the name of the missing link
				std::cout << "\t\tMissing: "<< missingText[j] << "\n";
			}
			delete[] missingText;
		}
		else {
			//Tell the user this resource is usable
			std::cout <<"\t"<< resources[i]->GetResource() << ": Usable. (All Links point to valid nodes)\n";
		}
		//Delete the instatiated list
		delete missing;
	}
	delete[] resources;
}

// <summary>
// Adds a new node to the graph
// </summary>
void ResourceManager::NewNode(std::string resource) {
	DirectedNode* newNode = new DirectedNode(resource);
	nodes->Add(newNode);
}


// <summary>
// Checks if the node's links have an existing corresponding node. Returns the list strings for unfound nodes
// </summary>
LinkedList<std::string>* ResourceManager::CheckMissingLinks(DirectedNode* resource) {
	//Create a list to store missing links
	LinkedList<std::string>* missing = new LinkedList<std::string>();
	//Get an array of link strings for this resource
	std::string* links = resource->GetLinks()->GetValueArray();
	//Loop through the array
	for (unsigned int i = 0; i < resource->GetLinks()->GetSize(); i++) {
		//Attempt to find the resource
		DirectedNode* node = FindResourceNode(links[i]);
		//If we didn't, add it to the missint list
		if (node == 0) {
			missing->Add(links[i]);
		}
	}
	delete[] links;
	//Check if we found any missing
	if (missing->GetSize() == 0) {
		//If we didnt, delete the list
		delete missing;
		//Return null pointer
		return 0;
	}
	else {
		//Otherwise, return the list
		return missing;
	}
	
}


// <summary>
// Deletes a node from the graph
// </summary>
void ResourceManager::DeleteNode(DirectedNode* node) {
	nodes->Remove(nodes->Find(node));
	delete node;
}


// <summary>
// Finds a node in the graph based on its resource string. Returns null pointer (0) if not found.
// </summary>
DirectedNode* ResourceManager::FindResourceNode(std::string resource) {
	//Get all nodes as an array
	DirectedNode** resources = nodes->GetValueArray();
	//Loop through the array
	for (unsigned int i = 0; i < nodes->GetSize(); i++) {
		//If the strings are equal
		if (strcmp(resources[i]->GetResource().c_str(), resource.c_str()) == 0) {
			//Store the node we want to return
			DirectedNode* ret =  resources[i];
			//Delete the created array
			delete[] resources;
			//Return the node
			return ret;
		}
	}
	
	delete[] resources;
	//Otherwise, return a null pointer if we have not found a matching resource
	return 0;
}

ResourceManager::~ResourceManager() {
	DirectedNode** resources = nodes->GetValueArray();
	for (unsigned int i = 0; i < nodes->GetSize(); i++) {
		delete resources[i];
	}
	delete[] resources;
	delete nodes;
}
