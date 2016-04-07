// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

#include "Slav.h"

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);
void sortByGender(Slav *, int);

void containers(Slav *, int);
void adapters(Slav *, int);

int main(int argc, char const *argv[])
{
	srand(time(NULL)); //Losowy seed dla późniejszego losowania słowian

	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);

	delete [] slavs;
}

void containers(Slav * slavs, int n)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;
	
	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");

	// Umieść Słowian w losowej kolejności w wektorze.
	vectorOfSlavs.push_back(NULL);

	for(int i = 0; i < n; i++)
		vectorOfSlavs.insert(vectorOfSlavs.begin() + rand() % vectorOfSlavs.size(), slavs + i);

	vectorOfSlavs.pop_back();

	// Wykorzystując iterator i funkcję description(), wyświetl wszystkich Słowian w wektorze.
	vector <Slav *>::iterator itVectorSlavs = vectorOfSlavs.begin(); //Tworzymy iterator

	for(; itVectorSlavs != vectorOfSlavs.end(); itVectorSlavs++)
		cout << (*itVectorSlavs)->description() << endl;

	REPORT_CONTAINERS;
	printf("## set\n");

	// Przenieś wszystkich Słowian z wektoru do zbioru.
	for(itVectorSlavs = vectorOfSlavs.begin(); itVectorSlavs != vectorOfSlavs.end(); itVectorSlavs++)
		setOfSlavs.insert(*itVectorSlavs);

	vectorOfSlavs.clear();
	
	REPORT_CONTAINERS;
	printf("## map\n");

	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór
	set <Slav *>::iterator itSetSlavs = setOfSlavs.begin();

	while(itSetSlavs != setOfSlavs.end())
	{
		mapOfSlavs[*itSetSlavs] =*(itSetSlavs = setOfSlavs.erase(itSetSlavs));
		itSetSlavs = setOfSlavs.erase(itSetSlavs);
	}
	
	// Wykorzystując iterator, wyświetl wszystkie pary Słowian
	map <Slav*, Slav*>::iterator itMapSlavs = mapOfSlavs.begin();
	for(; itMapSlavs != mapOfSlavs.end(); itMapSlavs++)
		cout << (itMapSlavs->first)->description() << " :::: " << (itMapSlavs->second)->description() << endl;
	
	REPORT_CONTAINERS;
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	// Umieść Słowian w kolejce.
	for(int i = 0; i<n; i++)
		queueOfSlavs.push(slavs + i);
	
	REPORT_ADAPTERS;

	printf("## stack\n");
	// Przenieś Słowian z kolejki do stosu
	for(int i = 0; i<n; i++)
	{
		stackOfSlavs.push(queueOfSlavs.front());
		queueOfSlavs.pop();
	}

	REPORT_ADAPTERS;

	// Wyświetl Słowian zdejmowanych ze stosu.
	for(int i = 0; i<n; i++)
	{
		cout << (*stackOfSlavs.top()).description() << endl;
		stackOfSlavs.pop();
	}

	REPORT_ADAPTERS;
}

void sortByGender(Slav* slavs, int n)
{
	printf("## Sort by gender\n");

	map<_gender, vector<Slav*>> mapOfSlavsSorted;

	for(int i = 0; i<n; i++)
	{
		if((slavs + i)->gender() == male)
			mapOfSlavsSorted[male].push_back(slavs + i);
		else
			mapOfSlavsSorted[female].push_back(slavs + i);
	}

	vector<Slav *>::iterator itVectorSlavsSorted = mapOfSlavsSorted[male].begin();

	int i = 0;
	_gender genderOfSlav;

	while(itVectorSlavsSorted != mapOfSlavsSorted[male].end())
	{
		cout << (*itVectorSlavsSorted)->description() << endl;
		itVectorSlavsSorted++;

		i++;
	}

	if(i == 0)
		cout << "Brak mezczyzn" << endl;

	itVectorSlavsSorted = mapOfSlavsSorted[female].begin();
	i = 0;

	while(itVectorSlavsSorted != mapOfSlavsSorted[female].end())
	{
		cout << (*itVectorSlavsSorted)->description() << endl;
		itVectorSlavsSorted++;

		i++;
	}

	if(i == 0)
		cout << "Brak kobiet" << endl;
}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());

}
