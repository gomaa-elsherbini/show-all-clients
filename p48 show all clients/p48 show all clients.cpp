#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;


struct stClient
{
	string Number;
	string pinCode;
	string name;
	string phone;
	double balance;
};

vector <string> extractRecordInfo(string line)
{//       A150#//#1234#//#Gomaa ElSherbini#//#00925365232#//#5000.000000

	vector <string> vClient;
	string delim = "#//#";
	short pos = 0;
	string clientItem = "";

	while ((pos = line.find(delim)) != -1)
	{
		clientItem = line.substr(0, pos);
		if (clientItem != "")
		{
			vClient.push_back(clientItem);
		}
		line.erase(0, pos + delim.length());
	}
	if (line != "")
	{
		vClient.push_back(line);
	}

	return vClient;
}

stClient readClientRecord(vector <string> vClient)
{
	stClient client;

	client.Number = vClient[0];
	client.pinCode = vClient[1];
	client.name = vClient[2];
	client.phone = vClient[3];
	client.balance = stod(vClient[4]);

	return client;
}

vector <string> getAllClientsData(string fileName)
{
	fstream Clients;
	vector <string> vClients;

	Clients.open(fileName, ios::in);

	string line;
	if (Clients.is_open())
	{
		while (getline(Clients, line))
		{
			vClients.push_back(line);
		}
		Clients.close();
	}
	return vClients;
}

void printClientsData(vector <string> vClients)
{
	stClient client;

	cout << endl;
	cout << "                                         Client List ("<< vClients.size()<<") Client(s)\n" ;
	cout << " ___________________________________________________________________________________________________________________\n" ;
	cout << endl;
	cout << " |" <<" Account Number " << "|" <<" Pin Code "<<"|"<<" Client Name "<<setw(35)<<"|"<<" Phone "<<setw(12)<<"|"<<" Balance "<<setw(10)<<"|"<< endl;
	cout << " ___________________________________________________________________________________________________________________\n" ;
	cout << endl;

	for (string& line : vClients)
	{
		client = readClientRecord(extractRecordInfo(line));

		cout << " | " << setw(15)<<left << client.Number  << "| " << setw(9) <<left<< client.pinCode  << "| " << setw(46)<<left << client.name  << "| " << setw(17)<<left << client.phone  << "| " << setw(17)<<left << client.balance  << "|";
		
		cout << endl;
	}

	cout<<" ___________________________________________________________________________________________________________________\n" ;
}

int main()
{
	printClientsData(getAllClientsData("clientInfo.txt"));



	system("pause>0");
	return 0;

}