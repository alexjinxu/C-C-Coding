//============================================================================
// Name        : ArrayManipulationCPP.cpp
// Author      : ax
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
using namespace std;

typedef struct Node{
    int nodePos;
	struct Node *pre;
	struct Node *next;
	float num;
}NODE;

class ChainManage{

private:
	NODE * HeadChain;
	NODE * EndChain;

public:

	int   size;
	bool  isCreated;

	ChainManage():size(-1), isCreated(false),EndChain(NULL), HeadChain(NULL){}
	bool  endInsertNode(float num);
	bool  sortChain(int dir);
	bool  dispayChain(int dir);
	int   findNode(float target);
    float findMaxMin(int k);
    bool  deleteNode(float target);
    bool  setChainSize(int k);
    NODE* getHeadandEndPointer(int k);
    void  restAllmember();
};


void ChainManage::restAllmember()
{
	HeadChain = EndChain = NULL;
	isCreated = false;
	size = -1;
}



/*
 *  k: 1 means return HeadChain
 *  k: -1 means return EndChain
 * */

NODE* ChainManage::getHeadandEndPointer( int k)
{
	if ( k ==1 )
	{
		return HeadChain;
	}
	else if (k == -1)
	{
		return EndChain;
	}

	return NULL;
}


bool ChainManage::setChainSize(int k)
{
	size = k;
	return true;

}

bool ChainManage::endInsertNode(float num)
{
	if (HeadChain == NULL && EndChain == NULL && isCreated == false)
	{
        NODE * temp = new NODE;
        if (temp == NULL) return false;
        temp->nodePos = 1;
        temp->num = num;
        temp->pre = temp;
        temp->next = temp;
        isCreated = true;
        EndChain = HeadChain = temp;

	}
	else if (EndChain == HeadChain && isCreated == true)
	{
		NODE * temp = new NODE;
		if (temp == NULL) return false;
		temp->nodePos = HeadChain->nodePos + 1 ;
		temp ->num = num;
        temp->next = HeadChain;
        EndChain->next =temp;
        temp->pre = EndChain;
        EndChain = temp;
        HeadChain->pre = EndChain;

	}
	else if (EndChain != HeadChain && isCreated == true)
	{
		NODE * temp = new NODE;
		if (temp == NULL) return false;
		temp->num = num;
		temp->nodePos = EndChain->nodePos + 1 ;
		EndChain->next =temp;
		temp->pre = EndChain;
		temp->next = HeadChain;
		EndChain = temp;
		HeadChain->pre = EndChain;

	}


   return true;
}

/*
 *  dir :  1 means ascending
 *  dir : -1 means descending
 * */

NODE * ComparedAndMerge(NODE * leftP, NODE * rightP, int dir)
{
  NODE head;
  NODE* nodeP;
  nodeP = &head;

  while (leftP != NULL && rightP != NULL)
  {
	  if(leftP->num <= rightP->num)
	  {
		  if(dir == 1)
		  {
			  nodeP->next =leftP;
			  leftP = leftP->next;
		  }
		  else if (dir == -1)
		  {
			  nodeP->next =rightP;
			  rightP = rightP->next;
		  }
	  }
	  else
	  {
		  if(dir == 1)
		  {
			  nodeP->next = rightP;
			  rightP=rightP->next;
		  }
		  else if (dir == -1)
		  {
			  nodeP->next = leftP;
			  leftP=leftP->next;
		  }
	  }

	  nodeP=nodeP->next;
  }
  nodeP->next = (leftP == NULL)? rightP: leftP;
  return head.next;
}


/*
 The dir is used to indication the order of sort.
  1: ascending sort
 -1: descending sort
*/
NODE* sortList(NODE *Head , int dir)
{
 NODE *slowP ,* fastP;
 NODE *leftSegP,* rightSegP;


 if(Head == NULL || Head->next == NULL)
 {
	 return Head;
 }

 slowP = Head;
 fastP = Head->next;


 while (fastP != NULL && fastP->next != NULL)
 {
	 slowP = slowP->next;
	 fastP = fastP->next->next;
 }

 fastP=slowP->next;
 slowP->next=NULL;

 leftSegP=Head;
 rightSegP=fastP;

 leftSegP  = sortList(leftSegP, dir);
 rightSegP = sortList(rightSegP, dir);

 return ComparedAndMerge (leftSegP, rightSegP ,dir);
}

/*
 The dir is used to indication the order of sort.
  1: ascending sort
 -1: descending sort
*/
bool ChainManage::sortChain( int dir)
{
	NODE *nodeP, *nodePreP;
	int i =1;

    if (HeadChain != EndChain)
    {
    	EndChain->next = NULL; //make the loop chain become a single chain.
    }
    else
    {
    	return true;
    }
	if(isCreated == true)
	{

		HeadChain=sortList(HeadChain,dir);


		nodePreP = HeadChain;
		nodePreP->nodePos =i;
        nodeP=HeadChain->next;

	   do
	    {
		    nodeP->nodePos= ++i ;
		    nodeP->pre = nodePreP;
		    nodePreP = nodePreP->next;
		    nodeP = nodeP->next;

	    } while ( nodeP != NULL );


	   EndChain = nodePreP;
	   EndChain->next = HeadChain;
	   HeadChain->pre = EndChain;

		return true;
	}

	return false;
}
bool ChainManage::deleteNode(float target)
{

  Node * temp = NULL;
 // Node * tempPos=NULL;
  bool isFound = false;

  if(isCreated == false)
  {
	  return false;
  }
  else
  {
	  if (HeadChain != EndChain)
	  {

		  temp = HeadChain;


		  do{
			  if(temp->num == target && isFound == false)
			  {
				  temp->num = temp->next->num;
				  isFound = true;
			  }
			  else if(isFound == true)
			  {
				  temp->num = temp->next->num;
			  }

			  temp = temp->next;

		  }while (temp != HeadChain);

           temp = HeadChain->pre;

          if (isFound == true)
          {
              EndChain = temp->pre;
        	  EndChain->next = HeadChain;
        	  HeadChain->pre = EndChain;
        	  delete(temp);
        	  size--;
              return true;
          }
          else
          {
        	  return false;
          }


	  }
	  else
	  {
		  temp = HeadChain;
		  if(temp->num == target)
		  {
			  HeadChain = EndChain= NULL;
			  isCreated = false;
			  delete(temp);
			  size--;
		  }
	  }
  }
   return true;
}
/*
 The dir is used to indication the sequence.
  1: display order is from head to end.
 -1: display order is from end to head.
*/
bool ChainManage::dispayChain(int dir)
{

	NODE * nodeP;
	if (dir ==1 )
	{
		nodeP = HeadChain;
		cout<<"Printing the array"<<endl;
	}
	else if (dir == -1)
	{
		nodeP = EndChain;
		cout<<"Reverse Printing the array"<<endl;
	}

	if(isCreated == true && HeadChain != EndChain )
	{

		if (dir == 1)
		{

			do{
				cout << setprecision(4)<<nodeP->num<<" ";
				nodeP = nodeP->next;
			}while(nodeP != HeadChain );

           cout<<endl;
		}
		else if (dir == -1)
		{
			do{
				cout<< setprecision(4) <<nodeP->num<<" ";
				nodeP = nodeP->pre;
			}while(nodeP != EndChain );

			cout<<endl;
		}
	}
	else if (isCreated == true && HeadChain == EndChain)
	{
		cout << setprecision(4) <<nodeP->num<<endl;
	}
	else  if(isCreated == false)
	{
		cout<<"!!!The array is not set!!!"<<endl;
	}
	return true;
}

/*
 * int k used to indicate find a max or min
 *
 * k == -1 : means min
 * K == 1  : means max
 * */


float ChainManage::findMaxMin(int k)
{
    NODE * nodeP = HeadChain;

	float temp = HeadChain ->num;
    if(isCreated == true)
    {
    	do{

    		nodeP = nodeP->next;
    		if (k == -1)
    		{
    			if( temp > nodeP->num) temp = nodeP->num;
    		}
    		else if ( k == 1)
    		{
    			if( temp < nodeP->num) temp = nodeP->num;
    		}

    	}while (nodeP->next != HeadChain );
    }

	return temp;
}



int ChainManage::findNode(float target)
{
	NODE* nodeP = HeadChain;

	if(isCreated == true)
	{
		do{

		   if(target == nodeP->num)
		   {
			   return nodeP->nodePos;
		   }
		   else
		   {
			   nodeP=nodeP->next;
		   }

		}while(nodeP!= HeadChain);

	   return -1;
	}

	return -2;
}

void GUIprint(void)
{
	cout << "1- Enter the size of the array                      " << endl; //
	cout << "2- Enter the array elements                         " << endl; //
	cout << "3- Sort the array                                   " << endl; //
	cout << "4- Find a number within the array                   " << endl; //
	cout << "5- Print the array                                  " << endl; //
	cout << "6- Reverse print the array                          " << endl; //
	cout << "7- Print array statistics (min, max, average, total)" << endl; //
	cout << "8- Delete a target in array                         " << endl; //
	cout << "9- Quit                                             " << endl; //

}

class GUIinterface:public ChainManage
{

  public :
	void InitialArray();
	void CreateArrayElements();
	void SortArray();
	void FindEleminArray( float tar);
	void PrintArray(int k);
	void PrintArrayStatistics();
	void ResetArray();
	void PrintStatics();
	void DeleteNode(float tar);

};

void GUIinterface::DeleteNode(float tar)
{
	if(deleteNode(tar) == false)
	{
		cout<<"The target does not found in array!"<<endl;
	}
	else if(deleteNode(tar) == true)
	{
        cout<<"Target "<<tar<<" was deleted in array!"<<endl;

	}
	dispayChain(1); //display the array from head to end
}

void GUIinterface::InitialArray()
{
    int temp;
    NODE * nodeP, tempNode;

	cout<<"What is the size of your array (1-20)? >"<<endl;

	cin>> temp;

	if (temp > 20  || temp <1)
	{
	   cout<<"Array size should be between 1 and 20 "<<"\n"<<endl;
	}
	else
	{
		if (size != -1 )
		{
          nodeP=getHeadandEndPointer(-1);
          nodeP->next=NULL;
          nodeP=getHeadandEndPointer(1);
          do
          {
        	  tempNode.next = nodeP->next;
        	  delete(nodeP);
        	  nodeP=tempNode.next;
          }while(nodeP != NULL);

          restAllmember();

		}

		setChainSize(temp);

		cout<<"Array size set"<<"\n"<<endl;
	}



}

void GUIinterface::CreateArrayElements()
{
	int i;
	float temp;
    if (size <=0)
    {
    	cout<<"!!!The array size is not set!!!"<<endl;
    }
    else if (size <= 20 && size > 0)
    {
    	for (i = 0; i < size; i ++)
    	{
    		cout<<"Enter array element"<<i+1<<":";
    		cin >>temp;
    		endInsertNode(temp);
    	}

    	cout<<"Array elements have been received"<<"\n"<<endl;
    }
}

void GUIinterface::SortArray()
{
    char charactor;
    int dir = 0;
	bool exitLoop = false;
    if (isCreated == false)
    {
    	cout<<"!!!The array is not set!!!"<<endl;
    }
    else
    {
    	do {

    		cout<<"Sorting the array"<<"\n"<<"Please choose Ascending/Descending (A/D) >";

    		cin>>charactor;

    		if (charactor == 'A')
    		{
			    dir  = 1;
			    cout<<"Array sorted (Ascending)"<<endl;
			    exitLoop = true;
    		}
    		else if (charactor == 'D')
    		{
		    	dir  = -1;
		    	cout<<"Array sorted (Descending)"<<endl;
		    	exitLoop = true;
    		}
    		else
    		{
		    	cout<<"That's not a valid choice"<<endl;
    		}

    		}while(! exitLoop);


    	sortChain(dir);

    	dispayChain(1); //display the array from head to end
    }
}

void GUIinterface::PrintArray(int k)
{
	dispayChain(k);

}

void GUIinterface::FindEleminArray (float tar)
{
     int targetPos = -1;
     targetPos = findNode(tar);


     if (targetPos == -1)
     {
    	 cout<<tar<<" was not found at the array!"<<endl;
     }
     else if (targetPos == -2)
     {
    	 cout<<"!!!The array is not set!!!"<<endl;
     }
     else
     {
    	 cout<<tar<<" was found at the position "<<targetPos<<" in the array!"<<endl;
     }
 }


void GUIinterface::PrintArrayStatistics()
{
	float Max, Min, Total, Average;
    int num = 0;
	NODE * nodeP;
    if (isCreated == true)
    {
    	Max=findMaxMin(1);

    	Min=findMaxMin(-1);

    	Total =0;

    	nodeP = getHeadandEndPointer(1);

    	do{
    		Total += nodeP->num;
    		nodeP=nodeP->next;
            ++num;
    	}while(nodeP != getHeadandEndPointer(1));


    	Average = Total/num;

    	cout<<"Min: "<<Min<<endl;
    	cout<<"Max: "<<Max<<endl;
    	cout<<"Total: "<<Total<<endl;
    	cout<<"Average: "<<Average<<endl;
    }else
    {
    	cout<<"!!!The array is not set!!!"<<endl;
    }
}

int main() {

	GUIinterface ChainInst;

	bool exitLoop = false;
    int choose = 0;
    string Input;

	do{
		GUIprint();
        cout<<"Please enter your choice:";

        cin>> Input;

        if(Input[1] == '\0' && (Input[0] >='0' && Input[0]<='9'))
        {
        	choose =Input[0]-'0';
        }
        else
        {
        	choose = 0;
        }

		switch(choose)
		{
			case 1:
				ChainInst.InitialArray();
				break;
			case 2:
				ChainInst.CreateArrayElements();
				break;
			case 3:
				ChainInst.SortArray();
				break;
			case 4:
				float target;
				cout<<"Please enter a number to be searched in the array:"<<endl;
				cin>>target;
                ChainInst.FindEleminArray(target);
				break;
			case 5:
				ChainInst.PrintArray(1);
				break;
			case 6:
				ChainInst.PrintArray(-1);
				break;
			case 7:
				ChainInst.PrintArrayStatistics();
				break;
			case 8:
				cout<<"Please enter the number that you want to delete:"<<endl;
				cin>>target;
				ChainInst.DeleteNode(target);
				break;
			case 9:
				exitLoop = true;
				break;
			default:
				cout<<"!!!The number is out of the options!!!"<<"\n"<<endl;
				cout<<"!!!Please chose the correct number!!! "<<"\n"<<endl;
				break;
		}



	}while (( !exitLoop));

	cout << "!!!Thanks your for using the APP!!!" << endl; //
	return 0;
}
