class TreeNode {
public:
    pair<int, int> data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(pair<int, int>  value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;
    TreeNode* current;

public:
    BinaryTree() : root(nullptr), current(nullptr) {}

    // Function to create the root of the tree
    void create(pair<int, int>  value) {
        if (root == nullptr) {
            root = new TreeNode(value);
            current = root;
        }
    }

    // Function to add an element to the left or right of the current node
    void add(int side, pair<int, int>  value) {
        if (side == 0 && current->left == nullptr) {
            current->left = new TreeNode(value);
            current = current->left;
        } else if (side == 1 && current->right == nullptr) {
            current->right = new TreeNode(value);
            current = current->right;
        }
    }

    // Function to go back to the previous level
    void back() {

        TreeNode* parent = findParent(root, current);
        if (parent != nullptr) {
            current = parent;
        }
    }
    
    bool isEmpty() const {
        return root == nullptr;
    }
    
    TreeNode* getRoot() const {
        return root;
    }
    
    void printTree(TreeNode* node) const {
	    if (node != nullptr) {
	        // Print the current node's data
	        cout << "(" << node->data.first << ", " << node->data.second << ") ";
	
	        // Recursively print the left subtree
	        printTree(node->left);
	
	        // Recursively print the right subtree
	        printTree(node->right);
	    }
	}
	
	pair<int, int> getCurrentNodeValue() const {
        if (current != nullptr) {
            return current->data;
        } else {
            // You might want to handle the case where 'current' is nullptr
            // For simplicity, returning a pair of -1 values here
            return make_pair(-1, -1);
        }
    }
    
    pair<int, int> getNBackValue(int n) const {
        if (current == nullptr) {
            // Handle the case where 'current' is nullptr
            // For simplicity, returning a pair of -1 values here
            return make_pair(-1, -1);
        }

        TreeNode* temp = current;
        while (n > 0 && temp != nullptr) {
            temp = findParent(root, temp);
            n--;
        }

        if (temp != nullptr) {
            return temp->data;
        } else {
            // Handle the case where 'temp' is nullptr
            // For simplicity, returning a pair of -1 values here
            return make_pair(-1, -1);
        }
    }
    
    void print() const {
        std::vector<std::vector<std::pair<int, int>>> levels;
        printRecursive(root, 0, false, levels);
    }
    
private:
    // Helper function to find the parent of a node in the tree
    TreeNode* findParent (TreeNode* node, TreeNode* child) const {
        if (node == nullptr || node == child) {
            return nullptr;
        }

        if ((node->left == child) || (node->right == child)) {
            return node;
        }

        TreeNode* leftParent = findParent(node->left, child);
        if (leftParent != nullptr) {
            return leftParent;
        }

        return findParent(node->right, child);
    }

    void printRecursive(const TreeNode* node, int depth, bool isRight, std::vector<std::vector<std::pair<int, int>>>& levels) const {
        if (node == nullptr) {
            return;
        }

        if (depth >= levels.size()) {
            levels.emplace_back();
        }

        levels[depth].push_back(node->data);

        const int spaces = 4;
        std::string prefix = isRight ? "R--" : "L--";

        std::cout << std::setw(depth * spaces) << "" << prefix << node->data.first << "," << node->data.second << std::endl;

        printRecursive(node->left, depth + 1, false, levels);
        printRecursive(node->right, depth + 1, true, levels);
    }

    void printLevels(const std::vector<std::vector<std::pair<int, int>>>& levels) const {
        const int spaces = 4;

        for (const auto& level : levels) {
            for (const auto& data : level) {
                std::cout << std::setw(spaces) << "+--" << data.first << "," << data.second;
            }
            std::cout << std::endl;
        }
    }
};

BinaryTree tree;

pair<int, int> sav;
int limN;

void parseElement(vector<vector<token>> tokenparse,pair<int, int>  coor);

void createTree(vector<vector<token>> tokenparse,pair<int, int>  val){
	if(tree.isEmpty()==1){
		tree.create(val);
	}
	else{
//				tree.add(1,val);
		cout<<"ERROR ON TREE CREATION";
	}
	int i=val.first;
	int j=val.second;
	val.second++;
	limN=0;
	parseElement(tokenparse,val);
}

void tokenDef(vector<vector<token>> tokenparse,pair<int, int> val,bool c){//cout<<"\nDEF";
	if(val.second+2>=tokenparse[val.first].size()){
		eri=val.first;
		erj=val.second;
		cout<<"ERROR ON VARIABLE DEFINITION ["<<eri<<";"<<erj<<"]!";
		exit(0);
	}
	tree.add(1,val);
	pair<int, int> val1=make_pair(val.first,val.second+1);
	pair<int, int> val2=make_pair(val.first,val.second+2);
	pair<int, int> valNext=make_pair(val.first,val.second+3);
	if(tokenparse[val1.first][val1.second].type=="var" and tokenparse[val1.first][val1.second].val==0 and tokenparse[val2.first][val2.second].type=="var"){
		tree.add(0,val1);
		tree.add(0,val2);
		tree.back();
		tree.back();
		if(c==0){
			parseElement(tokenparse,valNext);
		}
		else if(c==1){
			sav=valNext;
		}
	}
	else{
		eri=val.first;
		erj=val.second;
		cout<<"ERROR ON VARIABLE DEFINITION ["<<eri<<";"<<erj<<"]!";
		exit(0);
	}
}

void tokenOper(vector<vector<token>> tokenparse,pair<int, int> val,bool c){//cout<<"\nOPER";
	if(val.second+2>=tokenparse[val.first].size()){
		eri=val.first;
		erj=val.second;
		cout<<"ERROR ON OPERATION ["<<eri<<";"<<erj<<"]!";
		exit(0);
	}
	tree.add(1,val);
	pair<int, int> val1=make_pair(val.first,val.second+1);
	pair<int, int> val2=make_pair(val.first,val.second+2);
	pair<int, int> valNext=make_pair(val.first,val.second+3);
	if(tokenparse[val1.first][val1.second].type=="var" and tokenparse[val1.first][val1.second].val==0 and tokenparse[val2.first][val2.second].type=="var"){
		tree.add(0,val1);
		tree.add(0,val2);
		tree.back();
		tree.back();
		if(c==0){
			parseElement(tokenparse,valNext);
		}
		else if(c==1){
			sav=valNext;
		}
	}
	else{
		eri=val.first;
		erj=val.second;
		cout<<"ERROR ON OPERATION ["<<eri<<";"<<erj<<"]!";
		exit(0);
	}
}

void tokenLim(vector<vector<token>> tokenparse,pair<int, int> val){//cout<<"\nLIM";
	pair<int, int> valNext=make_pair(val.first,val.second+1);
//	cout<<endl<<"CORD: "<<val.first<<" / "<<val.second<<endl;
	if(tokenparse[val.first][val.second].val==0){
		pair<int, int> condit = tree.getNBackValue(3);
		if (tokenparse[condit.first][condit.second].type=="cond"){
			tree.add(1,val);
			limN++;
			parseElement(tokenparse,valNext);
		}
		else{
			cout<<endl<<condit.first<<" / "<<condit.second<<endl;
			eri=val.first;
			erj=val.second;
			cout<<"ERROR ON START ["<<eri<<";"<<erj<<"]!";
			exit(0);
		}
	}
	else if(tokenparse[val.first][val.second].val==1){
		if(limN>0){
			limN--;
			tree.add(1,val);
			sav=valNext;
		}
		else if(val.first==tokenparse.size()-1 and val.second==tokenparse[val.first].size()-1){
			tree.add(1,val);
		}
		else{
			eri=val.first;
			erj=val.second;
			cout<<"ERROR ON STOP ["<<eri<<";"<<erj<<"]!";
			exit(0);
		}
	}
	else{
		eri=val.first;
		erj=val.second;
		cout<<"ERROR ON STOP ["<<eri<<";"<<erj<<"]!";
		exit(0);
	}
}

void tokenShow(vector<vector<token>> tokenparse,pair<int, int> val,bool c){//cout<<"\nSHOW";
	if(val.second+1>=tokenparse[val.first].size()){
		eri=val.first;
		erj=val.second;
		cout<<"ERROR ON SHOW ["<<eri<<";"<<erj<<"]!";
		exit(0);
	}
	tree.add(1,val);
	pair<int, int> val1=make_pair(val.first,val.second+1);
	pair<int, int> valNext=make_pair(val.first,val.second+2);
	if(tokenparse[val1.first][val1.second].type=="var"){
		tree.add(0,val1);
		tree.back();
		if(c==0){
			parseElement(tokenparse,valNext);
		}
		else if(c==1){
			sav=valNext;
		}
	}
	else{
		eri=val.first;
		erj=val.second;
		cout<<"ERROR ON SHOW ["<<eri<<";"<<erj<<"]!";
		exit(0);
	}
}

void tokenCond(vector<vector<token>> tokenparse,pair<int, int> val,bool c){//cout<<"\nCOND";
	if(val.second+3>=tokenparse[val.first].size()){
		eri=val.first;
		erj=val.second;
		cout<<"ERROR ON CONDITION ["<<eri<<";"<<erj<<"]!";
		exit(0);
	}
	tree.add(1,val);
	pair<int, int> val1=make_pair(val.first,val.second+1);
	pair<int, int> val2=make_pair(val.first,val.second+2);
	pair<int, int> val3=make_pair(val.first,val.second+3);
	pair<int, int> val4=make_pair(val.first,val.second+4);
//	pair<int, int> valNext=make_pair(val.first,val.second+5);
	if(tokenparse[val1.first][val1.second].type=="var" and tokenparse[val1.first][val1.second].val==0 and tokenparse[val3.first][val3.second].type=="var" and tokenparse[val2.first][val2.second].type=="comp"){
		tree.add(0,val2);
		tree.add(0,val1);
		tree.add(0,val3);
		
		if(val.second+4>=tokenparse[val.first].size()){
			val4=make_pair(val.first+1,0);
		}
		if(tokenparse[val4.first][val4.second].type=="lim" and tokenparse[val4.first][val4.second].val==0){
			tokenLim(tokenparse,val4);
		}
		else if(tokenparse[val4.first][val4.second].type=="def"){
			tokenDef(tokenparse,val4,1);
		}
		else if (tokenparse[val4.first][val4.second].type=="oper"){
			tokenOper(tokenparse,val4,1);
		}
		else if (tokenparse[val4.first][val4.second].type=="cond"){
			tokenCond(tokenparse,val4,1);
		}
		else if (tokenparse[val4.first][val4.second].type=="show"){
			tokenShow(tokenparse,val4,1);
		}
		else{
			eri=val.first;
			erj=val.second;
			cout<<"ERROR ON CONDITION ["<<eri<<";"<<erj<<"]!";
			exit(0);
		}
		while(tree.getCurrentNodeValue()!=val){
			tree.back();
		}
		if(c==0){
			parseElement(tokenparse,sav);
		}
	}
	else{
		eri=val.first;
		erj=val.second;
		cout<<"ERROR ON CONDITION ["<<eri<<";"<<erj<<"]!";
		exit(0);
	}
}

void parseElement(vector<vector<token>> tokenparse,pair<int, int>  coor){//cout<<"\nPARS";
	int limc=0;
	int fin=0;
	int i=coor.first;
	int j=coor.second;
	
//	cout<<"TREE EMPTY?"<<tree.isEmpty();

	if (j>=tokenparse[i].size()){
		j=0;
		i++;
	}
	if (i>=tokenparse.size()){
		cout<<"ERROR STOP PROBLEM";
		exit(0);
	}
	
//	cout<<tokenparse[i][j].type<<endl;
	if(tree.isEmpty()==1 and tokenparse[i][j].type!="lim"){
		cout<<"ERROR COUDLN'T START THE PROGRAM";
		exit(0);
	}
	else if(tree.isEmpty()==1 and tokenparse[i][j].type=="lim" and tokenparse[i][j].val==1){
		cout<<"ERROR COUDLN'T START THE PROGRAM";
		exit(0);
	}
	else if(tree.isEmpty()==1 and tokenparse[i][j].type=="lim" and tokenparse[i][j].val==0){
		createTree(tokenparse,make_pair(i,j));
	}
	else if(tree.isEmpty()!=1){
		if (tokenparse[i][j].type=="def"){
			tokenDef(tokenparse,make_pair(i,j),0);
		}
		else if (tokenparse[i][j].type=="oper"){
			tokenOper(tokenparse,make_pair(i,j),0);
		}
		else if (tokenparse[i][j].type=="lim"){
			tokenLim(tokenparse,make_pair(i,j));
		}
		else if (tokenparse[i][j].type=="cond"){
			tokenCond(tokenparse,make_pair(i,j),0);
		}
		else if (tokenparse[i][j].type=="show"){
			tokenShow(tokenparse,make_pair(i,j),0);
		}
		else{
			eri=i;
			erj=j;
			cout<<"ERROR UNKNOWN TOKEN TYPE ["<<eri<<";"<<erj<<"]!";
			exit(0);
		}
		
//		tree.add(0,make_pair(i,j));	
	}
	else{
		cout<<"ERROR UNKNOWN IN PARSER";
		exit(0);
	}	
	
}

BinaryTree parser(vector<vector<token>> tokenparse){
    

//    tree.create(1);
//    tree.add('L', 2);
//    tree.add('R', 3);
//    tree.add('L', 5);
//    tree.add('R', 6);
//
//    tree.printTipsToRoot();
//
//    tree.back();
//    tree.back();
//
//    tree.add('R', 4);
//
//    tree.printTipsToRoot();

	pair<int, int> coor=make_pair(0,0);
	parseElement(tokenparse,coor);
        	
		
//        		define(i,j)
//        	if(tokenparse[i][j].type=="oper" and tokenparse[i].size()-j>=2){
//        		if 
//			}
	

    return tree;
}
