#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include "TString.h"

class HadoopPathMap
{
public:
    std::map<TString, TString> _map;
    HadoopPathMap();
    ~HadoopPathMap();
    TString getHadoopPath( TString );
};

HadoopPathMap::HadoopPathMap()
{
    ifstream mapfile;
    mapfile.open( "hadoopmap.txt" );
    std::string line, nfspath, hadooppath;
    while ( std::getline( mapfile, line ) ) 
    {
        mapfile >> nfspath >> hadooppath;
        TString nfspath_tstr = nfspath.c_str();
        TString hadooppath_tstr = hadooppath.c_str();
        _map[nfspath_tstr] = hadooppath_tstr;
    }
}

HadoopPathMap::~HadoopPathMap()
{
}

TString HadoopPathMap::getHadoopPath( TString nfspath )
{
    if ( _map.find( nfspath ) != _map.end() )
        return _map[nfspath];
    else
        return nfspath;
}
