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

// ===== Hipo headers =====
#include <reader.h>
#include <writer.h>
#include <dictionary.h>
#include <vector>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    char inputFile[256];
    char outputFile[256];

    int run = -9999;
    int file = -9999;

    if (argc > 2) {
        run = atoi(argv[1]);
        file = atoi(argv[2]);
        sprintf(inputFile, "Data/Rec/%06d/rec_clas_%06d.evio.%05d.hipo", run, run, file);
        sprintf(outputFile, "Data/Skim/%d/skim_%d_%d.hipo", run, run, file);
    } else {
        std::cout << " *** please provide the run and the file number..." << std::endl;
        cout << "Exiting ..." << endl;
        exit(0);
    }

    cout << "The filename is " << inputFile << endl;


    hipo::reader reader;
    reader.open(inputFile);

    hipo::dictionary factory;

    reader.readDictionary(factory);

    factory.show();

    hipo::event event;
    int evCounter = 0;

    hipo::bank bCVTRecTr(factory.getSchema("CVTRec::Tracks"));

    hipo::writer writer;
    writer.addDictionary(factory);
    writer.open(outputFile);

    try {

        while (reader.next() == true) {
            reader.read(event);

            evCounter = evCounter + 1;

            //if( evCounter > 5000 ){break;}
            if (evCounter % 10000 == 0) {
                cout.flush() << "Processed " << evCounter << " events \r";
            }
            
            event.getStructure(bCVTRecTr);
            int nCVTTr = bCVTRecTr.getRows();
            
            if( nCVTTr == 1 ){
                writer.addEvent(event);
            }
        }
    }catch (const char msg){
        cerr<<msg<<endl;
    }
    
    writer.close();
    writer.showSummary();

    return 0;
}

