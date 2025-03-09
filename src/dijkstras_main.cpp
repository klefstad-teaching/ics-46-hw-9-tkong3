#include "dijkstras.h"

int main() {
    Graph test;
    vector<int> prev;
    vector<string> files{"src/small.txt", "src/medium.txt", "src/large.txt", "src/largest.txt"};
    for (string file : files) {
        file_to_graph(file, test);
        cout << file << "\n";
        vector<int> result = dijkstra_shortest_path(test, 0, prev);
        for (size_t i = 0; i < result.size(); ++i) {
            print_path(extract_shortest_path(result, prev, i), result[i]);
        }
        prev.clear();
        test.clear();
    }
    return 0;
}