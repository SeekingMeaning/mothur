//
//  opticluster.h
//  Mothur
//
//  Created by Sarah Westcott on 4/20/16.
//  Copyright (c) 2016 Schloss Lab. All rights reserved.
//

#ifndef __Mothur__opticluster__
#define __Mothur__opticluster__

#include "cluster.hpp"
#include "optimatrix.h"
#include "calculator.h"
#include "mcc.hpp"
#include "sensitivity.hpp"
#include "specificity.hpp"
#include "fdr.hpp"
#include "npv.hpp"
#include "ppv.hpp"
#include "f1score.hpp"
#include "tp.hpp"
#include "fp.hpp"
#include "fpfn.hpp"
#include "tptn.hpp"
#include "tn.hpp"
#include "fn.hpp"
#include "accuracy.hpp"

/***********************************************************************/

class OptiCluster : public Cluster {

public:
    
#ifdef UNIT_TEST
    friend class TestOptiCluster;
    OptiCluster() : Cluster() { m = MothurOut::getInstance(); truePositives = 0; trueNegatives = 0; falseNegatives = 0; falsePositives = 0;  } //for testing class
    void setVariables(OptiData* mt, ClusterMetric* met) { matrix = mt; metric = met; }
#endif
    
    OptiCluster(OptiData* mt, ClusterMetric* met, long long ns) : Cluster() {
        m = MothurOut::getInstance(); matrix = mt; metric = met; truePositives = 0; trueNegatives = 0; falseNegatives = 0; falsePositives = 0; numSingletons = ns;
    }
    ~OptiCluster() {}
    bool updateDistance(PDistCell& colCell, PDistCell& rowCell) { return false; } //inheritance compliant
    string getTag() { string tag = "opti_" + metric->getName(); return tag; }
    long long getNumBins();
    int initialize(double&, bool, string);  //randomize and place in "best" OTUs
    
    bool update(double&); //returns whether list changed and MCC
    vector<double> getStats( double&,  double&,  double&,  double&);
    ListVector* getList();
    
protected:
    MothurOut* m;
    Utils util;
    map<long long, long long> seqBin; //sequence# -> bin#
    OptiData* matrix;
    vector<int> randomizeSeqs;
    vector< vector<long long> > bins; //bin[0] -> seqs in bin[0]
    map<long long, string> binLabels; //for fitting - maps binNumber to existing reference label
    
    ClusterMetric* metric;
    long long numSeqs, insertLocation, numSingletons;
    double truePositives, trueNegatives, falsePositives, falseNegatives;
    
    long long findInsert();
    vector<double> getCloseFarCounts(long long seq, long long newBin);
    vector<double> getFitStats( long long&,  long long&,  long long&,  long long&);
    
};

#endif /* defined(__Mothur__opticluster__) */
