#include "stdafx.h"
#include "Simulator.h"
#include "GUIView.h"

using namespace yaps;
using namespace std;

int main(int argc, char* argv[]) {
//    GUIView gui(800, 410, "NodeReadings2.png");   // scale 2
//    GUIView gui(240, 410, "NodeReadings1.png");   // scale 2
//    GUIView gui(400, 205, "NodeReadings2.png");   // scale 4
    GUIView gui(120, 205, "NodeReadings1.png");   // scale 4
    gui.run();
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
