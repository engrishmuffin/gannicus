#include "trie.h"
actionTrie::actionTrie()
{
	for(int i = 0; i < 10; i++)
		child[i] = NULL;
	fish = NULL;
	pattern = NULL;
	occupants = 0;
}

actionTrie::actionTrie(action * a, int p)
{
	for(int i = 0; i < 10; i++)
		child[i] = NULL;
	fish = new action*[1];
	fish[0] = a;
	pattern = new int[1];
	pattern[0] = p;
	occupants = 1;
}

actionTrie::actionTrie(action * a)
{
	for(int i = 0; i < 10; i++)
		child[i] = NULL;
	fish = new action*[1];
	fish[0] = a;
	pattern = new int[1];
	pattern[0] = 0;
	occupants = 1;
}

void actionTrie::insert(action * b, int p)
{
	int i;
	action ** temp;
	int * tPat;
	occupants++;
	temp = new action*[occupants];
	tPat = new int[occupants];
	for(i = 0; i < occupants-1; i++){
		temp[i] = fish[i];
		tPat[i] = pattern[i];
	}
	temp[i] = b;
	tPat[i] = p;
	if(fish) delete [] fish;
	if(pattern) delete [] pattern;
	fish = temp;
	pattern = tPat;
}

actionTrie * actionTrie::insert(int a, action * b)
{
	if(a < 10 && a >= 0){
		if(!child[a]) child[a] = new actionTrie(b);
		else child[a]->insert(b, 0);
		return child[a];
	}
	else return NULL;
}

actionTrie * actionTrie::insert(int a)
{
	if(a < 10 && a >= 0) {
		if(!child[a]) child[a] = new actionTrie();
		return child[a];
	}
	else return NULL;
}

actionTrie::~actionTrie()
{
	for(int i = 0; i < 9; i++){
		if(child[i] != NULL){
			delete child[i];
			child[i] = NULL;
		}
	}
	if(fish != NULL) delete [] fish;
	fish = NULL;
}

action * actionTrie::actionHook(int inputBuffer[30], int i, int f, int * r, int pos[5], bool neg[5], action * c, SDL_Rect &p, int &cFlag, int &hFlag)
{
	actionTrie * test = NULL;
	action * result = NULL;
	int j;
	for(j = i; j < 30; j++){
		test = child[inputBuffer[j]];
		if(test != NULL){
			if (f < 0) result = test->actionHook(inputBuffer, j, j, r, pos, neg, c, p, cFlag, hFlag);
			else result = test->actionHook(inputBuffer, j, f, r, pos, neg, c, p, cFlag, hFlag);
			if(result != NULL) return result;
		}
	}
	if(occupants != 0){
		for(int k = 0; k < occupants; k++){
			if(fish[k] != NULL){
				if(fish[k]->activate(pos, neg, pattern[k], i, f, r, p) == 1){
					if(fish[k]->cancel(c, cFlag, hFlag)){
						return fish[k];
					}
				}
			}
		}
	}
	return NULL;
}
