#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <chrono>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;
using namespace std::chrono;

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

static const string pt1_real_input { R"(#################################################################################
#..f....#...........#.....#.........#m..#.........#.#.......#...............#...#
#.#.###.#########.#.#.###.#.#.#####.#.#.#Q#.#####.#.#.###.###.#V#####.#####.#.#C#
#.#...#...........#t#.#.#...#.#...#.#.#.#.#.#.......#.#.#.....#.....#.#...#...#.#
#####.###############.#.#####.#.#.###.#.#.#.#########.#.###########.###.#.#####.#
#.....#...............#...#.#...#...#.#.#.#.........#.#...........#.....#.#...#e#
#.###.#.###############.#.#.#######.#I#.#.#########.#.###########.#####.#.#.#.#.#
#...#.#...#.....#.......#.....#.G.#.#.#.#.#.......#.#.....#.......#...#.#...#.#.#
###.#.###.#.#.#.###.###########.#.#.#.#.#.#####.#.#.#####.#.#.#####.#.#######.#.#
#...#.#...#.#.#...#.#...#.....#b#.#...#.#.......#.#.........#.#.....#.#...#...#.#
#.#####.###.#.###.#.#.#.#.###.#.#.#####.#########.#############.#####.#.#.#.###.#
#.......#.#.#...#.Z.#.#.B.#.....#.....#.#.......#.....#.........#.#.....#...#...#
#.#######.#.###.#####.#.#############.#M#.#.#########.#.#########.#.#############
#.#.......#...#.#.....#u#...K.......#.#.#.#...........#...#.........#...........#
#.###.###.#.###.#.#####.#.#####.###.#.#.#.#############.#.#.#########.#########.#
#...#...#...#...#.U.#...#.#..j#...#.#g..#.......#...R.#.#.#.....#.....#.......#.#
###.#######.#.#####.#####.#.#.###.#.#############.###.#.#.#######.#########.###.#
#.#.......#.#.....#..k....#.#.#d..#.#...#.........#...#.#.........#.#.......#...#
#.#######.#.#####.#####.###.#.#####.#.#.#.#########.###.#########.#.#.#.#####.#.#
#.....#...#.#.....#.H.#.#...#.S...#.D.#.#...#.....#.#...#.#.....#.#...#..a#...#.#
#.#.#.#.#####.#####.#.#.#.#######.#####.###.#.###.#.###.#.#.###.#.#.#####.#.###.#
#.#.#.#...#...#...#.#.#.#.#.....#.....#s#...#...#.#...#...#...#.#.#...#...#.#...#
###.#.###.#.###.#.#.#####J###.#######.#.#.#######.###.###.#####.#.#.###.#.#.#.###
#...#.#...#.#...#.#.#.....#...#.....#...#.#...#.....#.#...#...#.#.#.#...#.#.#...#
#.#####.###.#.###.#.###.###.###.#.#.#####.#.#.#.###.#.###.###.#.#.###.###.#.###.#
#.....#...#...#...#....h#...#...#.#.#...#...#.#.#.#.#...#.....#.#.....#...#.#.#.#
#.###.###.#.###.###########.#.###.#.###.#####.#.#.#.###.#######.#######.###.#.#.#
#.#.#.....#.#...#.....#...#...#.#.#.....#...#...#...#.#...#.....#.......#.#.#..p#
#.#.#########.###.#.#.#.#.###.#.#.#####.#.#######.###.###.#.###########.#.#.###.#
#.#.#.......#.....#.#...#...#...#.#...#.#.......#.#.#...#.#.......#...#.#.#...#.#
#.#.#.###.#.#.#####.#######.#####.###.#.#.#####.#.#.#.#.#.#######.#.#.#.#.###.#.#
#.#...#...#.#.....#.......#.....#...#...#.....#.#.#...#.#...#...#...#.#.#.#...#.#
#.#####.###.#####.#######.#####.###.#.###.#####.#.#####.#.###.#.#####.#.#.#.###.#
#...N.#.#.#.#.....#.......#...#.....#.#.#.#...#.#.......#.....#.......#...#...#.#
#####.#.#.#.#.#####.#######.#########.#.###.#.#.#######.#####################.#.#
#...#...#...#.....#.......#.#...#.....#.#...#.....#...X.#.....Y.#...#...W.....#.#
###.#####.#######.#######.#.#.#.#.#####.#.#########.#########.#.###.#.#.#######.#
#...#.....#...#.....#...#.#.#.#...#.....#.#.....#...#...#...#.#...#...#.#.#.....#
#.###.#####.#.#######.#.#.#.#.#######.#.#.#.###.#.###.#.#.#.#.###.#####.#.#.#####
#.........A.#.........#...#..x........#.......#.......#...#...#.........#.......#
#######################################.@.#######################################
#.O.......#.............#.......#.....................#...........#...#...#.#...#
###.#####.#######.#####.###.#.#.#.#####.#.#.#########.#######.###.#.#.#.#.#.#.#.#
#...#...#.......#.#..y....#.#.#.#.#...#.#.#.#.....#.........#...#.#.#...#.#.#.#.#
#.#####.#######.#.#.#####.###.#.#.#.#.#.###.#.###.#########.###.#.#.#####.#.#.#.#
#.#...#.......#.#.#.#...#.....#...#.#.#.#...#...#...#.....#.....#.#...#.#.#...#.#
#.#.#.#####.###.#.###.#.#############.#.#.#####.###.#.###.#######.###.#.#.#####.#
#..r#.#...#.....#.#.L.#.#...#...#.....#.#.........#.#.#...#.....#.....#.#.#..n..#
#####.#.#.###.###.#.###.#.#.#.#.###.###.#.#######.#.#.#.###.###.#######.#.#.#####
#...#...#...#..w..#.#.#.#.#.#.#...#...#.#...#...#.#...#...#.#...#.....#...#.....#
#.#.#######.#######.#.#.#.#.#.###.###.#.###.#.#.#######.#.#.#.#####.###.###.###.#
#.#...#...#.....#...#.#...#.....#...#.#.#.#.#.#.......#.#...#.#...#.#...#...#...#
###.#.#.#######.#.###.#########.###.#.#.#.#.#.#######.#.#####.#.#.#.#.#####.#.###
#...#...#...#.P.#.#...#.#.....#.#...#.#.#...#.#.#...#.#...#o#...#.#...#...#.#...#
#.#####.#.#.#.###.#.#.#.#.###.###.###.#.#.###.#.#.#.#.###.#.#####.#.###.#.#.###.#
#.....#.#.#.#.....#.#...#...#.....#...#.#...#.#...#.#.#.....#.....#.#...#.#...#.#
#.###.#.#.#.#######.#######.#########.#.#####.#.###.#.#.#####.#####.#.###.#.###.#
#.#.#.#.#.#...#.#.....#.....#...#...#.#.#.....#.#.#.#.#.#.....#...#.#...#.#.#...#
#.#.#.###.#.#.#.#.###.#.#####.#.#.#.#.#.#.#####.#.#.#.###.#####.###.###.#.###.###
#.#.#.E...#.#.#...#...#...#...#...#...#.#.....#.#.#.......#.........#..l#...#...#
#.#.#######.#.#####.###.#.#.#.#####.###.#####.#.#.#########.###.#####.#####.###.#
#.#.......#.#.....#.#.#.#.#.#.#...#.#...#.....#.#.#.....#...#.#.#...#.#...#.....#
#.#.#####.#.#####.#.#.#.#.###.#.#.###.###.#####.#.#.###.#####.#.#.#.#.###.#####.#
#.#.#.....#.#.......#.#.#.#...#.#.#...#.#.#.....#.#.#.#.....#.#...#...#...#.....#
#.#.#.#####.#.#######.#.#.#.###.#.#.###.#.#.#####.#.#.#####.#.#########.###.#####
#.#.#...#...#.#..q#...#.#.#.....#.#.#...#.#.#.....#.#.....#.#.......#...#...#...#
#.#.#.###.###.#.#.#.#####.#.#####.#.###.#.#.#.#.###.###.#.#.#######.#.#.#.#####.#
#.#.#.#...#.#...#.#.......#.....#.#...#.#.#...#.#v..#...#.#...#.....#.#.#.#...#.#
#.#.#.#.###.#.#################.#.###.#.#.###.###.###.#######.#.#####.###.#.#.#.#
#...#.#...#...#.............#...#...#.#.#...#.#...#.........#...#.......#...#...#
#.#####.#.#####.#.###########.#####.#.#.#.#.###.###########.#####.#####.#######.#
#.#...#.#.#.....#.....#.......#.....#.#.#.#...#.#...............#.#...#.......#.#
###.#.###.#.#########.#.#######.#####.#.#.###.#.#.#.#############.###.#####.###.#
#...#...#.#.#.........#.#.....#.....#.#.#.#...#.#.#....c..........#.....#.#.....#
#.#####.#.#.#.#########.#.#.#.#####.#.#.###.###.#.#################.###.#.#######
#.....#...#z#.......#...#.#.#...#.#.#.#.#...#...#.....#.....#...#...#.#.#.......#
#.###.#####.#######.#.###.#.###.#.#.#.#.#.###.#######.###.#.#.#.#.###.#.#T#.###.#
#...#.....#...#...#...#...#...#...#.#.#.#...#.#...#...#...#.#.#...#.#...#.#.#.#.#
###.#####.###.#.#.###########.###.#.#.#.#.#.#.#.###.###.###.#.#####.#F#####.#.#.#
#.......#.......#.............#...#.....#.#...#.........#.....#.............#i..#
#################################################################################)"};


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
  struct NodeHash
  {
    std::size_t operator()(const Node& n) const noexcept {
      // from https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key

      size_t res = 17;
      res = res * 31 + std::hash<int>{}(n.x);
      res = res * 31 + std::hash<int>{}(n.y);
      res = res * 31 + std::hash<char>{}(n.val);

      return res;
    }
  };

  using hash = NodeHash;
  using set = unordered_set<Node,NodeHash>;
  template <typename MapTo>
  using map = unordered_map<Node,MapTo,NodeHash>;
  int x, y;
  char val;

  bool operator<(const Node& b) const{
    return x < b.x || ( x == b.x && y < b.y);
  }

  bool operator==(const Node& b) const {
    return x == b.x && y == b.y && val == b.val;
  }
};

template<typename Container, typename FilterFn>
Container filter(const Container& s, const FilterFn f) {
  Container res;

  copy_if(s.begin(), s.end(), back_inserter(res), f);

  return res;
}

template<typename Container, typename FilterFn>
Container filter_set(const Container&& s, const FilterFn f) {
  Container res;

  copy_if(s.begin(), s.end(), inserter(res, res.begin()), f);

  return res;
};

template<typename Node>
class Graph {
  typename Node::template map<typename Node::set> _adjacancies;

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
    _adjacancies[n] = typename Node::set();
    return *this;
  }

  Graph& add_adjacency(const Node for_node, const Node adjacency) {
    assert_has_node(for_node);

    _adjacancies[for_node].insert(adjacency);
    return *this;
  }

  typename Node::set nodes() const {
    typename Node::set res;
    for(auto n : _adjacancies) {
      res.insert(n.first);
    }
    return res;
  }

  const typename Node::set adjacencies(const Node for_node) const {
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

  all_nodes = filter(all_nodes,[](const Node& n) { return n.val != '#'; });

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

vector<Node> recover_path(const typename Node::map<Node> parents,
			  Node from, Node to) {
  vector<Node> res;

  Node next = to;
  while(true) {
    res.push_back(next);
    if(next == from) {
      break;
    }
    auto entry = parents.find(next);

    if(entry==parents.end()) {
      throw domain_error("Cannot find node");
    }
    next = entry->second;
  }

  reverse(res.begin(), res.end());

  return res;
}

vector<Node> breadth_first_search(const Graph<Node>& g,
				  const Node from,
				  const Node to) {
  queue<Node> next;
  typename Node::set seen;
  typename Node::map<Node> parents;

  next.push(from);

  parents[from] = from;

  while(!next.empty()) {
    auto nextNode = next.front();
    next.pop();

    if(to == nextNode) {
      return recover_path(parents, from ,to);
    }

    seen.insert(nextNode);

    for(auto adjacent : g.adjacencies(nextNode)) {
      if(seen.find(adjacent)!=seen.end()) {
	continue;
      }
      parents[adjacent] = nextNode;
      next.push(adjacent);
    }
  }

  throw domain_error("Couldn't find route");
}

int main2() {
//   Graph<int> g;

//   g.add(1);

//   g.add_adjacency(1, 10);
//   g.add_adjacency(1, 12);

//   for(auto x : g.adjacencies(1)) {
//     cout << x << endl;
//   }
  
}

ostream& operator<<(ostream& o, Node& n) {
  o << n.x << "," << n.y << " => " << n.val;
  return o;
}

vector<Node> maze_all_nodes(const Graph<Node>& maze) {
  const auto all_nodes {
    filter_set(maze.nodes(),
	       [](const Node& n){
		 return n.val != '.';
	       })};


  vector<Node> nodes { all_nodes.begin(), all_nodes.end() };
  return nodes;
}

using NodePaths = Node::map<typename Node::map<vector<Node>>>;

NodePaths all_paths(const Graph<Node>& maze) {
  NodePaths node_to_node_path;
  vector<Node> all_nodes_v { maze_all_nodes(maze) };

  for(int i=0; i<all_nodes_v.size(); i++) {
    for(int j=i+1; j<all_nodes_v.size(); j++) {
      const auto from = all_nodes_v[i];
      const auto to = all_nodes_v[j];
      node_to_node_path[from][to] = breadth_first_search(maze, from, to);

      auto reversed = node_to_node_path[from][to];
      reverse(reversed.begin(), reversed.end());
      node_to_node_path[to][from] = move(reversed);
    }
  }

  return node_to_node_path;
}

int main() {
  const auto maze = parse_maze(pt1_real_input);
  // const auto maze = parse_maze(pt1_sample_input1);
  // auto node1 = maze.find_node('@');
  // auto node2 = maze.find_node('p');
  // auto route = find_route(maze, node1, node2);

  auto before = high_resolution_clock::now();

  auto node_to_node_path = all_paths(maze);

  auto after = high_resolution_clock::now();

  cout << (node_to_node_path.size()/2) << endl;

  const auto all_nodes = maze_all_nodes(maze);
  const auto first = all_nodes[0];
  const auto last = all_nodes[all_nodes.size()-1];

  auto steps = node_to_node_path[first][last];
  cout << first.val << " - > " << last.val << endl;
  for(auto n : steps) {
    cout << n << endl;
  }

  for(auto n : node_to_node_path[last][first]) {
    cout << n << endl;
  }
  cout << "Total steps: " << steps.size() << endl;
  cout << "Total paths: " << (all_nodes.size() * all_nodes.size() / 2) << endl;

  cout << "Duration: " << duration_cast<microseconds>(after - before).count() << "us" << endl;
}
