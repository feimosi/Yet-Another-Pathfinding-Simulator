#include "stdafx.h"
#include "Simulator.h"
#include "GUIView.h"

using namespace yaps;
using namespace std;

int main(int argc, char* argv[]) {
	Simulator simulator(7, 7);
	simulator.initialise("data.txt");
	simulator.printCurrentData();
	cout << "\n---------------\n" << flush;
	simulator.run();
	simulator.printCurrentData();
	GUIView gui;
	gui.run();
	int x;
	cin >> x;
}