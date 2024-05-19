#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>
#include <set>
using namespace std;

#define K_MER 12
#define MIN_OVERLAP 1
#define READSIZE 100
#define DATASIZE 1618
#define fora(i, f, t) for(int i = f; i < t; i++)
#define INF (1<<30)

int Find_Match_Length(const string& read1, const string& read2){
    fora(i, 0, READSIZE){
        int k = i;

        for(int j=0; k < READSIZE; k++, j++)
            if(read1[k] != read2[j]) break;

        if(k == READSIZE)
            return READSIZE - i;
    }
    return 0;
}

void Overlapgraph(const vector<string>& reads, int n, string& genome){
    set<int> visited;
    visited.insert(0); 
    int curRead = 0;
    genome = reads[0];

    while(visited.size() != n){
        int molap = 0, othread = -1;

        fora(i, 0, n){
            if(visited.find(i) == visited.end()){
                int ovl = Find_Match_Length(reads[curRead], reads[i]);

                if(ovl > molap){
                    molap = ovl; 
                    othread = i;        
                }
            }
        }
        genome += reads[othread].substr(molap, READSIZE - molap);
        curRead = othread;
        visited.insert(curRead);  
    }

    genome = genome.substr(0, genome.size() - Find_Match_Length(reads[curRead], reads[0]));

}

int main(int argc, char** argv){
    vector<string> reads;
    set<string> reads_unique;
    string read;

    fora(i, 0, DATASIZE){
        cin >> read;
        
        reads_unique.insert(read);
    }

    for(auto r : reads_unique)
        reads.push_back(r);

    string genome;
    Overlapgraph(reads, reads.size(), genome);
    cout<<genome<<endl;

    return 0;
}