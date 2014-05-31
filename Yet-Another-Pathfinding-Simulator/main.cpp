#include "stdafx.h"
#include "Simulator.h"
#include "GUIView.h"

using namespace yaps;
using namespace std;

int main(int argc, char* argv[]) {
    GUIView *gui;
    if (argc == 4)
        gui = new GUIView(int(argv[2] - '0'), int(argv[3] - '0'), argv[1]);
    else
        //gui = new GUIView(23, 46, "newdata.txt");
        //gui = new GUIView(100, 200, "psmap.jpg");
        //gui = new GUIView(200, 400, "psmap.jpg");
        //gui = new GUIView(74, 200, "gauget.jpg");
        gui = new GUIView(150, 400, "gauget.jpg");
    gui->run();
}

/*
Class hierarchy

   ###########
   # GUIView #
   ###########
       ||
       ||
       \/
   #############
   # Simulator #
   #############
       ||
       ||       ##################
        ------> # InputCollector #
       ||       ##################
       ||
       ||       #######################
        ------> # ApproximationEngine #
       ||       #######################
       ||
       ||       ##################
        ------> # RouteScheduler #
       ||       ##################
       ||
       ||       ######################
        ------> # FuzzyControlSystem #
                ######################
                        ||
                        ||                 #############
                         ----------------> # Fuzzifier #
                        ||                 #############
                        ||
                        ||                 ###################
                         ----------------> # InferenceEngine #
                        ||                 ###################
                        ||
                        ||                 ############
                         ----------------> # RuleBase #
                        ||                 ############
                        ||
                        ||                 ###############
                         ----------------> # Defuzzifier #
                                           ###############

    Helper classes:

    ###############
    # Coordinates #
    ###############

    #################
    # DataMatrix<T> #
    #################

*/
