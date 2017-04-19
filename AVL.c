#include <stdio.h>
#include <stdlib.h>
#define MAX(x,y)    (x)>(y)?(x):(y)

/***************
#findMinimumAVL
#findMaximumAVL
#insertAVL
#deleteAVL
****************/
struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    unsigned int height;
};

int height(struct Node* node){
    if(!node) return 0;
    return node->height;
}

int heightbalance(struct Node* nd){
    if(!nd) return 0;
    return (height(nd->left)-height(nd->right));
}


//Helper functions for rebalancing through rotations
struct Node* leftRotation(struct Node* node){
	struct Node* temp = node->right;
	//swing pointers
	node->right = temp->left;
	temp->left = node;
	//update heights
	node->height = MAX(height(node->left),height(node->right))+1;
	temp->height = MAX(height(temp->left),height(temp->right))+1;
	return temp;
}

struct Node* rightRotation(struct Node* node){
	struct Node* temp = node->left;
	//swing pointers
	node->left = temp->right;
	temp->right = node;
	//update heights
	node->height = MAX(height(node->left),height(node->right))+1;
	temp->height = MAX(height(temp->left),height(temp->right))+1;
	return temp;
}

struct Node* findMinimumAVL(struct Node* root){
	if(!root) return root;

	struct Node* retnode;
	if(root->left){
		retnode=findMinimumAVL(root->left);
	}else{
		retnode = root;
	}
	
	return retnode;
    
}

struct Node* findMaximumAVL(struct Node* root){
	if(!root) return root;
    
	struct Node* retnode;
	if(root->right){
		retnode=findMaximumAVL(root->right);
	}else{
		retnode = root;
	}
	return retnode;
    
}

struct Node* insertAVL(struct Node* root,int value){
	if(!root){
		struct Node* newNode = (struct Node *)malloc(sizeof(struct Node));
		newNode->data = value;
		newNode->left= NULL;
		newNode->right = NULL;
		newNode->height = 1;
		return newNode;
	}
	if((root->data)<value) 
		root->right = insertAVL(root->right,value);
	else  
		root->left =  insertAVL(root->left,value);
    
	//traverse and update heights along the path that the node was inserted
	//printf("MAX height: %d",MAX(height(root->left),height(root->right)));
	root->height =MAX(height(root->left),height(root->right))+1;
	//printf("In insert: data:%d   ht:%d\n",root->data,root->height);
	int ht_bal=0;
	ht_bal = heightbalance(root);
    
	if((ht_bal < -1) && (value>(root->right)->data)){       //rotate left
		return leftRotation(root);
	}
	else if((ht_bal > 1) && (value<=(root->left)->data)){   //rotate right
		return rightRotation(root); 
	}
	else if((ht_bal > 1) && (value>(root->left)->data)){    //rotate left right
		root->left = leftRotation(root->left);
		return rightRotation(root);
	}
	else if((ht_bal < -1) && (value<=(root->right)->data)){    //rotate right left
		root->right = rightRotation(root->right);
		return leftRotation(root);
	}    
	return root;
}

struct Node* deleteAVL(struct Node* root, int value){
	if(!root) return root;

	if((root->data)<value) 
		root->right = deleteAVL(root->right,value);
	else  
		root->left =  deleteAVL(root->left,value);

	if(root->data == value){
		if((!root->left) && (!root->right)){				//leaf node
			free(root);
		}
		else if((root->left != NULL) && (root->right == NULL)){		//only left child
			struct Node* temp = root->left;
			*root = *temp;				
			free(temp);
		}
		else if((root->left == NULL) && (root->right != NULL)){		//only right child
			struct Node* temp = root->right;
			*root = *temp;
			free(temp);
		}
		else{								//Both children present
			struct Node* temp = findMinimumAVL(root->right);
			root->data = temp->data;
			root->right = deleteAVL(root->right,temp->data);
		}
	}

	if(!root) return root;
	root->height =MAX(height(root->left),height(root->right))+1;
	
	int ht_bal=0;
	ht_bal = heightbalance(root);
    
	if((ht_bal < -1) && (value>(root->right)->data)){       //rotate left
		return leftRotation(root);
	}
	else if((ht_bal > 1) && (value<=(root->left)->data)){   //rotate right
		return rightRotation(root); 
	}
	else if((ht_bal > 1) && (value>(root->left)->data)){    //rotate left right
		root->left = leftRotation(root->left);
		return rightRotation(root);
	}
	else if((ht_bal < -1) && (value<=(root->right)->data)){    //rotate right left
		root->right = rightRotation(root->right);
		return leftRotation(root);
	}
    
	return root;

}

//Test program
int main(){

    struct Node* root = NULL;
    struct Node* temp = NULL;
    
    root = insertAVL(root,1);
    root = insertAVL(root,2);
    root = insertAVL(root,3);
    root = insertAVL(root,4);
    root = insertAVL(root,5);
    root = insertAVL(root,6);
    temp = findMinimumAVL(root);
    printf("%d\t%d\n",root->data,root->right->data);
    printf("ht bal: %d\n",heightbalance(root));
    printf("Minimum:%u\n",temp->data);	    
    temp = findMaximumAVL(root);
    printf("Maximum:%u\n",temp->data);

    root = deleteAVL(root,4);
	temp = findMaximumAVL(root);
	printf("%d\t\n",root->data);
	printf("ht bal: %d\n",heightbalance(root));
    printf("Maximum:%u\n",temp->data);

/*
	printf("%d\n",root->data);
	printf("%d\t\t%d\n",root->left->data,root->right->data);
	printf("%d\t%d\n",root->left->left->data,root->left->right->data);
*/
    return 0;
}

