/*
19K-0171	SUMEET KUMAR
19K-0169	SONU KUMAR
19K-1491	AMAN SOOFI
*/
#include<iostream>
#include<string>
#include<sstream>
#include<stdlib.h>
#include<cmath>
#include<unistd.h>
#include<fstream>
using namespace std;

// Global variables;
int ***nfa_without_null;
int **number_of_trans_nfa;
int *final_states;
int numof_final_states;
//queue
class Node{
	public:
	int *state;
	int count;	//number of states to make 1 state
	Node *next;
};

class Queue{
	Node *head,*tail;
	int num_of_nodes;
	public:
		Queue(){
			head = NULL;
			tail = NULL;
			num_of_nodes = 0;
		}
		
		void push(int *data,int n){
			
			if(data != NULL)
		{
			Node *temp = new Node;
			temp->state = data;
			temp->count = n;
			temp->next = NULL;
			num_of_nodes++;
			
			if(head == NULL){
				head = temp;
				tail = temp;
			}
			else{
				tail->next = temp;
				tail = tail->next;
			}
		}
		
		}
		
		int* pop(int *n)
		{
			if(head != NULL)
			{
				Node *temp = head;
				*n = temp->count;
				head = head->next;
				temp->next = NULL;
				num_of_nodes--;
				return temp->state;
			}
			else{
				*n=0;
			return NULL;
			}
		}
		
		bool isempty()
		{
			if(num_of_nodes == 0)
				return true;
			else
				return false;
		}
};

class nfa
{
   public:
   bool check_null;
   int n_trans,n_symbols;                                     
   int **fa,*input_tansitions;
   char *input_symbol;	
   nfa()
   {
   	 check_null = false;
   	 n_trans = 0; 
   	 n_symbols = 0;
   }
   void nfa_input(ifstream &input,int n_states,int n_symbols)
  {	
	int i = 0,j = 0;
    this->n_symbols = n_symbols;

	input_symbol = new char[n_symbols];
	
	input_symbol[i] = 'a';
	for(i = 0;i<n_symbols;i++)
	{
		cout<<input_symbol[i]<<" "; 
		input_symbol[i+1] = input_symbol[i] + 1;
	}
	cout<<endl;
	
	//number of NULL transitions
	input>>n_trans;
	if(n_trans > 0)
	{
		check_null = true;
		fa = new int*[n_symbols+1];
		input_tansitions = new int[n_symbols+1];
		input_tansitions[0] = n_trans;
		fa[0] = new int[n_trans];
		//cout<<"\t\tEnter the state number starting i.e 0 - Q0,1 -Q1: "<<endl;
	    for(j = 0;j<n_trans;j++)
	     {
			input>>fa[0][j]; 
		 }
		 cout<<endl;
	}
	else
	{
	 fa = new int*[n_symbols];
	 input_tansitions = new int[n_symbols];
	 check_null = false;
    }

    int k =0;
    if(check_null)
    k = 1; // this is because if null transitions occur then i have to start read symbol from index 1
    else
    k = 0; // read above if not the start index should be 0
	        
					                           
	for(i = k;i<n_symbols+k;i++)
	{
		//cout<<"\t\tEnter the number of transitions of input label:  "<<input_symbol[i-k]<<" ";
		input>>n_trans;
		input_tansitions[i] = n_trans;
		fa[i] = new int[n_trans];
		//cout<<"\t\tEnter the state number starting i.e 0 - Q0,1 -Q1: ";
	    for(j = 0;j<n_trans;j++)
		    input>>fa[i][j]; 
	}
	
	
}


};

// function Decleration
void Convert_NfaNull_to_Nfa(nfa n[],int n_states,int n_symboles);
void Convert_Nfa_to_Dfa(int n_states,int n_symboles);
int* Find_Union_of_states(int* arr,int &states_count,int i);
string convert_num_into_string(int *temp,int count);


bool compare(string s1,string s2)
{
	int x = s1.compare(s2);
	if(x!=0)
		return false;
	else
		return true;
}


int main()
{
	cout<<"\n\n\n\t\t\t-------------NULL NFA TO DFA--------------------"<<endl;
	
	ifstream input("input_file.txt");
  	if(!input)
  	{
  		cout<<"cannot open input file";
		 exit(0);	
	}
	
	int n_states = 0,i_symbols = 0,i=0,j=0;
	//cout<<"\t\tEnter the number of states: ";
	input>>n_states;
	//cout<<"\t\tEnter how many input symbols are there: ";
	input>>i_symbols;
	
	//cout<<"\t\tStates labels: "<<endl;
	for(j = 0;j<n_states;j++)
	{
		cout<<"  Q"<<j<<"  ";
	}

	nfa n[n_states];
	for(i = 0;i<n_states;i++)
	{
	//cout<<"\t\tAt  Q"<<i<<"  ";
	n[i].nfa_input(input,n_states,i_symbols);
    system("cls");
	}
	

//	cout<<"\t\tEnter number of Final States:";
	input>>numof_final_states;
	if(numof_final_states > n_states)
	{
		cout<<"\t\tFinal States cannot be greater than Total States";
		exit(0);
	}
	final_states = new int[numof_final_states];
	for(i = 0 ; i < numof_final_states ; i++)
	{
		input>>final_states[i];
	}
	
   Convert_NfaNull_to_Nfa(n,n_states,i_symbols);
   sleep(2);
   //printing NFA
   cout<<"\t\t--------------NFA TRANSITION TABLE--------------------"<<endl;
   int k = 0;
   char alphabet = 'a';
   for(i=0;i<i_symbols;i++)
   {
   	    cout<<"\t\t"<<(char)(alphabet + i)<<endl;
   	    for(j=0;j<n_states;j++)
   	    {
   	    	cout<<"\t\tQ"<<j<<" ";
   	    	for(k=0;k<number_of_trans_nfa[i][j];k++)
   	    	cout<<nfa_without_null[i][j][k];
   	    	
   	    	cout<<endl;
		}
		cout<<endl;	
   }
   
   sleep(2);
   
   Convert_Nfa_to_Dfa(n_states,i_symbols);

	input.close();
	return 0;
}

int* Find_Union_of_states(int* arr,int &states_count,int i)
    {
	    int j =0,k =0,l =0,m= 0,count = 0; 
	    int *temp,previous=0;
	    
		if(arr == NULL || states_count == 0)
	    return NULL;
	    
	     for(j = 0;j<states_count;j++)
	     {
	     	count = count + number_of_trans_nfa[i][arr[j]];	
		 }
		 if(count == 0)
		 	{
		 		states_count = 0;
				return NULL;
			}
		 temp = new int[count];
		 for(j = 0;j<states_count;j++)
		 {
		    for(k = previous;k<number_of_trans_nfa[i][arr[j]]+previous;k++)
			{
			   temp[k] = nfa_without_null[i][arr[j]][k-previous];
		 		
			}	
			previous = k;
		 }
		 
		 // removing duplicate from array and then update the count and the array
		 for(k=0; k<count; k++)
		    {
		        for(l=k+1; l<count; l++)
		        {
		            //If any duplicate found */
		            if(temp[k] == temp[l])
		            {
		                // Delete the current duplicate element
		                for(m=l; m<count; m++)
		                {
		                    temp[m] = temp[m + 1];
		                }
		 
		                //Decrement size after removing duplicate element
		                count--;
		 
		                // If shifting of elements occur then don't increment j
		                l--;
		            }
		        }
			}
			// now sorting the array
			for(k=0;k<count;k++)
			{		
				for(l=k+1;l<count;l++)
				{
					if(temp[k]>temp[l])
					{
						int temp_data  = temp[k];
						temp[k]= temp[l];
						temp[l]=temp_data;
					}
				}
			}
			states_count = count;
			return temp;
//			for(k = 0;k<count;k++)
//			{
//				cout<<temp[k]<<" ";
//			}
			
	}	// now firstly the temp and cout is for the input symbol and for second time it is for next symbol and so on

string convert_num_into_string(int *temp,int count)
{
	string str;
    stringstream ss;  
  	for(int i = 0;i<count;i++)
  		{
    	ss << temp[i];  
  		} 
    ss >> str;
    return str; 	
}
void Convert_NfaNull_to_Nfa(nfa n[],int n_states,int n_symboles)
{
	int i=0,j=0,k = 0,l = 0,m =0;
	int **temp,**temp2,**temp3;
	temp = new int*[n_states];
	temp2 = new int*[n_states];
	temp3 = new int*[n_states];
	nfa_without_null = new int**[n_symboles];
	number_of_trans_nfa = new int*[n_symboles];
	char alphabet = 'a';
	
	cout<<"\t\t------------NFA NULL TO NFA TRANSITION FUNCTION------------------"<<endl; 
	for(i = 0;i<n_symboles;i++)
	{
		cout<<"\t\tE* "<<(char)(alphabet + i)<<" E*"<<endl;
		nfa_without_null[i] = new int*[n_states];
		number_of_trans_nfa[i] = new int[n_states];
		for(int x = 0;x<n_states;x++)
		number_of_trans_nfa[i][x] = 0;
		cout<<"\t\t";
		for(j = 0;j<n_states;j++)
		{	
		
		    // generation 1st coulum E*(e star)
		    int count = 0;
			// this if condition is used to check whether null transtion occurs at particular transition
			if(n[j].check_null)
			{
				count = n[j].input_tansitions[0]; // this count is used to count the number of null transitions of particular state 
				temp[j] = new int[++count];  // by reading null you can also go to self state so thats why i have increamented the count   
				temp[j][0] = j;	
				cout<<temp[j][0];
				// this is used to find all states by reading null frm particular state
				for(k = 1;k<count;k++)
				{
					temp[j][k] = n[j].fa[0][k-1];
					cout<<temp[j][k];
				}		
			}
			else
			{
				// if there is no any null tranition then simply assign self state
				count = 1;
				temp[j] = new int[1];
				temp[j][0] = j;
				cout<<temp[j][0];
			}
			
			cout<<"  ";
		// now genrate 2nd column on inputs respectively like we have two inputs{a,b} so we have to check on a first and so on
			int index,input_symbol_count = 0; // input_symbol_count is used to store the number of count of
			                                                  // how many numbers are there by readun input symbol for eg{a} 
			if(n[j].check_null)  // now i  have to check on 1st symbol like {a} 
			                    // if there is null transition on this state then check_null should be true 
			                   // if true then number of transitions of input symbol {a} on index 1 so 
			{                   // that's i am increamenting the value of i and store it to the index
				index = i+1;
			}
			else
			index = i;
			
			int previous = 0;
        	temp2[j] = new int[count];		  
			for(k = 0 ;k<count;k++)
			{
			   if(n[temp[j][k]].check_null)  // now i  have to check on 1st symbol like {a} 
			                                // if there is null transition on this state then check_null should be true 
			                                // if true then number of transitions of input symbol {a} on index 1 so 
			    {                            // that's i am increamenting the value of i and store it to the index
				index = i+1;
		    	}
				else
				index = i;
			   
			   // now checking on the particular input symbol 
			   int count2 = n[temp[j][k]].input_tansitions[index];
			   // count2 is used to count the number of tranistions of particular state on particular input symbol
			   for(l = previous;l<count2+previous;l++) 
			   {
			   	 temp2[j][l] = n[temp[j][k]].fa[index][l-previous];
			   	 cout<<temp2[j][l];
			   	 input_symbol_count++;
			   }
			   previous = l;
			}
			
			
			cout<<"  ";			
			// now final E*(e star)
			int count3 = 0;
			for(k = 0;k<input_symbol_count;k++)
			{
				if(n[temp2[j][k]].check_null)
				{
				    count3 = count3 + n[temp2[j][k]].input_tansitions[0]; // this count is used to count the number of null transitions of particular state 
	            }
				count3++; // by reading null you can also go to self state so thats why i have increamented the count           
	        }
	        temp3[j] = new int[count3]; 
	        number_of_trans_nfa[i][j] = count3;
			nfa_without_null[i][j] = new int[count3];
			for(int x = 0;x<count3;x++)
			nfa_without_null[i][j][x] = -1;
			
	        for(k = 0;k<input_symbol_count;k++)				    
				{
					if(n[temp2[j][k]].check_null)
					{
							temp3[j][k] = temp2[j][k]; 
							// print data to console
							cout<<temp3[j][k];	
							// storing the data of final E* in to nfa_without_null array
							nfa_without_null[i][j][k] = temp3[j][k];
						// this is used to find all states by reading null frm particular state	
						for(l = 1+k;l<count3;l++)
						{
							temp3[j][l] = n[temp2[j][k]].fa[0][l-1-k];
							// print data to console
							cout<<temp3[j][l];
							// storing the data of final E* in to nfa_without_null array
							nfa_without_null[i][j][l] =  temp3[j][l];
						}
						k = l;
					}
					else
					{
						temp3[j][k] = temp2[j][k];
						// print data to console
						cout<<temp3[j][k];
						// storing the data of final E* in to nfa_without_null array
						nfa_without_null[i][j][k] = temp3[j][k];
			        } 
				}
				cout<<endl;
				cout<<"\t\t";

			}			
			cout<<endl<<endl; 	
	    }
		// delete dynamically allocated arrays
		for(j = 0;j<n_states;j++)
		{
			delete [] temp[j];
			delete [] temp2[j];
			delete [] temp3[j];
		}
		delete []temp;
		temp = 0;
		delete []temp2;
		temp2 = 0;
		delete []temp3;
		temp3 = 0;   
 	} 
	
void Convert_Nfa_to_Dfa(int n_states,int n_symbles)
{
	
	Queue Q[n_symbles];
	int *temp,size  = 0,*temp2,temp2_size = 0;
	//nfa_without_null	[sy0][st0][0];
	//int **number_of_trans_nfa[0][0]	|[1][0];
	string *already_visited_states;
	int *sizeof_already_visited_states;
	bool has_visited = false;
	int length = pow(2,n_states);
	already_visited_states = new string[length];	//2^n
	sizeof_already_visited_states= new int[length];	
	already_visited_states[0] = "0";  
	sizeof_already_visited_states[0] = 1;
	int str_index = 1;
	
	//initially pushed first state of nfa
	for(int i = 0;i<n_symbles;i++)
	{
		 size = number_of_trans_nfa[i][0];	
		temp = NULL;
		if(size > 0)
		{
		temp = new int[size];
		for(int j = 0 ;j<size ; j++)
		{
			temp[j] = nfa_without_null[i][0][j];
		}
			for(int k = 0 ;k < str_index; k++)
				{
					if(	compare(convert_num_into_string(temp,size) , already_visited_states[k] ) )
					{
						has_visited = true;
					}
				}
		
		if(has_visited == false){
		Q[i].push(temp,size);
		if(temp!=NULL)
			already_visited_states[str_index] =  convert_num_into_string(temp,size);
			sizeof_already_visited_states[str_index] = size;
			str_index++;
		
		}
		else
			has_visited = false;
		
		
	    }
	}
	bool break_loop = true;
	
	while(1){
		break_loop = true;

		for(int i = 0;i<n_symbles;i++)
		{
			if(!Q[i].isempty())
			{
				break_loop = false;
			}
		}
		cout<<endl;
		if(break_loop)	//if every Queue is empty
		{
			break;
		}
		 size  = 0;
		has_visited = false;
		
		for(int i = 0;i<n_symbles;i++)
		{
			temp = Q[i].pop(&size);
			temp2 = new int[size];
			temp2_size = size;
			if(size > 0){
				for(int j = 0;j<temp2_size;j++)
				{
					temp2[j] = temp[j];
				}
			}
			else
			{
				temp2 = NULL;
			}
			
			
			for(int j = 0;j<n_symbles;j++)
			{
				temp = Find_Union_of_states(temp,size,j); 
									
				if(temp!=NULL )
				{
				for(int k = 0 ;k < str_index; k++)
				{
					if(compare(convert_num_into_string(temp,size) , already_visited_states[k] ) )
					{
						has_visited = true;
					}
				}
				if(has_visited == false)
				{
						Q[j].push(temp,size);
						already_visited_states[str_index] =  convert_num_into_string(temp,size);
						sizeof_already_visited_states[str_index] = size;						
						str_index++;
				}	
				else
					has_visited = false;
					
			}	
					if(temp2_size > 0 ){
					temp = new int[temp2_size];		
					for(int k = 0;k<temp2_size;k++)
					{
					temp[k] = temp2[k];
					}
						
						
						}
					else
						temp = NULL;
					
				size = temp2_size;	
				
			}
			delete []temp2;	
		}
		cout<<endl;
	}
	
	
	//PRINTING
	cout<<"\t\t-------------D F A TRANSITION FUNCTION----------------------"<<endl;
	char alphabet = 'a';
	cout<<"\t\t   ";
	for(int i = 0 ;i < n_symbles ; i++)
	{
		cout<<(char)(alphabet + i)<<"   ";
	}
	cout<<endl;
	temp = 	NULL;
	size = 0;	
	cout<<"\t\t";
	for(int i = 0; i < str_index ; i++){
		cout<<already_visited_states[i];
		size = sizeof_already_visited_states[i];
		temp = new int[size];
		temp2 = new int[size];
		temp2_size = size;		
		string str = already_visited_states[i];
		
		for(int k = 0 ;k < size ; k++)
		{
			string str2;
			str2 = str[k];
			stringstream convert_StoI(str2);
			convert_StoI >> temp[k];
		}
	    break_loop = false;
	    for(int j = 0 ; j < size ; j++)
	    {
	    	 break_loop = false;
	    	for(int k = 0 ; k < numof_final_states ; k++)
	    	{
	    		if(temp[j] == final_states[k])
	    		{
	    			cout<<"+"<<"   ";
	    			break_loop = true;
	    			break;
				}
			}
			if(break_loop)
			{
				break;
			}
		}
		
		if(!break_loop)
		{
			cout<<"   ";
		}
	    
	    
	    
	    
	    
		for(int j = 0;j<temp2_size;j++)
		{
			temp2[j] = temp[j];
		}
		
		for(int j = 0 ;j < n_symbles ; j++) 
		{
			
		
			
			temp = Find_Union_of_states(temp,size,j);
			
			//cout<<"x ="<<temp[0];
			if(temp!=NULL)
			{
				for(int k = 0 ;k < size ; k++)
				{
					cout<<temp[k];
				}
			}
			else
			{
				cout<<"-";
				temp = new int[temp2_size];
			}
			
			
			
			for(int k = 0;k<temp2_size;k++)
			{
				temp[k] = temp2[k];
			}
			size = temp2_size;
			cout<<"   ";
		}
		cout<<endl;
		cout<<"\t\t";
	}
	
	
	
}


