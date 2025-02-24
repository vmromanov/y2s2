#include <vector>

#include "ffff.h"

using namespace std;


int main()
{
	vector<string> players = { "max","dan","nat","mat","vex","tom","nik","det" };
	vector<player> gamers;
	player gamer;
	for(int i=1;i<=players.size();i++)
	{
		gamer.N = i;
		gamer.name = players[i-1];
		gamers.push_back(gamer);
	}
	for (player el : gamers)
		cout << el.name << " ";
	cout << endl;

	sch(gamers,3);
	

}