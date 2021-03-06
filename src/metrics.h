// Copyright (c) 2016 The Zcash developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "uint256.h"

#include <atomic>
#include <string>

struct AtomicCounter {
    std::atomic<uint64_t> value;

    AtomicCounter() : value {0} { }

    void increment(){
        ++value;
    }

    void decrement(){
        --value;
    }

    int get(){
        return value.load();
    }
};

extern AtomicCounter transactionsValidated;
extern AtomicCounter ehSolverRuns;
extern AtomicCounter solutionTargetChecks;

void TrackMinedBlock(uint256 hash);

void MarkStartTime();
double GetLocalSolPS();

void TriggerRefresh();

void ConnectMetricsScreen();
void ThreadShowMetricsScreen();

/**
 * Rendering options:
 * Logo: img2txt -W 90 -H 20 -f utf8 -d none -g design.png >> design.ansi
 */

const std::string METRICS_ART =
"[0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m                                                                            [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m                                                                            [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%[0;1;30;90;43mt[0;32;40m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;1;33;93;43m%[0;33;5;43;103m%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%[0;1;30;90;43mt[0;34;40m                               [0;1;33;93;43mt[0;33;5;43;103m%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%[0;1;30;90;43mt[0;34;40m                               [0;1;33;93;43mt[0;33;5;43;103m%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%[0;1;30;90;43mt[0;32;40m;;;;;;;;;;;;;;;;;;;;[0;34;40m          [0;32;40m:[0;1;33;93;43mS[0;33;5;43;103m%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%X[0;1;30;90;43m;[0;34;40m         [0;32;40m8[0;1;33;93;43mS[0;33;5;43;103m%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;1;30;90;43m%[0;32;40m%[0;34;40m        [0;32;40m.[0;1;30;90;43mt[0;33;5;43;103m%%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;1;30;90;43mt[0;32;40m.[0;34;40m        [0;32;40mS[0;1;30;90;43m%[0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;1;33;93;43m%[0;32;40m@[0;34;40m        [0;32;40m [0;1;30;90;43mt[0;33;5;43;103mS%%%%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;1;30;90;43m%[0;32;40m;[0;34;40m        [0;32;40mt[0;1;30;90;43m%[0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%[0;32;40m8;;;;;;;;;;:[0;34;40m          [0;32;40m:;;;;;[0;32;5;40;100mS[0;33;5;43;103m%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%[0;32;40mS[0;34;40m                           [0;30;42m8[0;33;5;43;103m%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%[0;32;40mS[0;34;40m                           [0;30;42m8[0;33;5;43;103m%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%[0;32;40mtttttt;[0;34;40m         [0;32;40m.;ttttttttttt[0;33;5;43;103m%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%[0;1;30;90;43m%[0;32;40mt[0;34;40m        [0;32;40m%[0;1;30;90;43m%[0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%S[0;1;30;90;43m;[0;34;40m        [0;32;40m [0;1;30;90;43mt[0;33;5;43;103mS%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%[0;1;33;93;43mt[0;32;40mS[0;34;40m        [0;32;40mt[0;1;30;90;43m%[0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%[0;1;30;90;43mt[0;32;40m [0;34;40m        [0;1;30;90;42m8[0;33;5;43;103mX%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%[0;1;33;93;43mS[0;30;42m8[0;34;40m        [0;32;40m;[0;1;30;90;43mt[0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%[0;1;30;90;43mt[0;32;40m:[0;34;40m        [0;32;40m [0;1;30;90;43m;tttttttttttttttttttt%[0;33;5;43;103m%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%[0;1;33;93;43m%[0;34;40m                                [0;1;30;90;43mt[0;33;5;43;103m%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%[0;1;33;93;43mt[0;34;40m                                [0;1;30;90;43mt[0;33;5;43;103m%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%[0;1;33;93;43mt[0;34;40m                                [0;1;30;90;43mt[0;33;5;43;103m%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%[0;1;30;90;43mt[0;32;40m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;1;33;93;43mS[0;33;5;43;103m%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m     [0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0;34;40m     [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m                                                                            [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%[0;1;33;93;43mt[0;34;40m                                                                            [0;1;30;90;43mt[0;33;5;43;103m%[0m\n"
"[0;33;5;43;103m%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%[0m\n";



