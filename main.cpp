#include <bits/stdc++.h>

using namespace std;

int debug=0;

int prec=8;

int eri=0,erj=0;

#include "lexer.cpp"
#include "parser.cpp"
#include "interpreter.cpp"

variable varlist;


void standart()
{
	string dir;
	cout<<"Type file directory:\n";
	
	dir = "C:\\Sandu\\Uni\\PC\\SI\\TEXT2.txt";
	
	//cin>>dir;
	
	system("cls");
    
//    vector<vector<string> > wordMatrix;
//    vector<int> wordCountArray;
//    string line;
//    while (getline(file, line)) {
//        vector<string> words;
//        istringstream iss(line);
//        string word;
//        while (iss >> word) {
//            words.push_back(word);
//        }
//		wordMatrix.push_back(words);
//
//        wordCountArray.push_back(words.size());
//    }
//    file.close();
//    
//    for (const auto& row : wordMatrix) {
//        for (const auto& word : row) {
//            std::cout << word << " ";
//        }
//        std::cout << std::endl;
//        
//    }

	vector<string> Textlines;  // Vector to store lines from the file

    // Open the file
    ifstream file(dir.c_str());

    // Check if the file is opened successfully
    if (file.is_open()) {
        string line;

        // Read each line from the file
        while (getline(file, line)) {
            Textlines.push_back(line);  // Add each line to the vector
        }

        // Close the file
        file.close();
    } else {
        cerr << "Error opening file"<< endl;
        exit(0);
    }
	
	vector<vector<token>> Tokenlines;

	for (const auto& lineo : Textlines) {
		if(debug==1){
        	cout << lineo << endl;
		}
        Tokenlines.push_back(lexer(lineo));
        eri++;
    }
    
    if (Tokenlines.empty()){
    	cout<<"ERROR PROGRAM EMPTY";
    	exit(0);
	}
    
    
    removeEmptyRows(Tokenlines);
	parser(Tokenlines);
	if(debug==1){
		cout<<endl;
		tree.printTree(tree.getRoot());
		cout<<endl;
		tree.print();
	}
	
	interpreter(Tokenlines);
}

int mode()
{
	char x;
//	cout<<"\n\tType 1 for standart mode or 2 for intercative mode:";
	x='1';
//	cin>>x;
	if (x=='1')
		return 1;
	else if (x=='2')
		return 0;
	else
	return -1;
}

int main()
{
	int mod;
	mod=mode();
	if (mod==-1)
	{
		cout<<"Mode error!";
		exit(0);
	}
	else if(mod==1)
	{
		standart();
	}
}
