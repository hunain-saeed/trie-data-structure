#include <bits/stdc++.h>
#include<conio.h>
#define latter 26
using namespace std;
class Node
{
	public:
		Node *next[latter];
		bool isWord;

		Node()
		{
			for (int i = 0; i < latter; i++)
			{
				next[i] = 0;
			}
			isWord = false;
		}
};
class Tree
{
	Node *root;
	unsigned long long size;
	int ind;
	int Sno;
	public:
		Tree() : root(0), size(0)
		{
		}
		Tree(string str) : size(0)
		{
			size++;
			root = new Node();
			Node *temp = root;
			for (int i = 0; i < str.length(); i++)
			{
				int index = str[i] - 'a';
				if (temp->next[index] == 0)
				{
					temp->next[index] = new Node();
				}
				temp = temp->next[index];
			}
			temp->isWord = true;
		}
		void InsertInTree(string str)
		{
			size++;
			if (root == 0)
			{
				root = new Node();
			}
			Node *temp = root;
			for (int i = 0; i < str.length(); i++)
			{
				int index=0;
				if(str[i] >= 'a' && str[i] <= 'z')
				{
					index = str[i] - 'a';
				}
				else if(str[i] >= 'A' && str[i] <= 'Z')
				{
					index = str[i] - 'A';
				}
				if (temp->next[index] == 0)
				{
					temp->next[index] = new Node();
				}
				temp = temp->next[index];
			}
			temp->isWord = true;
		}

		unsigned long long getSize() const
		{
			return size;
		}
		
		bool case5(string str)
		{
			int j=0;
			int count=0;
			for(j=0; j<str.length()-1; j++)
			{
				if(str[j] == '*')
				{
					++count;
				}
				if(count == 1 && str[j] == '*')
				{
					ind = j;
				}
			}
			if(count == 2)
			{
				return true;
			}
			return false;
		}
		void search(string str, int cases)
		{
			if(root != 0)
			{
				int index, i=0, level=0;
				char arr[50] = { 0 };
				bool exist=true;
				Node *temp;
				temp = root;
				Sno = 0;
				while(1)
				{
					if(str[i] == '*')	//could be case 1, 3, 5
					{
						if(case5(str))	//for case 5
						{
							displayWords(temp,arr,str,level, 5);	//bonus case 5: abc*abc*abc
							if(Sno == 0)
							{
								cout<<"\nError: Word(s) not found!\n";
							}
							return;
						}
						break;
					}
					else if(str[i] == '.') // Case 4
					{
						displayWords(temp,arr,str,level, 4);
						if(Sno == 0)
						{
							cout<<"\nError: Word(s) not found!\n";
						}
						return;
					}
					else if(str[i] == '\0')
					{
						system("cls");
						cout<<"Invalid Formate\n";
						return;
					}
					if(str[i] >= 'a' && str[i] <= 'z')// || str[i] >= 'A' && str[i] <= 'Z')
					{
						arr[i] = str[i];
						
						if(str[i] >= 'a' && str[i] <= 'z')
						{
							index = str[i] - 'a';
						}			
						if(!temp->next[index])
						{
							exist = false;
							break;
						}
						temp = temp->next[index];
						level++;
						i++;
					}
					else
					{
						system("cls");
						cout<<"Invalid Formate\n";
						return;
					}
				}	// end while
				if(exist)
				{
					i++;
					if(str[i] == '\0') // case 1: abc*
					{
						displayWords(temp,arr,str,level, cases);
					}
					else if(str[i] >= 'a' && str[i] <= 'z')	// case 3: abc*abc
					{
						displayWords(temp,arr,str,level, 3);
					}
				}
				else
				{
					cout<<"\nError: Word(s) not found!";
				}
		}
		}
		void displayWords(Node *temp, char arr[], string str, int level, int cases)
		{
			if(temp->isWord != false)
			{
				arr[level] = '\0';
				++Sno;
				if(cases == 1)
				{
					cout << Sno << " " << arr;
					cout << "  " << level << endl;
				}
				else if(cases == 2)
				{
					reverseDisplay(arr, level);
				}
				else if(cases == 3)	//abc*abc
				{
					if(cmpCase3(arr, str))	
					{
						cout << Sno << " " << arr;
						cout << "  " << level << endl;
					}
					else
					{
						--Sno;
					}
				}
				else if(cases == 4)	//case 4: abc..f
				{
					if(cmpCase4(arr, str))
					{
						cout << Sno << " " << arr;
						cout << "  " << level << endl;
					}
					else
					{
						--Sno;
					}
				}
				else if(cases == 5)	// case 5: abc*abc*abc
				{
					if(cmpCase5(arr, str))
					{
						cout << Sno << " " << arr;
						cout << "  " << level << endl;
					}
					else
					{
						--Sno;
					}
				}
			}
			for (int i = 0; i < latter; i++)
			{
				if (temp->next[i])
				{
					arr[level] = i + 'a';
					displayWords(temp->next[i], arr, str, level + 1, cases);
				}
			}
		}
		bool cmpCase5(string arr, string str)	//Case 5: if input is abc*abc*abc
		{
			int i,j;
			for(i = str.length()-1, j = arr.length()-1; str[i] != '*'; i--, j--)
			{
				if(str[i] != arr[j])
				{
					return false;
				}
			}
			i--;
			for( ; j >= ind; j--)
			{
				if(str[i] == arr[j])
				{
					int k,l;
					for(k=i, l=j; str[k]!='*' && l >= ind; k--,l--)
					{
						if(str[k] != arr[l])
						{
							break;
						}
					}
					if(str[k] == '*')
					{
						return true;
					}
				}
			}
			return false;
		}
		bool cmpCase4(string arr, string str)	//Case 4: if string contain '.'
		{
			if(str.length() != arr.length())
			{
				return false;
			}
			else
			{
				for(int i = str.length()-1, j = arr.length()-1; str[i] != '.'; i--, j--)
				{
					if(str[i] != arr[j])
					{
						return false;
					}
				}
				return true;
			}
		}
		bool cmpCase3(string arr, string str)	//Case 3: if input is abc*abc
		{
			if(arr.length() < str.length())
			{
				return false;
			}
			for(int i = str.length()-1, j = arr.length()-1; str[i] != '*'; i--, j--)
			{
				if(str[i] != arr[j])
				{
					return false;
				}
			}
			return true;
		}
		void reverseDisplay(char arr[], int size)	//for Case 2 if input is *abc
		{
			cout << Sno << " ";
			for (int i=size-1; i>=0; i--) 
			{
				cout << arr[i];
			}
			cout << "  " << size << endl;
		}

		void print() //to print dictionary in O(n) times
		{
			char str[50] = { 0 };
			Node *temp = root;
			displayWords(temp, str, "", 0, 1);
		}
		
		//distructor is not correct.
//		void deleteTree(Node *root)
//		{
//			if(root != 0)
//			{
//				for(int i=0;i<26;i++)
//				{
//					deleteTree(root->next[i]);
//				}
//			}
//			root->isWord = false;
//			root = 0;
//			delete root;
//		}
//		~Tree()
//		{
//			if(root != 0)
//			{
//				deleteTree(root);
//			}
//			root = 0;
//		}
};

class EWords
{
	Tree t1,t2;	//t1 contain words in rigth order t2 contain word in reverse order
	string str;
	public:
		
		void input()
		{
			ifstream fin;
			fin.open("dictionary.txt");
			
			if(fin.is_open())
			{				
				while(!fin.eof())
				{
					fin>>str;			//reading word by word from file and storing in dynamic2D array
					t1.InsertInTree(str);
					reverse(str.begin(),str.end());
					t2.InsertInTree(str);
				}
				
				fin.close();
			}
			else
			{
				cout<<"\nError: File not found!";
			}
		}
		void searchWord()
		{
			while(1)
			{
				system("cls");
				cout<<"Total number of Words in a dictionary is : "<<t1.getSize()<<endl;
				cout<<"****************************************\n";
				cout<<"|             Instructions             |\n";
				cout<<"|**************************************|\n";
				cout<<"| To exit enter \"-\"                    |"<<endl;
				cout<<"| Only enter small case alphabets      |"<<endl;
				cout<<"|                                      |"<<endl;
				cout<<"| Input formats:                       |"<<endl;
				cout<<"| 1) abc*                              |"<<endl;
				cout<<"| 2) *def                              |"<<endl;
				cout<<"| 3) abc*def                           |"<<endl;
				cout<<"| 4) abc..def                          |"<<endl;
				cout<<"| 5) abc*def*ghi                       |"<<endl;
				cout<<"****************************************\n";
				cout<<"Enter here: ";
				cin>>str;
				if(str[0] == '-')
				{
					break;
				}
				else if(str[0] == '*')	//case 2: *abc
				{
					reverse(str.begin(),str.end());
					t2.search(str, 2);
				}
				else	//Case 1: abc* and Case 3: abc*abc and Case 4: ab..ef and Case 5: abc*abc*abc
				{
					t1.search(str, 1);
				}
				// press enter to search next
				cout<<"\nPress any key to continue...\n";
				getch();
			}
		}
};

int main()
{
	EWords e1;
	e1.input();
	e1.searchWord();

	return 0;
}
