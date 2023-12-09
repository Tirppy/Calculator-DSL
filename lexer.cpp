struct token{
	string type;
	int val;
	string name;
	int vali;
	double valf;
};

bool isNumber(string s) 
{ 
	std::size_t char_pos(0);
	char_pos = s.find_first_not_of(' '); 
	if (char_pos == s.size()) return false;
	if (s[char_pos] == '+' || s[char_pos] == '-')  
		++char_pos;
	int n_nm, n_pt; 
	for (n_nm = 0, n_pt = 0;  
		std::isdigit(s[char_pos]) || s[char_pos] == '.';  
		++char_pos) { 
		s[char_pos] == '.' ? ++n_pt : ++n_nm; 
	}
	if (n_pt>1 || n_nm<1)
		return false; 
	while (s[char_pos] == ' ') { 
		++ char_pos; 
	} 
	return char_pos == s.size();
}

bool isInteger(double N)
{
    int X = N;
 
    double temp2 = N - X;
    if (temp2 > 0) {
        return false;
    }
    return true;
}

void removeEmptyRows(std::vector<std::vector<token>>& matrix) {
    // Use iterator to iterate and erase empty rows
    auto it = matrix.begin();
    while (it != matrix.end()) {
        if (it->empty()) {
            it = matrix.erase(it);
        } else {
            ++it;
        }
    }
}

//int main()
vector<token> lexer(string line)
{
	
//	string line = "start int x 3 add x 5 show x if x g 4 show 2 stop";
	
	vector <string> tokens;
	
	stringstream check1(line);
	
	string intermediate;
	
	while (check1 >> intermediate)
    {
        tokens.push_back(intermediate);
    }
	
//	for(int i = 0; i < tokens.size(); i++)
//		cout << tokens[i] << " ";
	
	vector<token> linetoken;
	
	token tokenc;
	
	
	int nr;
	
	regex pattern("[a-zA-Z_][a-zA-Z0-9_]*");
	
	erj=0;
	
	for(int i = 0; i < tokens.size(); i++){
		nr=0;
//		cout<<"\n"<<tokens[i]<<typeid(tokens[i]).name()<<endl;
		if (tokens[i]=="add")
		{
			tokenc.type="oper";
			tokenc.val=0;
			linetoken.push_back(tokenc);
		}
		else if (tokens[i]=="sub")
		{
			tokenc.type="oper";
			tokenc.val=1;
			linetoken.push_back(tokenc);
		}
		else if (tokens[i]=="mult")
		{
			tokenc.type="oper";
			tokenc.val=2;
			linetoken.push_back(tokenc);
		}
		else if (tokens[i]=="div")
		{
			tokenc.type="oper";
			tokenc.val=3;
			linetoken.push_back(tokenc);
		}
		else if (tokens[i]=="start")
		{
			tokenc.type="lim";
			tokenc.val=0;
			linetoken.push_back(tokenc);
		}
		else if (tokens[i]=="stop")
		{
			tokenc.type="lim";
			tokenc.val=1;
			linetoken.push_back(tokenc);
		}
		else if (tokens[i]=="int")
		{
			tokenc.type="def";
			tokenc.val=0;
			linetoken.push_back(tokenc);
		}
		else if (tokens[i]=="double")
		{
			tokenc.type="def";
			tokenc.val=1;
			linetoken.push_back(tokenc);
		}
		else if (tokens[i]=="if")
		{
			tokenc.type="cond";
			tokenc.val=0;
			linetoken.push_back(tokenc);
		}
		else if (tokens[i]=="while")
		{
			tokenc.type="cond";
			tokenc.val=1;
			linetoken.push_back(tokenc);
		}
		else if (tokens[i]=="e")
		{
			tokenc.type="comp";
			tokenc.val=0;
			linetoken.push_back(tokenc);
		}
		else if (tokens[i]=="g")
		{
			tokenc.type="comp";
			tokenc.val=1;
			linetoken.push_back(tokenc);
		}
		else if (tokens[i]=="s")
		{
			tokenc.type="comp";
			tokenc.val=2;
			linetoken.push_back(tokenc);
		}
		else if (tokens[i]=="ge")
		{
			tokenc.type="comp";
			tokenc.val=3;
			linetoken.push_back(tokenc);
		}
		else if (tokens[i]=="se")
		{
			tokenc.type="comp";
			tokenc.val=4;
			linetoken.push_back(tokenc);
		}
		else if (tokens[i]=="show")
		{
			tokenc.type="show";
			tokenc.val=0;
			linetoken.push_back(tokenc);
		}
		else if (isNumber(tokens[i]))
		{
			tokenc.type="var";
			if (isInteger(stof(tokens[i]))==1){
				tokenc.val=1;
				tokenc.vali=stoi(tokens[i]);
			}
			else{
				tokenc.val=2;
				tokenc.valf=stof(tokens[i]);
			}
			linetoken.push_back(tokenc);
		}
		else if (regex_match(tokens[i], pattern))
		{
			tokenc.type="var";
			tokenc.val=0;
			tokenc.name=tokens[i];
			linetoken.push_back(tokenc);
//			try
//			{
//				for (int j=0;j<varlist.size();j++){
//					if(tokens[i] == varlist[j].name){
//						tokenc.type="var";
//						tokenc.val=0;
//						tokenc.name=tokens[i];
//						linetoken.push_back(tokenc);
//						break;
//					}
//					throw (tokens[i]);
//				}
//			}
//			catch(string missvar)
//			{
//				cout<<"\nExpression '"<<missvar<<"' not found!";
//				exit(0);
//			}
		}
		else
		{
            cerr << "ERROR UNKNOWN TOKEN TYPE ["<<eri<<";"<<erj<<"]!";
            exit(0);
        }
        erj++;
	}
	
	if(debug==1){
		for(int i = 0; i < linetoken.size(); i++){
			cout<<linetoken[i].type<<linetoken[i].val<<" ";
		}
		cout<<endl;
	}
	
	return linetoken;
}
	
