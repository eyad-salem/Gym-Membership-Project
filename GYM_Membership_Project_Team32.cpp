// Gym Membership Tracker Project.cpp : This file contains the 'main' function. Program execution begins and ends there.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <fstream>
using namespace std;

string check_monthly_access();
string check_yearly_access();
struct member {
	int id;
	char name[30];
	double weight;
	double height;
	string subtype;
	string startdate;
	string enddate;
	int asstrainerid;
};

struct trainer {
	int id;
	char name[30];
	char spec[20];
	int memid[20];
	int membcount = 0;
};

struct plan {
	char name[30];
	string cost;
};

const int maxmembers = 80;
const int maxplans = 2;
const int maxtrainers = 4;

member memb[maxmembers];
int membcount = 0;

trainer trainers[maxtrainers];
int tcounter = 0;

plan plans[maxplans];

string Current_date() {
	time_t start = time(nullptr);
	struct tm* local_time = localtime(&start);

	char date0[80];
	mktime(local_time);
	strftime(date0, 80, "%d-%m-%Y", local_time);

	return 	string(date0);


}

string addyear() {
	time_t start = time(nullptr);
	struct tm* local_time = localtime(&start);
	int year = local_time->tm_year += 1;

	char date[80];
	mktime(local_time);
	strftime(date, 80, "%d-%m-%Y", local_time);

	return string(date);
}
string addmonth() {
	time_t start = time(nullptr);
	struct tm* local_time = localtime(&start);
	int mon = local_time->tm_mon += 1;

	char date2[80];
	mktime(local_time);
	strftime(date2, 80, "%d-%m-%Y", local_time);
	return string(date2);
}



void checkstatus() {
	int id;
	int membindex = -1;
	cout << "Enter member ID" << endl;
	cin >> id;
	for (int i = 0; i < maxmembers; i++) {
		if (id == memb[i].id) {
			membindex = i;
			break;
		}
	}
	if (membindex == -1) {
		cout << "Member Not Found" << endl;
		return;
	}
	if (memb[membindex].subtype == "Monthly") {
		check_monthly_access();

	}
	else if (memb[membindex].subtype == "Yearly") {
		check_yearly_access();
	}
}

string Check_Expiry_Date()
{
	time_t now = time(nullptr);
	struct tm* exp_time = localtime(&now);
	struct tm* exp_time1 = localtime(&now);

	time_t expiry = mktime(exp_time);
	time_t expiry1 = mktime(exp_time1);

	string curDate = Current_date();
	string Addmonth = addmonth();
	string Addyear = addyear();

	exp_time->tm_mon += 1;
	exp_time1->tm_year += 1;

	int id;
	int membindex = -1;
	cout << "Enter member ID" << endl;
	cin >> id;
	for (int i = 0; i < maxmembers; i++) {
		if (id == memb[i].id) {
			membindex = i;
			break;
		}
	}
	if (membindex == -1) {
		cout << "Member Not Found" << endl;
	}
	if (memb[membindex].subtype == "Monthly") {
		addmonth();
		cout << "Current date: " << Current_date() << endl;
		cout << "Expiry date:  " << addmonth() << endl;

	}
	else if (memb[membindex].subtype == "Yearly") {
		addyear();
		cout << "Current date: " << Current_date() << endl;
		cout << "Expiry date:  " << addyear() << endl;

	}


	return "";
}


string check_monthly_access()
{
	time_t now = time(nullptr);
	struct tm* exp_time = localtime(&now);
	time_t expiry = mktime(exp_time);

	string curDate = Current_date();
	string Addmonth = addmonth();

	exp_time->tm_mon += 1;

	cout << "Current date: " << Current_date() << endl;
	cout << "Expiry date:  " << addmonth() << endl;
	if (now <= expiry)
		cout << "you're okay" << endl;
	else
		cout << "Renew your sub" << endl;

	return "";
}
string check_yearly_access()
{
	time_t now1 = time(nullptr);
	struct tm* exp_time1 = localtime(&now1);
	time_t expiry1 = mktime(exp_time1);

	string curDate = Current_date();
	string Addyear = addyear();

	exp_time1->tm_year += 1;

	cout << "Current date: " << Current_date() << endl;
	cout << "Expiry date:  " << addyear() << endl;
	if (now1 <= expiry1)
		cout << "you're okay" << endl;
	else
		cout << "Renew your sub" << endl;

	return "";
}



void mkplan() {
	plans[0] = { "Monthly","30.00$" };
	plans[1] = { "Yearly","300.00$" };
	trainers[0] = { 200,"Mohamed eraby","(strength)",{},0 };
	trainers[1] = { 201,"Hossam Mansour","(Cardio)",{},0 };
	trainers[2] = { 202,"Karim Maged","(health)",{},0 };
	trainers[3] = { 203,"Bergo","(body building)",{},0 };
}

void saveMembersToFile()
{
    ofstream file("Gym_Members.txt");

    if (!file) {
        return;
    }

    file << membcount << endl;

    for (int i = 0; i < membcount; i++) {
        file << memb[i].id << endl;
        file << memb[i].name << endl;
        file << memb[i].weight << endl;
        file << memb[i].height << endl;
        file << memb[i].subtype << endl;
        file << memb[i].startdate << endl;
        file << memb[i].enddate << endl;
        file << memb[i].asstrainerid << endl;
    }

    file.close();
}

void loadMembersFromFile()
{
    ifstream file("Gym_Members.txt");

    if (!file) {
        return;
    }

    file >> membcount;
    file.ignore();

    for (int i = 0; i < membcount; i++) {
        file >> memb[i].id;
        file.ignore();

        file.getline(memb[i].name, 30);
        file >> memb[i].weight;
        file >> memb[i].height;
        file.ignore();

        getline(file, memb[i].subtype);
        getline(file, memb[i].startdate);
        getline(file, memb[i].enddate);

        file >> memb[i].asstrainerid;
        file.ignore();
    }

    file.close();
}

void addmember() {
	if (membcount >= maxmembers) {
		cout << "The gym is full! Can't add any more members sorry.";
	}
	member newmember;
	newmember.asstrainerid = 0;
	cout << "Member ID =" << "  ";
	cout << (newmember.id = 560 + membcount) << endl;
	cout << "Enter your name" << endl;
	cin.getline((newmember.name), 30);
	cout << "Enter your height(cm)" << endl;
	cin >> (newmember.height);
	cout << "Enter your weight(kg)" << endl;
	cin >> (newmember.weight);
	newmember.startdate = Current_date();
	cin.ignore(1000, '\n');
	cout << "The start Date will be " << newmember.startdate << endl;
	char n;
	for (int i = 0; i < 2; i++) {
		cout << plans[i].name << " " << plans[i].cost << " " << endl;
	}
	cout << "Enter a choice M = MONTHLY , Y = Yearly" << endl;
	cin >> n;
	if (n == 'm' || n == 'M') {
		newmember.enddate = addmonth();
		newmember.subtype = "Monthly";
		cout << newmember.enddate << endl;
	}
	else if (n == 'Y' || n == 'y') {
		newmember.enddate = addyear();
		newmember.subtype = "Yearly";
		cout << newmember.enddate << endl;
	}
	cin.ignore(1000, '\n');
	memb[membcount] = newmember;
	membcount++;
    saveMembersToFile();
}

void BMI() {
	double heightm;
	double bmi = 0;
	int memid;
	int memindex = -1;
	cout << "Enter Member ID -->";
	cin >> memid;
	for (int i = 0; i < membcount; i++) {
		if (memid == memb[i].id) {
			memindex = i;
			break;
		}
	}
	if (memindex == -1) {
		cout << "Member not found" << endl;
		return;
	}
	heightm = ((memb[memindex].height) / 100.0);
	bmi = (memb[memindex].weight / (pow(heightm, 2)));

	if (bmi <= 18.5) {
		cout << "BMI = " << fixed << setprecision(1) << bmi << endl;
		cout << "Rofaya3" << endl;
	}
	else if (bmi > 18.5 && bmi <= 24.9) {
		cout << "BMI = " << fixed << setprecision(1) << bmi << endl;
		cout << "Gamed" << endl;
	}
	else if (bmi > 25.0 && bmi <= 29.9) {
		cout << "BMI = " << fixed << setprecision(1) << bmi << endl;
		cout << "3ndak kersh" << endl;
	}
	else {
		cout << "BMI = " << fixed << setprecision(1) << bmi << endl;
		cout << "Mkalbaz mot" << endl;
	}
}

void assigntrainer() {
	int memid = 0;
	int trainerid = 0;
	int memindex = -1;
	int trainerindex = -1;
	cout << "Enter Member ID " << endl;
	cin >> memid;
	for (int i = 0; i < membcount; i++) {
		if (memid == memb[i].id) {
			memindex = i;
			break;
		}
	}
	if (memindex == -1) {
		cout << "Member Not found" << endl;
		return;
	}

	for (int i = 0; i < maxtrainers; i++) {
		cout << trainers[i].id << " " << trainers[i].name << " " << trainers[i].spec << endl;
	}
	cout << "Enter the ID of the trainer desired " << endl;
	cin >> trainerid;
	for (int i = 0; i < maxtrainers; i++) {
		if (trainerid == trainers[i].id) {
			trainerindex = i;
			memb[memindex].asstrainerid = trainerid;
			break;
		}
	}
	if (trainerindex == -1) {
		cout << "Trainer was not found" << endl;
		return;
	}

	if ((trainers[trainerindex].membcount) >= 20) {
		cout << trainers[trainerindex].name << " has a full member List " << endl;
	}

	trainers[trainerindex].memid[trainers[trainerindex].membcount] = memb[memindex].id;
	(trainers[trainerindex].membcount)++;



	cout << "This Member ID  " << memb[memindex].id << " " << "Has been assigned to the Trainer " << trainers[trainerindex].name << endl;

}



void trainerprofile() {
	int id;
	int trainerindex = -1;
	cout << "Enter Trainer ID" << endl;
	cin >> id;
	for (int i = 0; i < 4; i++) {
		if (id == trainers[i].id) {
			trainerindex = i;
			break;
		}

	}
	if (trainerindex == -1) {
		cout << "Trainer not found" << endl;
	}
	cout << "This trainer has these members" << endl;

	for (int i = 0; i < trainers[trainerindex].membcount; i++) {
		cout << "Member ID =  " << trainers[trainerindex].memid[i] << endl;
	}
}






void viewprofile() {
	int id;
	int membindex = -1;
	cout << "Enter Member ID" << endl;
	cin >> id;
	for (int i = 0; i < maxmembers; i++) {
		if (id == memb[i].id) {
			membindex = i;
		}
	}
	if (membindex == -1) {
		cout << "Member is not Found" << endl;
	}

	else {
		cout << "-------------------------------------------" << endl;
		cout << "Member Name is " << memb[membindex].name << endl << "Memeber Weight is " << memb[membindex].weight << " (Kg)" << endl << "Member Height is " << memb[membindex].height << " (cm)" << endl;
		cout << "Your Startdate is " << " " << memb[membindex].startdate << endl << "Subscription Type " << " " << memb[membindex].subtype << endl << "Your Expiry Date is " << " " << memb[membindex].enddate << endl;
	}

}
int menu()
{
	
	int choise =0;
	while (choise != 8) {
		cout << "-------------------------------------------" << endl;
		cout << "Welcome to PUMP GYM" << endl;
		cout << "choose the wanted service" << endl << endl;
		cout << "Receptionist Menu" << endl << "-----------------" << endl << endl;
		cout << "1- Register a new member" << endl;
		cout << "2- Assign trainer" << endl;
		cout << "3- Check Membership Satuts" << endl << endl;
		cout << "Member Menu" << endl << "-----------" << endl << endl;
		cout << "4- View Profile" << endl;
		cout << "5- Check Expiry Date" << endl;
		cout << "6- View Assigned Trainer" << endl;
		cout << "7- BMI" << endl;
		cout << "8- Exit" << endl;
		cout << "Your choise: ";
		cin >> choise;
		if (choise == 1) {
			cin.ignore(1000, '\n');

			addmember();
		}
		if (choise == 2) {
			assigntrainer();
		}
		if (choise == 3) {
			checkstatus();
		}

		if (choise == 4) {
			viewprofile();
		}
		if (choise == 5) {
			Check_Expiry_Date();
		}
		if (choise == 6) {
			trainerprofile();
		}
		if (choise == 7) {
			BMI();
		}

		if (choise == 8) {
		cout << endl << "Thank you for choosing PUMP GYM" << endl;
		break;
	}
	}


	return 0;
}












int main() {
	mkplan();
    loadMembersFromFile();
	menu();
	return 0;
}