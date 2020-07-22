// hashTagCounter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "FibHeap.h"
//#include "Node.h"
//#include "hashTable.h"

using namespace std;

int main(int argc, char *argv[])
{
	//Read the input file name from the command line
	string inputFileName = argv[1];
	
	string outputFileName = "";
	ifstream file(inputFileName);
	ofstream ofile;
	//check if output file name exists in command line
	if(argv[2]){
		//cout<<"output file name is present";
		outputFileName = argv[2];
		
		ofile.open("./"+outputFileName, std::ios_base::out | std::ios_base::app & std::ios_base::out | std::ios_base::trunc);
	}
	
	//cout<<"arguements are "<< inputFileName<<"\t"<<outputFileName<<"\n";
	//initialize Fibonacci Heap
    FibHeap h;
	//initialize hash map 
    unordered_map<string, Node*> hashMap;
    
    string line;
    string hashTag;
    int val;
    int remove;
	//read from input file one line at a time
    while (getline(file,line)) {
		//use string "stop" as a end of file, if found, stop reading
        if (line == "stop" || line=="STOP") {
            break;
        }
		//Check for Query
        if (line[0] != '#') {
            remove = stoi(line, nullptr, 10);
            vector<Node*> maxNodes(remove);
            for (int i = 0; i < remove; i++) {
                Node* maxNode = h.removeMax();
				//write into the file if output file name is not provided in command line
				if(outputFileName!=""){
					
					if (i == remove - 1) {
						//ofile<< maxNode->data;
						ofile << maxNode->hashTag.substr(1, maxNode->hashTag.length()-1);
					}
					else {
						//ofile<<maxNode->data<<",";
						ofile << maxNode->hashTag.substr(1, maxNode->hashTag.length() - 1) << ",";
					}
					
				}
				else{
					if (i == remove - 1) {
						cout << maxNode->hashTag.substr(1, maxNode->hashTag.length()-1);
					}
					else {
						cout << maxNode->hashTag.substr(1, maxNode->hashTag.length() - 1) << ",";
					}
				}
                
                maxNodes[i] = maxNode;
            }
			if(outputFileName!=""){
				
				ofile << "\n";
				//ofile.close();
			}
			else
				cout << "\n";
			//reinsert the max nodes
            for (int i = 0; i < remove; i++) {
                h.insert(maxNodes[i]);
            }
            
        }
		
        else {
            hashTag = line.substr(0, line.find(' '));
            val = stoi(line.substr(line.find(' ') + 1, line.length() - 1));
            //check if the hastag is in hashmap, insert into fibonacci heap if not present, else update the count
            if (hashMap.find(hashTag) == hashMap.end()) {
                Node* n = new Node(val, hashTag);
                hashMap.insert(make_pair(hashTag, n));
                h.insert(n);
            }
            else {
                auto it = hashMap.find(hashTag);
                Node* n = it->second;
                h.increaseCount(n, val);
            }
        }

    }
	//close the output file
	if(outputFileName!="")
		ofile.close();
    return 0;
    
    
    
    
    
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
