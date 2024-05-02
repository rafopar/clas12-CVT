/* 
 * File:   Skim_Events.cc
 * Author: rafopar
 *
 * Created on May 2, 2024, 6:14 PM
 */

/*
 * This will skim events that have only 1 CVTRecTrack
 */

#include <cstdlib>
#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    char inputFile[256];

    int run = -9999;
    int file = -9999;

    if (argc > 2) {
        run = atoi(argv[1]);
        file = atoi(argv[2]);
        sprintf(inputFile, "Data/rec_clas_%06d.evio.%05d.hipo", run, file);
    } else {
        std::cout << " *** please provide the run and the file number..." << std::endl;
        cout << "Exiting ..." << endl;
        exit(0);
    }

    cout<<"The filename is "<<inputFile<<endl;
    
    
    return 0;
}

