#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

static const string pt2_input { R"(#############
#g#f.D#..h#l#
#F###e#E###.#
#dCba@#@BcIJ#
#############
#nK.L@#@G...#
#M###N#H###.#
#o#m..#i#jk.#
#############)"};


static const string pt1_sample_input1 { R"(#################
#i.G..c...e..H.p#
########.########
#j.A..b...f..D.o#
########@########
#k.E..a...g..B.n#
########.########
#l.F..d...h..C.m#
#################)"};


vector<string> split_lines2(const string& input) {
  istringstream s { input };
  vector<string> res;
  string token;

  while(getline(s, token, '\n')) {
    res.push_back(token);
  }

  return res;
}

class Node {
public:
  int x, y;
  char val;

  bool operator<(const Node& b) const{
    return x < b.x || ( x == b.x && y < b.y);
  }
};

template<typename Container, typename FilterFn>
Container filter(Container& s, FilterFn f) {
  Container res;

  copy_if(s.begin(), s.end(), back_inserter(res), f);

  return res;
}

template<typename Node>
class Graph {
  map<Node, set<Node>> _adjacancies;
  void assert_has_node(const Node n) const{
    if(_adjacancies.find(n) == _adjacancies.end()) {
      throw out_of_range("Node not known");
    }
  }

public:
  Graph() {
  }

  Graph& add(const Node n) {
    if(_adjacancies.find(n) != _adjacancies.end()) {
      throw invalid_argument("Node already exists");
    }
    _adjacancies[n] = set<Node>();
    return *this;
  }

  Graph& add_adjacency(const Node for_node, const Node adjacency) {
    assert_has_node(for_node);

    _adjacancies[for_node].insert(adjacency);
    return *this;
  }

  set<Node> nodes() const {
    set<Node> res;
    for(auto n : _adjacancies) {
      res.insert(n.first);
    }
    return res;
  }

  const set<Node> adjacencies(const Node for_node) const {
    assert_has_node(for_node);
    return _adjacancies.find(for_node)->second;
  }
};

Graph<Node> parse_maze(const string& input) {
  vector<Node> all_nodes;
  int i=0;
  for(auto& line : split_lines2(input)) {
    int j=0;
    for(auto c : line) {
      Node n;
      n.x = i;
      n.y = j;
      n.val = c;
      all_nodes.push_back(n);
      j++;
    }
    i++;
  }

  all_nodes = filter(all_nodes,[](Node& n) { return n.val != '#'; });

  map<pair<int,int>, Node> coord_to_node;

  for(auto n : all_nodes) {
    coord_to_node[make_pair(n.x, n.y)] = n;
  }

  Graph<Node> g;

  for(auto n : all_nodes) {
    g.add(n);
    const vector<pair<int,int>> neighbours {{-1,0},{0, -1}, {1,0}, {0,1}};

    for(auto neigh : neighbours) {
      auto adj = coord_to_node.find(make_pair(n.x + neigh.first, n.y + neigh.second));
      if(adj==coord_to_node.end()) {
	continue;
      }
      g.add_adjacency(n, adj->second);
    }
  }

  return g;
}

ostream& operator<<(ostream& o, Node& n) {
  o << n.x << "," << n.y << " => " << n.val;
  return o;
}

int main2() {
  Graph<int> g;

  g.add(1);

  g.add_adjacency(1, 10);
  g.add_adjacency(1, 12);

  for(auto x : g.adjacencies(1)) {
    cout << x << endl;
  }
}

int main() {
  auto maze = parse_maze(pt1_sample_input1);
  // auto node1 = maze.find_node('@');
  // auto node2 = maze.find_node('p');
  // auto route = find_route(maze, node1, node2);

  for(auto node : maze.nodes()) {
    cout << node <<endl;
    for(auto adj : maze.adjacencies(node)) {
      cout << "-> " << adj << endl;
    }
    cout << endl;
  }
}
