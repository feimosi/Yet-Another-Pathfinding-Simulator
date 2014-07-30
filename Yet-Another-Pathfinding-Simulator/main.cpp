#include "stdafx.h"
#include "Simulator.h"
#include "GUIView.h"

using namespace yaps;
using namespace std;

int main(int argc, char* argv[]) {
    GUIView *gui;
    if (argc == 4)
        gui = new GUIView(atoi(argv[2]), atoi(argv[3]), argv[1]);
    else
        gui = new GUIView(100, 200, "randomMapApprx.jpg");
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

    #########
    # Graph #
    #########

    ############
    # MapParse #
    ############

    #################
    # PriorityQueue #
    #################

    ############
    # Settings #
    ############

    ############
    # VECTOR2 #
    ############

*/
