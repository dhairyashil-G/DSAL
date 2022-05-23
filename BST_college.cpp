#include<iostream>
using namespace std;
class tnode
{
    int data;
    tnode *left,*right;
    public:
        tnode()
        {
            data=0;
            right=NULL;
            left=NULL;
        }
        tnode(int x)
        {
            data=x;
            right=NULL;
            left=NULL;
        }
        friend class Btree;
};

class Btree
{
    tnode *root;
    public:
        Btree()
        {
            root=NULL;
        }
        void insert(int val,tnode* root);
        tnode* create(int val);
	void preorder_rec(tnode* root);
	void min(tnode* root);
	void max(tnode* root);
	void mirror(tnode* root);
	tnode* deletion(tnode* root,int x);

};
tnode* Btree::create(int val)
{
    root=new tnode(val);
    return root;
}
void Btree::insert(int val,tnode* root)
{
    tnode *temp;
    int flag=0;
    temp=root;
    while(flag==0)
    {
        if(val<temp->data)
        {
            if(temp->left==NULL)
            {
                temp->left =new tnode(val);
                flag=1;
            }
            else
            {
                temp=temp->left;
            }
        }
        else if(val>temp->data)
        {
            if(temp->right==NULL)
            {
                temp->right=new tnode(val);
                flag=1;
            }
            else
            {
                temp=temp->right;
            }
        }
    }
}

void Btree::preorder_rec(tnode* root)
{
    if(root!=NULL)
    {
        cout<<root->data<<endl;
        preorder_rec(root->left);
        preorder_rec(root->right);
    }
    return;
}

void Btree::min(tnode* root)
{ 
    tnode* temp;
    temp=root;
    while(temp->left!=NULL)
	{
		temp=temp->left;
	}
    cout<<"Minimum element is: "<<temp->data;

}


void Btree::max(tnode* root)
{ 
    tnode* temp;
    temp=root;
    while(temp->right!=NULL)
	{
		temp=temp->right;
	}
    cout<<"Minimum element is: "<<temp->data;
}

void Btree::mirror(tnode* root)
{

	if(root!=NULL)	
	{	
		tnode* temp_left;
		temp_left=root->left;
		root->left=root->right;
		root->right=temp_left;
		mirror(root->left);
		mirror(root->right);
	}
}
tnode* Btree::deletion(tnode* root,int x)
{
	tnode* travel=root;
	tnode* temp;
	if(travel==NULL)
	{
	   cout<<"No value to delete"<<endl;
	   return root;
	}
	else if(travel->data>x)
	{
		travel->left=deletion(travel->left,x);
	}
	else if(travel->data<x)
	{
		travel->right=deletion(travel->right,x);
	}
	else 
	{
		if(travel->left==NULL && travel->right==NULL)
		{
			return NULL;
			
		}
		else if(travel->left==NULL)
		{
			temp=root->right;
			travel->right=NULL;
			travel->left=NULL;
			return temp;
		}
		else if(travel->right==NULL)
		{
			temp=root->left;
			travel->right=NULL;
			travel->left=NULL;
			return temp;
		}
		
		tnode* curr=root;
		curr=curr->left;
		while(curr && curr->right!=NULL)
			curr=curr->right;
		temp=curr;		

		travel->data=temp->data;
		travel->left=deletion(travel->left,temp->data);
	}
	return travel;
	

}

int main()
{
    Btree b;
    int ch=1;
    int choice=0;
    int val,x;
    tnode* temp_root;
    while(choice!=7)
   {
       cout<<"Enter:\n1)To create a Binary Search tree\n2)For Preorder rec Traversal : .\n3)Minimun\n4)Maximun\n5)Mirror\n6)Deletion\n7)Exit\n\t :";
       cin>>choice;
        switch(choice)
        {
            case 1:
            {
                cout<<"Enter first element of Btree : ";
                cin>>val;
                temp_root=b.create(val);
                cout<<"Enter 1 to continue & 0 to stop:";
                cin>>ch;
                while(ch!=0)
                {
                    cout<<"Enter No. to be added in Btree : ";
                    cin>>val;
                    b.insert(val,temp_root);
                    cout<<"Enter 1 to continue & 0 to stop:";
                    cin>>ch;
                }
                break;
            }
           case 2:
		cout<<"Pre-order Recursive Traversal:"<<endl;
                b.preorder_rec(temp_root); 
           case 3:
		b.min(temp_root);
                break;
	   case 4:
		b.max(temp_root);
		break;
	   case 5:
		b.mirror(temp_root);
		break;
	   case 6:
	   {
		cout<<"Enter no. to be deleted : ";
		cin>>x;
		temp_root=b.deletion(temp_root,x);
	   }
	   case 7:
		
		break;
            default:
                cout<<"Invalid Input";
                break;
        }   
    }

  return 0;
}