#include<iostream>
#include<fstream>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<ctype.h>
using namespace std;

struct rotor
{
	char input;
	char output;
	int  pos;
	char alphabet[26];
public:
	rotor()
	{
		pos=1;
		char ch='A';
		for(int i=0; i<26; i++)
		{
			alphabet[i]=ch;
			ch++;
		}
	}
	void decrement()
	{
		char temp=alphabet[0];
		alphabet[0]=alphabet[25];
		for(int i=24;i>0;i--)
		{
			alphabet[i+1]=alphabet[i];
		}
		alphabet[1]=temp;
		if(pos>1)
			pos--;
		else if(pos==1)
			pos=26;
	}
	void increment()
	{
		char temp=alphabet[25];
		alphabet[25]=alphabet[0];
		for(int i=1;i<25;i++)
		{
			alphabet[i-1]=alphabet[i];
		}
		alphabet[24]=temp;
		if (pos<26)
			pos++;
		else if(pos==26)
			pos=1;
	}
	void setting(int initial_letter_pos)//To set the value of rotor position by incrementing or decrementing the rotor values
	{
		int i =0;
		if (initial_letter_pos<=13)
			while (i<initial_letter_pos-1)
				{
					increment();
					i++;
				}

		else
			while(i<(26-initial_letter_pos+1))
			{
				decrement();
				i++;
			}
	}
}r1,r2,r3;

void set_plugboard(char pairs[10][3])
{
	int flag=0;

	while(flag==0)
	{
		flag=1;
		int pno;
		char check[20],letter;
		cout<<"\nEnter the number of plug board pairs you will link: ";
		cin>>pno;
		cout<<"\nEnter Pairs of letters for Plugboard: ";
		for (int i = 0; i < pno; i++)
			{
				cin>>pairs[i];
				if(i==0)
					strcpy(check,pairs[i]);
				else
					strcat(check,pairs[i]);
			}
		for (int i = 0; i < 20; i++)
		{
			letter=check[i];
			int pos = i;
			for (int j = 0; j < 2*pno ; j++)
			{
				if(pos==j)
				{
					continue;
				}
				else
					if(letter==check[j])
					{
						flag=0;
						cout<<"\nAmbigous Input!";
						break;
					}
			}
			if(flag==0)
			break;
		}
	}

	cout<<"\nPlugboard has been set!";

}

char plug_board(char message,char plugboard[10][3])//accepts the letter of message one by one
{

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if(message==plugboard[i][j])
				{
				    message = plugboard[i][1-j];
                    break;
				}
		}
	}
	return message;
}
void set_reflector(char reflector_setting[2][27])
{
	char choice;
	char reflector_list[4][27]={{"EJMZALYXVBWFCRQUONTSPIKHGD"},{"YRUHQSLDPXNGOKMIEBFZCWVJAT"},{"FVPJIAOYEDRZXWGCTKUQSBNMHL"},{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"}};
	do
	{
		cout<<"\nThese are the following hardwired reflectors available for the machine: \n";
		char ch='A';
		for (int i = 0; i < 3; i++)
		{
			cout<<ch<<": "<<reflector_list[i]<<"\n";
			ch++;
		}
		cout<<"Choose a reflector[A,B,C]: ";
		cin>>choice;
		switch(choice)
		{
			case 'A':  strcpy(reflector_setting[0],reflector_list[0]);
				   strcpy(reflector_setting[1],reflector_list[3]);
				   break;
			case 'B':  strcpy(reflector_setting[0],reflector_list[1]);
				   strcpy(reflector_setting[1],reflector_list[3]);
				   break;
			case 'C':  strcpy(reflector_setting[0],reflector_list[2]);
				   strcpy(reflector_setting[1],reflector_list[3]);
				   break;
			default: cout<<"Invalid Reflector choice!";
				   break;
		}
	}while(choice!='A' && choice!='B'&& choice!='C');

}

char reflector(char letter, char reflector_setting[2][27])
{
	for (int i = 0; i < 26; ++i)
	{
		if(letter==reflector_setting[1][i])
		{
			letter=reflector_setting[0][i];
			break;
		}
	}
	return letter;
}

char reverse_wiring(char letter, char encrypting_list[3][27])
{
	r3.input=letter;
	for(int j=0;j<26;j++)
	{
		if(r3.input==encrypting_list[2][j])//linear search for letter position in encrypting list since signal is reversed
		{
			r3.output=r3.alphabet[j];//consequent array index determines its encrypted letter
			r2.input=r3.output;
			break;
		}
	}
	for(int j=0;j<26;j++)
	{
		if(r2.input==encrypting_list[1][j])
		{
			r2.output=r2.alphabet[j];
			r1.input=r2.output;
			break;
		}
	}
	for(int j=0;j<26;j++)
	{
		if(r1.input==encrypting_list[0][j])
		{
			r1.output=r1.alphabet[j];
			letter= r1.output;
			break;
		}
	}

	return letter;
}

void rotor_process(char encrypted_message[],char encrypting_list[3][27], char message[1000],char plugboard_pairs[10][3],char reflector_setting[2][27],int n)
{
	for(int i=0;i<n;i++)
	{
		message[i]=plug_board(message[i], plugboard_pairs);
		r1.input=message[i];
		for(int j=0;j<26;j++)
		{
			if(r1.input==r1.alphabet[j])//linear search for letter position in enigma setting/alphabet list
				{
					r1.output=encrypting_list[0][j];//consequent array index determines its encrypted letter
					r2.input=r1.output;
					break;
				}
		}
		for(int k=0;k<26;k++)
		{
			if(r2.input==r2.alphabet[k])
				{
					r2.output=encrypting_list[1][k];
					r3.input=r2.output;
                    break;
				}
		}

		for(int l=0;l<26;l++)
		{
			if(r3.input==r3.alphabet[l])
				{
					r3.output=encrypting_list[2][l];
					encrypted_message[i]=r3.output;
					break;
				}
		}

		encrypted_message[i]=reflector(encrypted_message[i],reflector_setting);
        encrypted_message[i]=reverse_wiring(encrypted_message[i], encrypting_list);
        encrypted_message[i]=plug_board(encrypted_message[i], plugboard_pairs);
		r1.increment();//rotor moves after encryption
		if(i%25==0)
				r2.increment();//r2 increments after 26 letters
		if(i%51==0)
				r2.increment();//r3 increments after 52 letters

	}
}
void input(char message[1000])
{
	int flag;
	do
	{
		cout<<"\n\n\t\tEnter the message[ONLY IN CAPITALS AND ALPHABETS, NO SPACES ALLOWED]: ";
		cin>>message;
		int a=strlen(message);
		for(int i=0;i<a;i++)
		{
			if(isalpha(message[i]))
				if(isupper(message[i]))
					flag=0;
				else
				{
					flag=1;
					break;
				}
			else
			{
				flag=1;
				break;
			}
		}
	}while(flag==1);
}

void database(char message[1000], char encrypted_message[1000])
{
	fstream f1("message.txt", ios::out| ios::app);
	fstream f2("encrypted_message.txt", ios::out| ios::app);
	f1<<message;
	f1<<"\n";
	f2<<encrypted_message;
	f2<<"\n";
	f1.close();
	f2.close();
}

int check(char s[27])
{
    fstream f("rotor_wiring.txt", ios::in);
    char a[50][27];
    int i=0;
    while(true)
    {
        f.getline(a[i],sizeof(a),'\n');
        if(f.eof())
        {
        	return 1;
        }

        else{
                if(!strcmp(a[i],s))
                {
                    cout<<"The setting already exists";
                    return 0;
                }
                else
                {
                    i++;
                }
            }
    }
    f.close();
}

void rotor_wiring(char encrypting_list[3][27])//ROTOR ENCRYPTION KEYS
{
	char userlist[26][30];
	char wiring[30];
	int n;
	char choice[4];
	fstream f("rotor_wiring.txt", ios::in|ios::out|ios::app);	//For rotor wiring to be accessed from file
	f.seekg(0, ios::end);
	if(f.tellg()==0)
	{
		char w[3][30]={{"JPGVOUMFYQBENHZRDKASXLICTW\n"},{"NZJHGRCXMYSWBOUFAIVLPEKQDT\n"},{"FKQHTLXOCBJSPDZRAMEWNIUYGV\n"}};//default keys
		f<<w[0];
		f<<w[1];
		f<<w[2];
	}
	f.close();
	fstream f1("rotor_wiring.txt", ios::out| ios::in|ios::app );
	if(!f1)
        cout<<"FNF";
	cout<<"\nWould you like to add a rotor setting?(yes/no)\n";
	cin>>choice;
	while(strcmpi(choice,"yes")==0)
	{
	    cout<<"How many rotor wirings will you enter?\n";
        cin>>n;
		for (int i = 0; i < n; i++)
		{
			cout<<"Enter your rotor wiring settings: ";
			cin>>userlist[i];
			if(check(userlist[i])==0)
				{
					cout<<"\nWould you like to add a rotor setting?(yes/no)\n";
					cin>>choice;
					break;
				}
			strcat(userlist[i], "\n");
			f1<<userlist[i];
			strcpy(choice,"no");
		}
	}
	int no=1;
	char full_list[100][27];
	cout<<"\nThis is the rotor wiring list: \n";
	f1.seekg(0);
	while(true)
	{
		f1.getline(wiring,27,'\n');
		if(f1.eof())
            break;
		cout<<"wiring"<<" "<<no<<": "<<wiring<<"\n";
		strcpy(full_list[no-1],wiring);
		no++;
	}
	cout<<"\nAmong the following list choose any three wheels: ";
	int choice2[3];
	for (int i = 0; i < 3; i++)
	{
	    if(i==0)
        {
                cout<<"\nChoose the first rotor: ";
                cin>>choice2[i];
                strcpy(encrypting_list[i],full_list[choice2[i]-1]);
        }

		else if(i==1)
         {
                cout<<"\nChoose the second rotor: ";
                cin>>choice2[i];
                strcpy(encrypting_list[i],full_list[choice2[i]-1]);
         }
        else if(i==2)
        {
                cout<<"\nChoose the third rotor: ";
                cin>>choice2[i];
                strcpy(encrypting_list[i],full_list[choice2[i]-1]);
        }


	}
	f1.close();

 }
void rotor_set()
{
	int initial_pos;
	cout<<"\nInitial rotor positions are to be set";
	cout<<"\nEnter the first rotor's position[1-26]: \t";
	cin>>initial_pos;
	r1.setting(initial_pos);
	cout<<"\nEnter the second rotor's position[1-26]: \t";
	cin>>initial_pos;
	r2.setting(initial_pos);
	cout<<"\nEnter the third rotor's position[1-26]: \t";
	cin>>initial_pos;
	r3.setting(initial_pos);
}
void display(char encrypted_message[1000], int n)
{
		encrypted_message[n]='\0';
		cout<<"\n\t\t\tThe encrypted message is: ";
		for(int i=0;i<n;i++)
		{
			cout<<encrypted_message[i];
			if((i+1)%4==0)
				cout<<" ";
		}
}

int main()
{
	char choice[3];
	cout<<"\t\t\t\t\t\tWelcome to the ENIGMA MACHINE!";
    cout<<"\nDeveloped Solution by A-Star Enterprise";
    cout<<"\nCredits: Arjun Somvanshi, Manvendra Somvanshi\n";
    cout<<"\nWe have a default setting for the enigma machine. If you are not well-versed with it's working you can use our default settings.";
    cout<<"\nDo you want to use default settings?[yes/no]: ";
    cin>>choice;

	char message[1000],message1[1000],encrypted_message[1000];

	if(strcmpi(choice,"yes")==0)
	{
		char w[3][27]={{"JPGVOUMFYQBENHZRDKASXLICTW"},{"NZJHGRCXMYSWBOUFAIVLPEKQDT"},{"FKQHTLXOCBJSPDZRAMEWNIUYGV"}};
		char plugboard_pairs[10][3]={{"AB"},{"CD"},{"EF"},{"GH"},{"IJ"},{"KL"},{"MN"},{"OP"},{"QR"},{"ST"}};
		char reflector_setting[2][27]={{"EJMZALYXVBWFCRQUONTSPIKHGD"},{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"}};
		input(message);
    	strcpy(message1,message);
    	rotor_process(encrypted_message,w,message,plugboard_pairs,reflector_setting,strlen(message));
		display(encrypted_message, strlen(message));
		database(message1,encrypted_message);
	}

	else
	{
		char plugboard_pairs[10][3],encrypting_list[3][27], reflector_setting[2][27];
		set_plugboard(plugboard_pairs);
		rotor_wiring(encrypting_list);
		rotor_set();
    	char e_l[3][27];
    	for(int i=0;i<3;i++)
        	strcpy(e_l[i],encrypting_list[i]);
		set_reflector(reflector_setting);
		input(message);
    	strcpy(message1,message);
    	rotor_process(encrypted_message,e_l,message,plugboard_pairs,reflector_setting,strlen(message));
		display(encrypted_message, strlen(message));
		database(message1,encrypted_message);
	}
	cout<<"\nPress any character and enter key to exit: ";
	char l;
	cin>>l;
    return 0;
}
