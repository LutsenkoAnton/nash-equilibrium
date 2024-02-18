#include <iostream>
#include "game.h"
#include "sat.h"

using namespace std;

// Recursive search of players; in g only the graph should be specified
void generate_players(Game& g) { } // TODO

int main(int argc, __attribute__((unused)) char* argv[]) {
    int n;
    if (argc <= 1) cout << "Input number of vertices: ";
    cin >> n;
    int start;
    if (argc <= 1) cout << "Input starting vertex: ";
    cin >> start;
    --start;
    Game g(n, start);
    if (argc <= 1) cout << "Input players corresponding to vertices: ";
    for (int i = 0; i < n; ++i) {
        int player;
        cin >> player;
        g.set_player(i, player - 1);
    }
    if (argc <= 1) cout << "Input number of edges: ";
    int m;
    cin >> m;
    if (argc <= 1) cout << "Input edges (m lines):\n";
    while (m--) {
        int a, b;
        cin >> a >> b;
        --a;--b;
        g.add_edge(a, b);
    }
    g.fill_components();
    vector<int> cnt_components = g.get_cnt_components();
    vector<int> cycles;
    for (int i = 0; i < g.get_components_count(); ++i) {
        if (cnt_components[i] > 1) {
            cycles.push_back(i);
        }
    }
    g.print_terminal_descriptions();
    SAT initial_sat(g);
    initial_sat.add_all_strategies(g);
    if (!initial_sat.is_solvable()) {
        cout << "\x1b[31;1mThere is a Nash Equlibirum((((\x1b[0m";
    }
    for (int i = 0; i < g.get_player_count(); ++i) {
        for (auto cycle : cycles) {
            SAT s(g);
            s.add_all_strategies(g);
            s.minimize_all_except(cycle, i);
            if (s.is_solvable()) {
                cout << "\x1b[32;1mOH MY GOD YES WE HAVE FOUND IT!!!!!\x1b[0m";
                s.print_beautiful_results();
                return 0;
            }
        }
    }
    cout << "\x1b[31;1m((\x1b[0m";
    // s.minimize_loop_rank(2, 2);
    // s.minimize_all_except(6, 2);
    // s.print_beautiful_results();
    // s.print_all_beautiful_solutions();
    return 0;
}
