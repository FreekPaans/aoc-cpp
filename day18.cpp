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

class MazeNode {
public:
  struct MazeNodeHash
  {
    std::size_t operator()(const MazeNode& n) const noexcept {
      // from https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key

      size_t res = 17;
      res = res * 31 + std::hash<int>{}(n.x);
      res = res * 31 + std::hash<int>{}(n.y);
      res = res * 31 + std::hash<char>{}(n.val);

      return res;
    }
  };

  using hash = MazeNodeHash;
  using set = unordered_set<MazeNode,MazeNodeHash>;
  template <typename MapTo>
  using map = unordered_map<MazeNode,MapTo,MazeNodeHash>;
  int x, y;
  char val;

  bool operator<(const MazeNode& b) const{
    return x < b.x || ( x == b.x && y < b.y);
  }

  bool operator==(const MazeNode& b) const {
    return x == b.x && y == b.y && val == b.val;
  }
};

ostream& operator<<(ostream& o, const MazeNode& n) {
  o << n.x << "," << n.y << " => " << n.val;
  return o;
}

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

Graph<MazeNode> parse_maze(const string& input) {
  vector<MazeNode> all_nodes;
  int i=0;
  for(auto& line : split_lines2(input)) {
    int j=0;
    for(auto c : line) {
      MazeNode n;
      n.x = i;
      n.y = j;
      n.val = c;
      all_nodes.push_back(n);
      j++;
    }
    i++;
  }

  all_nodes = filter(all_nodes,[](const MazeNode& n) { return n.val != '#'; });

  map<pair<int,int>, MazeNode> coord_to_node;

  for(auto n : all_nodes) {
    coord_to_node[make_pair(n.x, n.y)] = n;
  }

  Graph<MazeNode> g;

  for(auto n : all_nodes) {
    g.add(n);
    const vector<pair<int,int>> neighbours {{-1,0},{0, -1}, {1,0}, {0,1}};

    for(auto neigh : neighbours) {
      const auto adj = coord_to_node.find(make_pair(n.x + neigh.first,
						    n.y + neigh.second));
      if(adj==coord_to_node.end()) {
	continue;
      }
      g.add_adjacency(n, adj->second);
    }
  }

  return g;
}

vector<MazeNode> recover_path(const MazeNode::map<MazeNode> parents,
			      const MazeNode from, const MazeNode to) {
  vector<MazeNode> res;

  MazeNode next = to;
  while(true) {
    res.push_back(next);
    if(next == from) {
      break;
    }
    const auto entry = parents.find(next);

    if(entry==parents.end()) {
      throw domain_error("Cannot find node");
    }
    next = entry->second;
  }

  reverse(res.begin(), res.end());

  return res;
}

vector<MazeNode> breadth_first_search(const Graph<MazeNode>& g,
				      const MazeNode from,
				      const MazeNode to) {
  queue<MazeNode> next_nodes;
  MazeNode::set seen_nodes;
  MazeNode::map<MazeNode> parents;

  parents[from] = from;
  next_nodes.push(from);

  while(!next_nodes.empty()) {
    const auto next_node = next_nodes.front();
    next_nodes.pop();

    if(to == next_node) {
      return recover_path(parents, from ,to);
    }

    seen_nodes.insert(next_node);

    for(const auto adjacent : g.adjacencies(next_node)) {
      if(seen_nodes.find(adjacent)!=seen_nodes.end()) {
	continue;
      }
      parents[adjacent] = next_node;
      next_nodes.push(adjacent);
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


vector<MazeNode> maze_all_keys_and_doors(const Graph<MazeNode>& maze) {
  vector<MazeNode> keys_and_doors;

  const auto all_nodes = maze.nodes();

  copy_if(all_nodes.begin(), all_nodes.end(),
	  back_inserter(keys_and_doors),
	  [](const MazeNode& n){
	    return n.val != '.';
	  });
  return keys_and_doors;
}

// struct NodePath {
//   vector<MazeNode> path;
//   set<char> required_keys;
// };
using NodePaths = unordered_map<char,unordered_map<char,vector<char>>>;

NodePaths maze_all_paths(const Graph<MazeNode>& maze) {
  NodePaths node_to_node_path;
  vector<MazeNode> keys_and_doors { maze_all_keys_and_doors(maze) };


  for(int i=0; i<keys_and_doors.size(); i++) {
    for(int j=i+1; j<keys_and_doors.size(); j++) {
      const auto from = keys_and_doors[i];
      const auto to = keys_and_doors[j];

      const auto from_to = breadth_first_search(maze, from, to);

      // auto required_keys = std::accumulate(from_to.begin(), from_to.end(),
      // 					   set<char>(),
      // 					   [](set<char>& s, const MazeNode &n) {
      // 					     if(isupper(n.val)) {
      // 					       s.insert(tolower(n.val));
      // 					     }
      // 					     return s;
      // 					   });

      vector<char> from_to_char;

      transform(from_to.begin(), from_to.end(),
		back_inserter(from_to_char),
		[](const MazeNode n) {
		  return n.val;
		});

      auto reversed = from_to_char;
      reverse(reversed.begin(), reversed.end());

      node_to_node_path[from.val][to.val] = move(from_to_char);
      // node_to_node_path[from][to].required_keys = required_keys;

      node_to_node_path[to.val][from.val] = move(reversed);
      // node_to_node_path[to][from].required_keys = required_keys;
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

bool is_door(char node_val) {
  return isupper(node_val);
}

bool is_key(char node_val) {
  return islower(node_val);
}

vector<MazeNode> find_min_steps(const Graph<MazeNode>& maze,
				MazeNode root) {
  // This function uses modified dijkstra

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

  auto node_to_node_path =
    measure("all_paths",
	    [&maze]() {
	      return maze_all_paths(maze);
	    });

  const auto all_keys = maze_all_keys_and_doors(maze);

  unordered_map<char,MazeNode> key_to_node;
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
    dijkstra_queue(compare_nodes);

  dijkstra_queue.push(root_node);

  const int max_iterations = 10000000;
  int limit = max_iterations;

  unordered_map<char, unordered_map<char, bitset<64>>> path_required_keys;
  unordered_map<char, unordered_map<char, bitset<64>>> path_keys;

  measure("generate path keys",
	  [&node_to_node_path,&path_required_keys, &path_keys,&key_encoding]() {
	    for(auto from_node : node_to_node_path) {
	      for(auto to_node : from_node.second) {
		for(auto node : to_node.second) {
		  path_keys[from_node.first][to_node.first]
		    |= key_encoding[node];

		  if(is_door(node)) {
		    path_required_keys[from_node.first][to_node.first] |= key_encoding[tolower(node)];
		  }
		}
	      }
	    }
	    return 0;
	  });

  MazeNode::map<MazeNode> parents;
  while(true) {
    if(limit--==0) {
      throw domain_error("reached limit");
    }

    if(dijkstra_queue.empty()) {
      break;
    }

    auto current_node = dijkstra_queue.top();
    dijkstra_queue.pop();

    if((current_node.collected_keys & keys_complete) == keys_complete) {
      cout << "All done! " << weights[current_node] << " " << current_node.collected_keys << endl;
      cout << "Took " << max_iterations - limit << " iterations" <<endl;
      return vector<MazeNode>();
    }

    const auto my_weight = weights[current_node];

    for(const auto& adjacent : node_to_node_path[current_node.key]) {
      const auto adj_key = adjacent.first;
      const auto path = adjacent.second;

      if(!is_key(adj_key)) {
	continue;
      }

      const auto required_keys = path_required_keys[current_node.key][adj_key];
      if((current_node.collected_keys & required_keys) != required_keys) {
	continue;
      }

      const auto distance = path.size()-1;
      const node_collected_keys nck(adj_key,
				    current_node.collected_keys |
				    path_keys[current_node.key][adj_key]);

      const auto adj_weight = weights.find(nck);

      if(adj_weight == weights.end() ||
	 (my_weight + distance) < adj_weight->second) {
	parents[key_to_node[adj_key]] = key_to_node[current_node.key];
	weights[nck] = my_weight + distance;
	dijkstra_queue.push(nck);
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
	      return maze_all_paths(maze);
	    });

  const auto all_nodes = maze_all_keys_and_doors(maze);

  const auto root = *find_if(all_nodes.begin(), all_nodes.end(),
			     [](const MazeNode& n) {
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
}
