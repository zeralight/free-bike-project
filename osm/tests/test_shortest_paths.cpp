#define DEBUG

#include <QtCore>
#include <clocale>

#include <functional>
#include <fstream>
#include <cstring>
#include <iostream>
#include <cassert>
#include <limits>
#include <algorithm>

#include "OsmParser.hpp"
#include "ShortestPaths.hpp"

using namespace osm;
using namespace std;

bool equalFiles(std::string const& fileName1, std::string const& fileName2);

void test1() {

    /*
        Check distance calculation correctness
    */

    std::ifstream cin("input1");
    std::ofstream cout("output1");

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        Nodes nodes(n);
        AdjacencyList edges(n);
        for (int i = 0; i < n; ++i) {
            edges[i].resize(n);
            for (int j = 0; j <n; ++j) {
                edges[i][j].first = j;
                edges[i][j].second = std::numeric_limits<double>::max();
            }
        }
        for (int i = 0; i < n; ++i) {
            nodes[i].id = i;
            nodes[i].isBicycleParking = true;
        }
        for (int i = 0; i < m; ++i) {
            int x, y, r;
            cin >> x >> y >> r;
            --x, --y;
            auto m = std::min((double)r, edges[x][y].second);
            edges[x][y].first = y;
            edges[y][x].first = x;
            edges[x][y].second = edges[y][x].second = m;
        }
/*
        for (int i = 0; i < n; ++i) {
            cerr << "node " << i << " : " << nodes[i].id << ' ' << nodes[i].isBicycleParking << '\n';
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cerr << "edge " << i << " => " << j << " : " << edges[i][j].first << ' ' << edges[i][j].second << '\n';
            }
        }
*/
        int s;
        cin >> s;
        auto paths = AllShortestPaths::run(nodes, edges);
        for (int i = 1; i <= n; ++i) {
            if (s == i)
                continue;
            auto it = paths.find({i-1, s-1});
            if (it == end(paths))
                cout << -1;
            else
                cout << it->second.first;
            if (i < n && s != n)
                cout << ' ';
        }
        cout << '\n';
    }

    cout.close();
    cin.close();
    
    assert (equalFiles("expected_output1", "output1")); 
    std::cout << "Test1 [OK]\n";
}

void test2() {
    /*
        Check path correctness
    */

}

std::function<void()> tests[] = {test1, test2};

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    std::setlocale(LC_NUMERIC, "en_US.UTF-8"); // Avoid floatting number representation problems (3,14 instead of 3.14)

    for (auto const& test: tests)
        test();
    return 0;
}


bool equalFiles(std::string const& fileName1, std::string const& fileName2)
{
    std::ifstream in1(fileName1);
    std::ifstream in2(fileName2);

    std::ifstream::pos_type size1, size2;

    size1 = in1.seekg(0, std::ifstream::end).tellg();
    in1.seekg(0, std::ifstream::beg);

    size2 = in2.seekg(0, std::ifstream::end).tellg();
    in2.seekg(0, std::ifstream::beg);

    if(size1 != size2)
        return false;

    static const size_t BLOCKSIZE = 4096;
    size_t remaining = size1;

    while(remaining)
    {
        char buffer1[BLOCKSIZE], buffer2[BLOCKSIZE];
        std::size_t size = std::min(BLOCKSIZE, remaining);

        in1.read(buffer1, size);
        in2.read(buffer2, size);

        if(0 != std::memcmp(buffer1, buffer2, size))
            return false;

        remaining -= size;
    }

    return true;
}
