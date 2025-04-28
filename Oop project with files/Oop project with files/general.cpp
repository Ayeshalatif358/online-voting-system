#include<iostream>
#include<string>
#include"general.h"
#include"candidate.h"
#include"voter.h"
using namespace std;
general_election::general_election()
{
	C = nullptr;
	candidate_no = 0;
}
//void general_election::setcandidate() {
//	int size;
//	size = candidate_no + 1;
//	C = new candidate * [size];
//	candidate** cand = new candidate * [size];
//	for (int i = 0;i < size;i++)
//	{
//		cand[i] = C[i];
//	}
//	cand[size - 1] = new candidate();
//	cin >> *cand[size - 1];
//
//	delete[]cand;
//	C = cand;
//	candidate_no = size;
//}
Code* general_election::getUniquecode()
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
void general_election::select_mpa()
{
	Code* uniqueCons = getUniquecode();
	int len = 0;
	while (uniqueCons[len].getcode() != "#") {
		len++;
	}
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
	mCode = new Code[len];
	for (int i = 0; i < len; i++) {
		mCode[i] = C[index[i]]->getcons();
	}
	delete[] uniqueCons;
	delete[] index;
}