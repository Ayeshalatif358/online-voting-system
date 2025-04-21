#include<iostream>
#include<string>
#include"local.h"
#include"candidate.h"
#include"constituency.h"
#include"general.h"
#include"voter.h"
using namespace std;
void local_election::setcandidate() {
	int size;
	size = candidate_no + 1;
	C = new candidate * [size];
	candidate** cand = new candidate * [size];
	for (int i = 0;i < size;i++)
	{
		cand[i] = C[i];
	}
	cand[size - 1] = new candidate();
	cin >> *cand[size - 1];

	delete[]cand;
	C = cand;
	candidate_no = size;
}
void local_election::setn_Code()
{
	string n;
	cout << "Enter national code: ";
	cin >> n;
	code->setcode(n);
}
Code* local_election::getUniquecode()
{
	int k = 0;
	Code* s = new Code[candidate_no];
	Code* S;
	for (int i = 0;i < candidate_no;i++)
	{
		s[i] = *C[i]->getcons();
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
			if (C[j]->getcons()->getcode() == uniqueCons[i].getcode()) {
				if (C[j]->getnoOfvotes() > maxVotes) {
					maxVotes = C[j]->getnoOfvotes();
					maxIndex = j;
				}
			}
		}
		index[i] = maxIndex;
	}
	code = new Code[len];
	for (int i = 0; i < len; i++) {
		code[i] = *C[index[i]]->getcons();
	}
	delete[] uniqueCons;
	delete[] index;
}
void local_election::assign_mna()
{
	for (int i = 0;i < mna_count;i++)
	{
		for (int j = 0;j < 3;j++)
		{

		}
	}
}