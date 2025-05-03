#include<iostream>
#include<string>
#include"local.h"
#include"candidate.h"
#include<fstream>
#include"constituency.h"
#include"general.h"
#include"voter.h"
using namespace std;
int local_election::getmnaCount()
{
    return mna_count;
}
Code* local_election::getUniquecode()
{
	int k = 0;
	Code* s = new Code[candidate_no];
	Code* S;
	for (int i = 0;i < candidate_no;i++)
	{
		s[i] = C[i]->getcons();
	}
	for (int i = 0;i < candidate_no;i++)
	{
		for (int j = i + 1; j < candidate_no; j++)
		{
			if (C[i]->getcons() == C[j]->getcons() && s[i].getcode() != "-1" && s[j].getcode() != "-1")
			{
				s[j].setcode("-1");
				k++;
			}
		}
	}
	S = new Code[k + 1];
	for (int i = 0;i < k;i++)
	{
		if (s[i].getcode() != "-1")
		{
			S[i] = s[i];
		}
	}
	S[k].setcode("#");
	return S;
}
void local_election::select_mna()
{
	Code* uniqueCons = getUniquecode();
	int len = 0;
	while (uniqueCons[len].getcode() != "#") {
		len++;
	}
	mna_count = len;
	int* index = new int[len];
	for (int i = 0; i < len; i++) {
		int maxVotes = -1;
		int maxIndex = -1;
		for (int j = 0; j < candidate_no; j++) {
			if (C[j]->getcons().getcode() == uniqueCons[i].getcode()) {
				if (C[j]->getnoOfvotes() > maxVotes) {
					maxVotes = C[j]->getnoOfvotes();
					maxIndex = j;
				}
			}
		}
		index[i] = maxIndex;
	}
	winCode = new Code[len];
	for (int i = 0; i < len; i++) {
		winCode[i] = C[index[i]]->getcons();
	}
	delete[] uniqueCons;
	delete[] index;
    ofstream write;
    write.open("Winner MNA",ios::app);
    if(!write.is_open()){
        cout<<"Error opening file!!\n";
    }
	for(int i=0;i<len;i++){
		write<<winCode[i]<<endl;
	}
}

int local_election::checkMNAexist(string n)
{
    for (int i = 0;i < candidate_no;i++) {
        for (int j = i;j < candidate_no;j++) {
            if (C[i]->getcons().getNcode() == n) {
                return 1;
            }
        }
    }
    return -1;
}

int local_election::MNcheck(int i, string n)
{
    int k = 0;
    for (int j = 0; j < i; j++)
    {
        if (C[j]->getcons().getNcode() == n) {
            k++;
            if (k > 1) {
                return -1;
            }
        }
        return -3;
    }
}
int local_election::MNcheckCons(int i, string c)
{
    int k = 0;
    for (int j = 0; j < i; j++)
    {
        if (C[j]->getcons().getcode() == c) {
           k++;
           if (k > 1) {
              return -2;
           }
           }
        }
        return -3;
}
void local_election::assignCodeToMNA() {
    if (C == nullptr) {
        addCandidate("MNA DATA");
    }
    string line, pos;
    ofstream write("Candidate", ios::app);
    if (!write.is_open()) {
        cout << "Error opening file!!\n";
    }
    ifstream read("Candidate");

    for (int i = 0; i < candidate_no; i++) {
         if (C[i]->getcons().getcode() == "") {
                string c, n;
                cout << "For MNA having CNIC: " << C[i]->getcnic() << endl;

                cout << "Enter constituency code: ";
                cin >> c;

                cout << "Enter national code: ";
                cin >> n;

                while (MNcheckCons(i,c) == -2) {
                    cout << "Constituency Code of MNA must be unique!!\nEnter Constituency Code again: ";
                    cin >> n;
                }

                while (MNcheck(i, n) == -1) {
                    cout << "National Code of MNA must be unique!!\nEnter National Code again: ";
                    cin >> n;
                }
                
                C[i]->setcode(c);
                C[i]->setNcode(n);
            }
            else continue;
        }
}

void election::showCand()
{
    for (int i = 0; i < candidate_no; i++)
    {
        if (C[i]->getcons() == winCode[i])
        {
            cout << C[i];
        }
    }
}