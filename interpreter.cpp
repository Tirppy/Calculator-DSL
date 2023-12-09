struct variable{
	string name;
	int type;
	int vali;
	double valf;
};

vector <variable> allvar;

template <typename T>
bool compare(int comparisonType, T a, T b) {
	if(debug==1){
		cout<<a<<" "<<b<<" "<<comparisonType<<endl;
	}
    if (comparisonType == 0) {
        return a == b;
    } else if (comparisonType == 1) {
        return a > b;
    } else if (comparisonType == 2) {
        return a < b;
    } else if (comparisonType == 3) {
        return a >= b;
    } else if (comparisonType == 4) {
        return a <= b;
    } else {
        return false;
    }
}

void traverseTree(TreeNode* node,vector<vector<token>> tokenparse);

void execute(TreeNode* node,vector<vector<token>> tokenparse){
	token tok=tokenparse[node->data.first][node->data.second];
	if (tok.type=="def"){
		token tok1=tokenparse[node->left->data.first][node->left->data.second];
		token tok2=tokenparse[node->left->left->data.first][node->left->left->data.second];
		for (int i=0;i<allvar.size();i++){
			if (tok1.name==allvar[i].name){
				eri=node->left->data.first;
				erj=node->left->data.second;
				cout<<"ERROR VARIABLE ALREADY EXISTING ["<<eri<<";"<<erj<<"]!";
				exit(0);
			}
		}
		variable var;
		var.name=tok1.name;
		if (tok.val==0){
			var.type=0;
			if(tok2.val==2){
				eri=node->left->left->data.first;
				erj=node->left->left->data.second;
				cout<<"ERROR INVALID VAL ["<<eri<<";"<<erj<<"]!";
				exit(0);
			}
			else if(tok2.val==0){
				int found=0;
				int i;
				for(i=0;i<allvar.size();i++){
					if(allvar[i].name==tok2.name){
						found=1;
						break;
					}
				}
				if (found==0){
					eri=node->left->left->data.first;
					erj=node->left->left->data.second;
					cout<<"ERROR INVALID VAL ["<<eri<<";"<<erj<<"]!";
					exit(0);
				}
				if(allvar[i].type==1){
					eri=node->left->left->data.first;
					erj=node->left->left->data.second;
					cout<<"ERROR INVALID VAL ["<<eri<<";"<<erj<<"]!";
					exit(0);
				}
				var.vali=allvar[i].vali;
			}
			else if(tok2.val==1){
				var.vali=tok2.vali;
			}
		}
		else if (tok.val==1){
			var.type=1;
//			if(tok2.val==1){
//				cout<<"ERROR INVALID VAL";
//				exit(0);
//			}
			if(tok2.val==0){
				int found=0;
				int i;
				for(i=0;i<allvar.size();i++){
					if(allvar[i].name==tok2.name){
						found=1;
						break;
					}
				}
				if (found==0){
					eri=node->left->left->data.first;
					erj=node->left->left->data.second;
					cout<<"ERROR INVALID VAL ["<<eri<<";"<<erj<<"]!";
					exit(0);
				}
				if(allvar[i].type==0){
					var.valf=allvar[i].vali;
				}
				else if(allvar[i].type==0){
					var.valf=allvar[i].valf;
				}
			}
			else if(tok2.val==1){
				var.valf=tok2.vali;
			}
			else if(tok2.val==2){
				var.valf=tok2.valf;
			}
		}
		allvar.push_back(var);
	}
	else if (tok.type=="oper"){
		token tok1=tokenparse[node->left->data.first][node->left->data.second];
		token tok2=tokenparse[node->left->left->data.first][node->left->left->data.second];
		int found=0;
		int i;
		int j;
		for (i=0;i<allvar.size();i++){
			if (tok1.name==allvar[i].name){
				found=1;
				break;
			}
		}
		if(found==0){
			eri=node->left->data.first;
			erj=node->left->data.second;
			cout<<"ERROR INVALID VAL ["<<eri<<";"<<erj<<"]!";
			exit(0);
		}
		
		if (tok.val==0){
			if (tok2.val==0){
				found=0;
				for (j=0;j<allvar.size();j++){
					if (tok2.name==allvar[j].name){
						found=1;
						break;
					}
				}
				if(found==0){
					eri=node->left->left->data.first;
					erj=node->left->left->data.second;
					cout<<"ERROR INVALID VAL ["<<eri<<";"<<erj<<"]!";
					exit(0);
				}
				if (allvar[j].type==0 and allvar[i].type==0){
					allvar[i].vali+=allvar[j].vali;
				}
				else if(allvar[j].type==1 and allvar[i].type==0){//cout<<"1. "<<allvar[i].vali<<" 2. "<<allvar[j].valf<<" 3. ";cout.precision(6);cout<<static_cast<double>(allvar[i].vali)+allvar[j].valf<<endl;
					allvar[i].type=1;
					allvar[i].valf=allvar[i].vali+allvar[j].valf;
				}
				else{
					if(allvar[j].type==1){
						allvar[i].valf+=allvar[j].vali;
					}
					else if(allvar[j].type==2){
						allvar[i].valf+=allvar[j].valf;
					}
				}
			}
			else if (tok2.val==1 and allvar[i].type==0){
				allvar[i].vali+=tok2.vali;
			}
			else if(tok2.val==2 and allvar[i].type==0){
				allvar[i].type=1;
				allvar[i].valf=allvar[i].vali+tok2.valf;
			}
			else{
				if(tok2.val==1){
					allvar[i].valf+=tok2.vali;
				}
				else if(tok2.val==2){
					allvar[i].valf+=tok2.valf;
				}
			}
		}
		else if (tok.val==1){
			if (tok2.val==0){
				found=0;
				for (j=0;j<allvar.size();j++){
					if (tok2.name==allvar[j].name){
						found=1;
						break;
					}
				}
				if(found==0){
					eri=node->left->left->data.first;
					erj=node->left->left->data.second;
					cout<<"ERROR INVALID VAL ["<<eri<<";"<<erj<<"]!";
					exit(0);
				}
				if (allvar[j].type==0 and allvar[i].type==0){
					allvar[i].vali-=allvar[j].vali;
				}
				else if(allvar[j].type==1 and allvar[i].type==0){
					allvar[i].type=1;
					allvar[i].valf=allvar[i].vali-allvar[j].valf;
				}
				else{
					if(allvar[j].type==0){
						allvar[i].valf-=allvar[j].vali;
					}
					else if(allvar[j].type==1){
						allvar[i].valf-=allvar[j].valf;
					}
				}
			}
			else if (tok2.val==1 and allvar[i].type==0){
				allvar[i].vali-=tok2.vali;
			}
			else if(tok2.val==2 and allvar[i].type==0){
				allvar[i].type=1;
				allvar[i].valf=allvar[i].vali-tok2.valf;
			}
			else{
				if(tok2.val==1){
					allvar[i].valf-=tok2.vali;
				}
				else if(tok2.val==2){
					allvar[i].valf-=tok2.valf;
				}
			}
		}
		else if (tok.val==2){
			if (tok2.val==0){
				found=0;
				for (j=0;j<allvar.size();j++){
					if (tok2.name==allvar[j].name){
						found=1;
						break;
					}
				}
				if(found==0){
					eri=node->left->left->data.first;
					erj=node->left->left->data.second;
					cout<<"ERROR INVALID VAL ["<<eri<<";"<<erj<<"]!";
					exit(0);
				}
				if (allvar[j].type==0 and allvar[i].type==0){
					allvar[i].vali*=allvar[j].vali;
				}
				else if(allvar[j].type==1 and allvar[i].type==0){
					allvar[i].type=1;
					allvar[i].valf=allvar[i].vali*allvar[j].valf;
				}
				else{
					if(allvar[j].type==0){
						allvar[i].valf*=allvar[j].vali;
					}
					else if(allvar[j].type==1){
						allvar[i].valf*=allvar[j].valf;
					}
				}
			}
			else if (tok2.val==1 and allvar[i].type==0){
				allvar[i].vali*=tok2.vali;
			}
			else if(tok2.val==2 and allvar[i].type==0){
				allvar[i].type=1;
				allvar[i].valf=allvar[i].vali*tok2.valf;
			}
			else{
				if(tok2.val==1){
					allvar[i].valf*=tok2.vali;
				}
				else if(tok2.val==2){
					allvar[i].valf*=tok2.valf;
				}
			}
		}
		else if (tok.val==3){
			if (tok2.val==0){
				found=0;
				for (j=0;j<allvar.size();j++){
					if (tok2.name==allvar[j].name){
						found=1;
						break;
					}
				}
				if(found==0){
					eri=node->left->left->data.first;
					erj=node->left->left->data.second;
					cout<<"ERROR INVALID VAL ["<<eri<<";"<<erj<<"]!";
					exit(0);
				}
				if(allvar[i].type==0){
					allvar[i].type=1;
					if(allvar[j].type==0){
						allvar[i].valf=allvar[i].vali/allvar[j].vali;
					}
					else if(allvar[j].type==1){
						allvar[i].valf=allvar[i].vali/allvar[j].valf;
					}
				}
				else{
					if(allvar[j].type==0){
						allvar[i].valf/=allvar[j].vali;
					}
					else if(allvar[j].type==1){
						allvar[i].valf/=allvar[j].valf;
					}
				}
			}
			else if(allvar[i].type==0){
				allvar[i].type=1;
				if(tok2.val==1){
					allvar[i].valf=allvar[i].vali/tok2.vali;
				}
				else if(tok2.val==2){
					allvar[i].valf=allvar[i].vali/tok2.valf;
				}
			}
			else{
				if(tok2.val==1){
					allvar[i].valf/=tok2.vali;
				}
				else if(tok2.val==2){
					allvar[i].valf/=tok2.valf;
				}
			}
		}
	}
    else if (tok.type=="show"){
    	token tok1=tokenparse[node->left->data.first][node->left->data.second];
		int found=0;
		int i;
		for (i=0;i<allvar.size();i++){
			if (tok1.name==allvar[i].name){
				found=1;
				break;
			}
		}
		if(found==0){
			eri=node->left->data.first;
			erj=node->left->data.second;
			cout<<"ERROR INVALID VAL ["<<eri<<";"<<erj<<"]!";
			exit(0);
		}
		cout<<allvar[i].name<<"=";
		if(allvar[i].type==0){
			cout<<allvar[i].vali<<endl;
		}
		else if(allvar[i].type==1){
    		cout<<setprecision(prec)<<allvar[i].valf<<endl;
		}
		else{
			cout<<"ERROR";
		}
	}
	else if (tok.type=="cond"){
		token tok1=tokenparse[node->left->data.first][node->left->data.second];
		token tok2=tokenparse[node->left->left->data.first][node->left->left->data.second];
		token tok3=tokenparse[node->left->left->left->data.first][node->left->left->left->data.second];
		int found=0;
		int i;
		int j;
		double val1;
		double val2;
		for (i=0;i<allvar.size();i++){
			if (tok2.name==allvar[i].name){
				found=1;
				break;
			}
		}
		if(found==0){
			eri=node->left->left->data.first;
			erj=node->left->left->data.second;
			cout<<"ERROR INVALID VAL ["<<eri<<";"<<erj<<"]!";
			exit(0);
		}
		if (allvar[i].type==0){
			val1=static_cast<double>(allvar[i].vali);
		}
		else if (allvar[i].type==1){
			val1=allvar[i].valf;
		}
		if (tok3.val==1){
			val2=static_cast<double>(tok3.vali);
		}
		else if (tok3.val==2){
			val2=tok3.valf;
		}
		else if (tok3.val==0){
			for (j=0;j<allvar.size();j++){
				if (tok2.name==allvar[j].name){
					found=1;
					break;
				}
			}
			if(found==0){
				eri=node->left->left->data.first;
				erj=node->left->left->data.second;
				cout<<"ERROR INVALID VAL ["<<eri<<";"<<erj<<"]!";
				exit(0);
			}
			if(allvar[j].type==0){
				val2=static_cast<double>(allvar[j].vali);
			}
			else if(allvar[j].type==1){
				val2=allvar[j].valf;
			}
		}
		if (tok.val==0){
			if (compare(tok1.val,val1,val2)){
				if(debug==1){
					cout<<"YAS"<<endl;
				}
				traverseTree(node->left->left->left->right,tokenparse);
			}
			else{
				if(debug==1){
					cout<<"NO"<<endl;
				}
			}
		}
		else if (tok.val==1){
			while (compare(tok1.val,val1,val2)){
				if(debug==1){
					cout<<"YAS"<<endl;
				}
				traverseTree(node->left->left->left->right,tokenparse);
				if (allvar[i].type==0){
					val1=static_cast<double>(allvar[i].vali);
				}
				else if (allvar[i].type==1){
					val1=allvar[i].valf;
				}
			}
		}
	}
}

void traverseTree(TreeNode* node,vector<vector<token>> tokenparse) {
    if (node != nullptr) {
		if(debug==1){
			cout<<"exec "<<tokenparse[node->data.first][node->data.second].type<<tokenparse[node->data.first][node->data.second].val<<endl;
		}
//        std::cout << "L--" << node->data.first << "," << node->data.second << std::endl;  // Process the current node
		
		execute(node,tokenparse);

//        if (node->left != nullptr) {
////            std::cout << "    ";
//            traverseTree(node->left,tokenparse);  // Recursively traverse the left subtree
//        }

        if (node->right != nullptr) {
//            std::cout << "    R--" << node->right->data.first << "," << node->right->data.second << std::endl;
//            std::cout << "        ";
            traverseTree(node->right,tokenparse);  // Recursively traverse the right subtree
        }
    }
}


TreeNode* globalTreeRoot = nullptr;

void interpreter(vector<vector<token>> tokenparse){
	
	traverseTree(tree.getRoot(),tokenparse);
	
	if(debug==1){
		for(int i=0;i<allvar.size();i++){
			cout<<allvar[i].name<<" = "<<allvar[i].type<<"-"<<allvar[i].vali<<" | "<<allvar[i].valf<<endl;
		}
	}

//	cout<<endl<<"TEST:"<<findNMovesToLeft(tree.getRoot()->right->right->right,2).first<<findNMovesToLeft(tree.getRoot()->right->right->right,2).second;
}
