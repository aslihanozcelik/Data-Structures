
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

typedef struct NodeFootballerInfo {
	std::string away_team;	//away team
	int minofgoal;			//minute of goal
	int match_id;			//match id
	NodeFootballerInfo* next;// pointer to next node
}footballerInfoNode;

typedef struct NodeFootballer {
	std::string name;		//footballer name
	std::string team;		//footballer team
	NodeFootballer* next;	//pointer to next node
	NodeFootballerInfo* front;	//pointer to footballer info linked list
}footballerNode;


typedef struct LinkedListAllFootballers {
	int size;		//size of linked list
	NodeFootballer* front;	//pointer to first node of linked list
	NodeFootballer* back;	//poiinter to last added node of linked list
}allFootballers;

//This function creates Linked List 
allFootballers* createLinkedList() {
	allFootballers *LL = new allFootballers[sizeof(allFootballers)];
	LL->size = 0;
	LL->front = NULL;
	LL->back = NULL;
	return LL;
}
//This function creates a new node for Footballer Linked List
footballerNode* createNode(string name, string team) {
	footballerNode *temp = (footballerNode*)malloc(sizeof(footballerNode));
	temp->name = name;
	temp->team = team;
	temp->next = NULL;
	return temp;
}
//This function add a given node to Footballer Linked List
void addFootballer(allFootballers* LL, footballerNode* node) {
	if (LL->size == 0) {
		LL->front = node;
		LL->size = 1;
		LL->back = LL->front->next;
	}
	else
	{
		LL->back = node;
		LL->back = LL->back->next;
	}
}


typedef struct Footballer {
	std::string name;		//Footballer name
	std::string team;		//Team 
	std::string away_team;	//Away Team
	int min_of_goal;		//Minute of Goal
	int matchID;			//Match ID

}footballers;

typedef struct FootballersandGoals {
	std::string name;	//Footballer name
	int numofgoals;		//Number of goals 
}goals;

//This function calculates the number of goals for each footballer
goals* setFootballersandGoals(footballers* allF, int size, string* footballers, int f_c) {
	int counter = 0;
	goals * footballerStruct = new goals[f_c];
	for (int i = 0; i < f_c; i++) {
		for (int j = 0; j < size; j++) {
			if (footballers[i] == allF[j].name) {
				counter++;
			}
		}
		footballerStruct[i].name = footballers[i];
		footballerStruct[i].numofgoals = counter;
		counter = 0;

	}
	return footballerStruct;
}

//This function finds the most scored half
int MostScoredHalf(footballers* allF) {
	int counter1 = 0, counter2 = 0;
	int x;
	for (int i = 0; i < sizeof(footballers); i++) {
		if (allF[i].min_of_goal <= 45) {
			counter1++;
		}
		if (allF[i].min_of_goal > 45) {
			counter2++;
		}
	}
	if (counter1 > counter2) {
		x = 0;
	}
	if (counter2 > counter1) {
		x = 1;
	}
	return x;
}

//All output operations 
void printOutput(char * argv, string* allOperations, footballers* allF, int size, string* footballers, int counter1, string* teams, int counter2, goals* footballerStruct) {

	//Open "output.txt" file
	ofstream output;
	output.open(argv);
	//THE MOST SCORED HALF
	output << "1)THE MOST SCORED HALF" << endl;
	int msh = 0;
	msh = MostScoredHalf(allF);
	output << msh << endl;

	//GOAL SCORER
	output << "2)GOAL SCORER" << endl;
	int max = 0;
	int max_indice = 0;
	int* goalScorers = new int[counter1];
	int gs_c = 0;
	for (int i = 0; i < counter1; i++) {
		if (footballerStruct[i].numofgoals > max) {
			max = footballerStruct[i].numofgoals;
			max_indice = i;
		}
	}
	goalScorers[gs_c] = max_indice;

	for (int i = 0; i < counter1; i++) {
		if (footballerStruct[i].numofgoals == max) {
			if (i != goalScorers[0]) {
				goalScorers[++gs_c] = i;
			}
		}
	}
	int a;
	for (int i = 0; i <= gs_c; i++) {
		a = goalScorers[i];
		output << footballerStruct[a].name << endl;
	}
	//THE NAMES OF FOOTBALLERS WHO SCORED HAT-TRICK
	output << "3)THE NAMES OF FOOTBALLERS WHO SCORED HAT-TRICK" << endl;
	string* hat_tricks = new string[size];
	int* indices = new int[size];
	int indices_c = 0;
	int ht_c = 0;
	int x = 0;

	for (int i = 0; i < counter1; i++) {

		for (int j = 0; j < size; j++) {
			if (footballerStruct[i].name == allF[j].name) {
				indices[indices_c] = j;
				indices_c++;
			}
		}
		if (indices_c >= 3) {
			for (int j = 0; j < indices_c; j++) {
				for (int k = 0; k < indices_c; k++) {
					if (allF[indices[j]].matchID == allF[indices[k]].matchID) {
						if (indices[j] != indices[k]) {
							ht_c++;
						}
					}
				}
			}
			if (ht_c >= 3) {
				hat_tricks[x] = footballerStruct[i].name;
				x++;
			}
		}
		ht_c = 0;
		indices_c = 0;
	}

	string* hat_tricks2 = new string[counter1];
	int q = 0;
	hat_tricks2[q] = hat_tricks[0];
	q++;
	int counter3 = 0;
	for (int i = 1; i < x; i++) {
		for (int j = 0; j < q; j++) {
			if (hat_tricks[i] != hat_tricks2[j]) {
				counter3++;
			}
		}
		if (counter3 == q) {
			hat_tricks2[q] = hat_tricks[i];
			q++;
		}
		counter3 = 0;
	}
	for (int i = 0; i < q; i++) {
		output << hat_tricks2[i] << endl;
	}
	//LIST OF TEAMS
	output << "4)LIST OF TEAMS" << endl;
	for (int i = 0; i < counter2; i++) {
		output << teams[i] << endl;
	}
	//LIST OF FOOTBALLERS
	output << "5)LIST OF FOOTBALLERS" << endl;
	for (int i = 0; i < counter1; i++) {
		output << footballers[i] << endl;
	}
	//MATCHES OF GIVEN FOOTBALLERS
	output << "6)MATCHES OF GIVEN FOOTBALLER" << endl;
	string f_baller1 = allOperations[0];
	string f_baller2 = allOperations[1];
	//MATCHES OF FIRST FOOTBALLERS
	output << "Matches of " << f_baller1 << endl;
	for (int i = 0; i < size; i++) {
		if (allF[i].name == f_baller1) {
			output << "Footballer Name: " << f_baller1 << ",Away Team: " << allF[i].away_team << ",Min of Goal: " << allF[i].min_of_goal << ",Match ID: " << allF[i].matchID << endl;
		}
	}
	//MATCHES OF SECOND FOOTBALLERS
	output << "Matches of " << f_baller2 << endl;
	for (int i = 0; i < size; i++) {
		if (allF[i].name == f_baller2) {
			output << "Footballer Name: " << f_baller2 << ",Away Team: " << allF[i].away_team << ",Min of Goal: " << allF[i].min_of_goal << ",Match ID: " << allF[i].matchID << endl;
		}
	}
	//PRINT GIVEN FOOTBALLERS AND MATCH IDs IN ASCENDING ORDER ACCORDING TO MATCH ID
	output << "7)ASCENDING ORDER ACCORDING TO MATCH ID" << endl;
	string f_baller3 = allOperations[2];
	string f_baller4 = allOperations[3];

	std::list<int> sortID;
	std::list<int> sortID2;

	for (int i = 0; i < size; i++) {
		if (allF[i].name == f_baller3) {
			sortID.push_back(allF[i].matchID);
		}
	}
	for (int i = 0; i < size; i++) {
		if (allF[i].name == f_baller4) {
			sortID2.push_back(allF[i].matchID);
		}
	}
	sortID.sort();
	sortID.unique();
	sortID.sort();
	int first_size = sortID.size();

	sortID2.sort();
	sortID2.unique();
	sortID2.sort();
	int mId;
	int second_size = sortID2.size();
	for (int i = 0; i < first_size; i++) {
		mId = sortID.front();
		output << "footballer Name: " << f_baller3 << ",Match ID: " << mId << endl;
		sortID.pop_front();
	}
	for (int i = 0; i < second_size; i++) {
		mId = sortID2.front();
		output << "footballer Name: " << f_baller4 << ",Match ID: " << mId << endl;
		sortID2.pop_front();
	}
	//PRINT GIVEN FOOTBALLERS AND MATCH IDs IN DESCENDING ORDER ACCORDING TO MATCH ID
	output << "8)DESCENDING ORDER ACCORDING TO MATCH ID" << endl;
	string f_baller5 = allOperations[4];
	string f_baller6 = allOperations[5];
	std::list<int> sortID3;
	std::list<int> sortID4;

	for (int i = 0; i < size; i++) {
		if (allF[i].name == f_baller5) {
			sortID3.push_back(allF[i].matchID);
		}
	}
	for (int i = 0; i < size; i++) {
		if (allF[i].name == f_baller6) {
			sortID4.push_back(allF[i].matchID);
		}
	}
	sortID3.sort();
	sortID3.unique();
	sortID3.sort();
	int third_size = sortID3.size();

	sortID4.sort();
	sortID4.unique();
	sortID4.sort();
	int fourth_size = sortID4.size();
	sortID3.reverse();
	sortID4.reverse();

	for (int i = 0; i < third_size; i++) {
		mId = sortID3.front();
		output << "footballer Name: " << f_baller5 << ",Match ID: " << mId << endl;
		sortID3.pop_front();
	}
	for (int i = 0; i < fourth_size; i++) {
		mId = sortID4.front();
		output << "footballer Name: " << f_baller6 << ",Match ID: " << mId << endl;
		sortID4.pop_front();
	}
	output.close();

	// destroy array objects which are created by new expression
	delete[] goalScorers;
	delete[] indices;
	delete[] hat_tricks;
	delete[] hat_tricks2;

}
int main(int argc, char *argv[])
{
	string * strings = new string[BUFSIZ];

	//READ INPUT FILE
	ifstream input1;
	input1.open(argv[1]);
	int input1_size = 0;
	int i = 0;
	int a = 0;
	while (input1) {
		if (input1_size == 4 + (a * 5) && input1_size != 0) {
			getline(input1, strings[i], '\n');
			a++;
		}
		else {
			getline(input1, strings[i], ',');
		}

		input1_size++;
		i++;
	}

	input1.close();

	int counter = 0;
	footballers * allF = new footballers[input1_size / 5];

	//put all information of footballers to Footballer struct
	for (i = 0; i < input1_size / 5; i++) {

		allF[i].name = strings[counter];
		allF[i].team = strings[counter + 1];
		allF[i].away_team = strings[counter + 2];
		allF[i].min_of_goal = stoi(strings[counter + 3]);
		allF[i].matchID = stoi(strings[counter + 4]);
		counter = counter + 5;
	}
	//READ OPERATIONS FILE
	string * strings2 = new string[6];
	ifstream input2;

	input2.open(argv[2]);
	int input2_size = 0;
	i = 0;

	getline(input2, strings2[i++], ',');
	getline(input2, strings2[i++], '\n');
	getline(input2, strings2[i++], ',');
	getline(input2, strings2[i++], '\n');
	getline(input2, strings2[i++], ',');
	getline(input2, strings2[i++], '\n');

	input2.close();
	//Create Footballer List (Remove same footballer names)
	string * footballer_names = new string[input1_size / 5];
	std::list<string> sort_footballers;
	for (int i = 0; i < input1_size / 5; i++) {
		footballer_names[i] = allF[i].name;
	}
	for (int i = 0; i < input1_size / 5; i++) {
		sort_footballers.push_back(footballer_names[i]);
	}
	sort_footballers.sort();
	sort_footballers.unique();
	sort_footballers.sort();
	int f_c = sort_footballers.size();

	for (int i = 0; i < f_c; i++) {
		footballer_names[i] = sort_footballers.front();
		sort_footballers.pop_front();
	}
	//Create Team List (Remove same team names)
	string * teams = new string[input1_size];
	int t_c = 0;
	teams[t_c] = allF[0].team;
	t_c++;
	int match2 = 0;
	for (i = 1; i < input1_size / 5; i++) {

		for (int j = 0; j < t_c; j++) {
			if (allF[i].team == teams[j]) {
				match2++;

			}
		}

		if (match2 == 0) {
			teams[t_c] = allF[i].team;
			t_c++;
		}
		else {
			match2 = 0;
		}
	}

	goals * footballerStruct = new goals[f_c];
	footballerStruct = setFootballersandGoals(allF, input1_size / 5, footballer_names, f_c);

	//printOutput function
	printOutput(argv[3], strings2, allF, input1_size / 5, footballer_names, f_c, teams, t_c, footballerStruct);
	// destroy array objects which are created by new expression
	delete[] allF;
	delete[] strings2;
	delete[] teams;
	delete[] footballer_names;
	delete[] strings;
	delete[] footballerStruct;

}

