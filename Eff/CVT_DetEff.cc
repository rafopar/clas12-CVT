/* 
 * File:   CVT_DetEff.cc
 * Author: rafopar
 *
 * Created on February 1, 2023, 7:29 PM
 */

#include <cstdlib>
#include <iostream>

#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TMath.h>

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

    std::cout << " reading file example program (HIPO) " << __cplusplus << std::endl;

    char inputFile[256];
    int run = -9999;

    if (argc > 1) {
        run = atoi(argv[1]);
        sprintf(inputFile, "Data/rec_clas_00%d.hipo", run);
    } else {
        std::cout << " *** please provide the run number..." << std::endl;
        cout << "Exiting ..." << endl;
        exit(0);
    }


    const int detBMT = 1;
    const int detCVT = 5;
    const int detCTOF = 4;
    const double zCTOF_max = 25.;
    const double zCTOF_min = -22.;
    const int nBMTLayers = 6;
    const int nBMTSec = 3;

    TFile *file_out = new TFile(Form("CVT_Eff_%d.root", run), "Recreate");

    TH1D h_nCVTTr("h_nCVTTr", "", 11, -0.5, 10.5);

    hipo::reader reader;
    reader.open(inputFile);

    hipo::dictionary factory;

    reader.readDictionary(factory);

    factory.show();

    hipo::event event;
    int evCounter = 0;

    hipo::bank bCVTRecTr(factory.getSchema("CVTRec::Tracks"));
    hipo::bank bCVTRecTraj(factory.getSchema("CVTRec::Trajectory"));
    hipo::bank bBMTADC(factory.getSchema("BMT::adc"));
    hipo::bank bBMTRecCrosses(factory.getSchema("BMTRec::Crosses"));
    hipo::bank bBMTRecClusters(factory.getSchema("BMTRec::Clusters"));
    hipo::bank bBSTRecCrosses(factory.getSchema("BSTRec::Crosses"));
    hipo::bank bBSTRecClusters(factory.getSchema("BSTRec::Clusters"));


    try {

        while (reader.next() == true) {
            reader.read(event);

            evCounter = evCounter + 1;

            if (evCounter % 10000 == 0) {
                cout.flush() << "Processed " << evCounter << " events \r";
            }

            event.getStructure(bCVTRecTr);
            event.getStructure(bBMTRecCrosses);
            event.getStructure(bBMTRecClusters);
            event.getStructure(bBSTRecCrosses);
            event.getStructure(bBSTRecClusters);
            event.getStructure(bCVTRecTraj);
            event.getStructure(bBMTADC);

            int nCVTTr = bCVTRecTr.getRows();
            h_nCVTTr.Fill(nCVTTr);


        }
    } catch (const char *msg) {
        cerr << msg << endl;
    }

    gDirectory->Write();

    return 0;
}

