#include <iostream>
#include <bitset>
#include <numeric>
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

static const string pt1_sample_input2 { R"(########################
#...............b.C.D.f#
#.######################
#.....@.a.B.c.d.A.e.F.g#
########################)"};

static const string pt1_sample_input3 {R"(########################
#@..............ac.GI.b#
###d#e#f################
###A#B#C################
###g#h#i################
########################)"};

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

  const typename Node::set& adjacencies(const Node for_node) const {
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

vector<Node> recover_path(const Node::map<Node> parents,
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
  Node::set seen;
  Node::map<Node> parents;

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

ostream& operator<<(ostream& o, const Node& n) {
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

struct NodePath {
  vector<Node> path;
  set<char> required_keys;
};
using NodePaths = Node::map<Node::map<NodePath>>;

NodePaths all_paths(const Graph<Node>& maze) {
  NodePaths node_to_node_path;
  vector<Node> all_nodes_v { maze_all_nodes(maze) };

  for(int i=0; i<all_nodes_v.size(); i++) {
    for(int j=i+1; j<all_nodes_v.size(); j++) {
      const auto from = all_nodes_v[i];
      const auto to = all_nodes_v[j];

      const auto from_to = breadth_first_search(maze, from, to);

      auto required_keys = std::accumulate(from_to.begin(), from_to.end(),
					   set<char>(),
					   [](set<char>& s, const Node &n) {
					     if(isupper(n.val)) {
					       s.insert(tolower(n.val));
					     }
					     return s;
					   });

      auto reversed = from_to;
      reverse(reversed.begin(), reversed.end());

      node_to_node_path[from][to].path = move(from_to);
      node_to_node_path[from][to].required_keys = required_keys;

      node_to_node_path[to][from].path = move(reversed);
      node_to_node_path[to][from].required_keys = required_keys;
    }
  }

  return node_to_node_path;
}

template<typename F>
auto measure(string label, F f) -> decltype(f()){
  auto before = high_resolution_clock::now();

  auto result = f();

  auto after = high_resolution_clock::now();

  cout << "Timing " << label << ": "
       << duration_cast<microseconds>(after - before).count()
       << "us"
       << endl;

  return result;
}

vector<Node> find_min_steps(const Graph<Node>& maze,
			    Node root) {
  // todo recheck weight in prio-queue
  struct node_collected_keys{
    node_collected_keys() {}

    node_collected_keys(const char key,
			const bitset<64> collected_keys)
      : key{key},
	collected_keys{collected_keys} {
	}
    char key;
    bitset<64> collected_keys;

    bool operator==(const node_collected_keys& nck) const {
      return key == nck.key && collected_keys == nck.collected_keys;
    }
  };

  struct hash {
    std::size_t operator()(const node_collected_keys& n) const noexcept {
      // from https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key

      size_t res = 17;
      res = res * 31 + std::hash<char>{}(n.key);
      res = res * 31 + std::hash<bitset<64>>{}(n.collected_keys);

      return res;
    }
  };


  // This function uses modified dijkstra
  auto node_to_node_path =
    measure("all_paths",
	    [&maze]() {
	      return all_paths(maze);
	    });
  


  const auto all_keys = maze_all_nodes(maze);

  unordered_map<char,Node> key_to_node;
  unordered_map<char,bitset<64>> key_encoding;

  if(all_keys.size()>64) {
    throw invalid_argument("Cannot solve maze with more than 64 keys");
  }

  bitset<64> keys_complete;
  unsigned long bit_idx=0;

  for(auto key : all_keys) {
    // can we leave bit_idx in this scope?
    key_to_node[key.val] = key;
    if(islower(key.val)) {
      keys_complete.set(bit_idx);
    }
    key_encoding[key.val].set(bit_idx);
    bit_idx++;
  }

  node_collected_keys root_node {root.val, key_encoding['@']};
  unordered_map<node_collected_keys,int,hash> weights {{root_node, 0}};

  //todo try non-ref
  auto compare_nodes = [&weights](const node_collected_keys& n1,
				  const node_collected_keys& n2) {
			 return weights[n1] > weights[n2];
		       };
  // todo can we not explicitly provide the second template argument (vector<Node>)?
  priority_queue<node_collected_keys,
		 vector<node_collected_keys>,
		 decltype(compare_nodes) >
    smallest_path(compare_nodes);

  smallest_path.push(root_node);

  const int max_iterations = 10000000;
  int limit = max_iterations;

  Node::map<Node> parents;
  while(true) {
    if(limit--==0) {
      throw domain_error("reached limit");
    }

    if(smallest_path.empty()) {
      break;
    }
    auto smallest = smallest_path.top();
    smallest_path.pop();

    if((smallest.collected_keys & keys_complete) == keys_complete) {
      cout << "All done! " << weights[smallest] << " " << bitset<64>(smallest.collected_keys) << endl;
      cout << "Took " << max_iterations - limit << " iterations" <<endl;
      return vector<Node>();
    }

    const auto my_weight = weights[smallest];

    for(auto& adjacent : node_to_node_path[key_to_node[smallest.key]]) {
      if(!islower(adjacent.first.val)) {
	continue;
      }

      // feel there should be a better way to check if we have all keys...
      int have_keys=0;

      // TODO: accumulate, already already store

      for(auto required_key : adjacent.second.required_keys) {
	if((key_encoding[required_key] & smallest.collected_keys) == 0) {
	  break;
	}
	have_keys++;
      }

      if(have_keys!=adjacent.second.required_keys.size()) {
	continue;
      }


      const auto adj_key = adjacent.first.val;
      const auto dist = adjacent.second.path.size()-1;

      bitset<64> key_builder;
      for(auto i : adjacent.second.path) {
	key_builder |= key_encoding[i.val];
      }
      node_collected_keys nck(adj_key,
			      smallest.collected_keys | key_builder);
      const auto adj_weight = weights.find(nck);

      if(adj_weight == weights.end() ||
	 (my_weight + dist) < adj_weight->second) {
	parents[adjacent.first] = key_to_node[smallest.key];
	weights[nck] = my_weight + dist;
	smallest_path.push(nck);
      }
    }
  }

  throw domain_error("Couldn't find path");
}

int main() {
  auto input = pt1_real_input;
  // auto input = pt1_sample_input1;
  // auto input = pt1_sample_input2;
  // auto input = pt1_sample_input3;

  const auto maze =
    measure("parse_maze",
	    [&input]() {
	      return parse_maze(input);
	    });

  auto node_to_node_path =
    measure("all_paths",
	    [&maze]() {
	      return all_paths(maze);
	    });

  const auto all_nodes = maze_all_nodes(maze);

  const auto root = *find_if(all_nodes.begin(), all_nodes.end(),
			    [](const Node& n) {
			      return n.val == '@';
			    });


  cout << "Root: " << root << endl;

  auto steps =
    measure("all steps", [&maze,&root]() {
    return find_min_steps(maze, root);
			 });

  cout << "Steps: "<< steps.size() << endl;

  int i=0;
  for(auto s : steps) {
    cout << i++ << " " << s << endl;
  }

  
  // cout << "Node count: " << all_nodes.size() << endl;

  // const auto first = all_nodes[0];
  // const auto last = all_nodes[all_nodes.size()-1];

  // const auto& node_path = node_to_node_path[first][last];
  // const auto& steps = node_path.path;
  // cout << first.val << " - > " << last.val << endl;
  // for(auto n : steps) {
  //   cout << n << endl;
  // }

  // for(auto n : node_to_node_path[last][first].path) {
  //   cout << n << endl;
  // }

  // cout << "Keys required:" << endl;

  // for(auto k : node_path.required_keys) {
  //   cout << k << " ";
  // }
  // cout << endl;

  // cout << "Total steps: " << steps.size() << endl;
  // cout << "Total paths: " << (all_nodes.size() * all_nodes.size() / 2) << endl;
}
