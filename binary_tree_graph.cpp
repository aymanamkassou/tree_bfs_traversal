#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <bitset>
#include <limits>
#include <string>
using namespace std;

// Classe pour representer un arbre binaire avec noeuds contenant des chaines de caracteres
class binary_tree {
private:
    // Stockage des noeuds avec leur position comme cle
    map<int, string> tree;

public:
    // Constructeur pour initialiser avec plusieurs chaines
    binary_tree(vector<string> strings) {
        for (string str : strings) {
            insert_string(str);
        }
    }
    
    // Constructeur pour un seul noeud racine
    binary_tree(string string) {
        tree[0] = string;
    }
    
    // Retourne le nombre de noeuds
    int size() const {
        return tree.size();
    }
    
    // Calcule l'index du fils gauche
    int left_child_index(int index) {
        return (index * 2) + 1;
    }
    
    // Calcule l'index du fils droit
    int right_child_index(int index) {
        return (index * 2) + 2;
    }
    
    // Recupere la valeur a une position donnee
    string string_at_index(const int index) const {
        if (tree.count(index) == 0) {
            return "\0";
        }
        return tree.at(index);
    }
    
    // Verifie si une position est vide
    bool is_null_at_index(const int index) const {
        if (tree.count(index) == 0) {
            return true;
        }
        return false;
    }
    
    // Insere une nouvelle chaine dans l'arbre
    void insert_string(const string& str) {    
        int insertion_index = 0;
        char choice;
        bool inserted = false;
        
        while (!is_null_at_index(insertion_index)) {
            cout << "Would you like to insert " << str << " left (l or L) of " 
                 << tree[insertion_index] << " or right (r or R)?\n";
            cin >> choice;
            
            switch (choice) {
                case 'l':
                case 'L':
                    insertion_index = left_child_index(insertion_index);
                    break;
                case 'r':
                case 'R':
                    insertion_index = right_child_index(insertion_index);
                    break;
                default:
                    cout << "Invalid choice\n";
                    continue;
            }
            
            if (is_null_at_index(insertion_index)) {
                tree.insert({insertion_index, str});
                inserted = true;
                break;
            }
        }
        
        if (!inserted) {
            cout << "Tree is full\n";
        }
    }
    
    // Parcours en largeur (BFS)
    void bfs_traversal() {
        if (tree.empty()) return;
        
        queue<int> q;
        q.push(0);  // Commence a la racine
        
        cout << "BFS Traversal: ";
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            
            if (tree.count(current) > 0) {
                cout << tree[current] << " ";
                
                // Ajoute les fils a la queue
                int left = left_child_index(current);
                int right = right_child_index(current);
                
                if (tree.count(left) > 0) q.push(left);
                if (tree.count(right) > 0) q.push(right);
            }
        }
        cout << endl;
    }
};

// Classe pour un graphe oriente pondere
class weighted_graph {
private:
    static const int MAX_VERTICES = 1000;  // Limite du nombre de sommets
    map<string, int> vertex_to_index;      // Conversion nom vers index
    vector<string> index_to_vertex;        // Conversion index vers nom
    vector<vector<pair<int, int>>> adj_list;  // Liste d'adjacence avec poids
    int vertex_count;

public:
    // Initialise le graphe vide
    weighted_graph() : vertex_count(0) {
        adj_list.resize(MAX_VERTICES);
    }
    
    // Obtient ou cree l'index d'un sommet
    int get_vertex_index(const string& vertex) {
        if (vertex_to_index.find(vertex) == vertex_to_index.end()) {
            vertex_to_index[vertex] = vertex_count;
            index_to_vertex.push_back(vertex);
            vertex_count++;
        }
        return vertex_to_index[vertex];
    }
    
    // Ajoute une arete dirigee
    void add_edge(const string& from, const string& to, int weight) {
        int from_idx = get_vertex_index(from);
        int to_idx = get_vertex_index(to);
        adj_list[from_idx].push_back({to_idx, weight});
    }
    
    // Parcours en largeur avec bitset pour marquer les visites
    void bfs_traversal(const string& start) {
        int start_idx = get_vertex_index(start);
        bitset<MAX_VERTICES> visited;
        queue<int> q;
        
        q.push(start_idx);
        visited.set(start_idx);
        
        cout << "BFS depuis " << start << ": ";
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << index_to_vertex[current] << " ";
            
            // Visite des voisins non explores
            for (const auto& neighbor : adj_list[current]) {
                if (!visited[neighbor.first]) {
                    visited.set(neighbor.first);
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }
    
    // Algorithme de Dijkstra avec file de priorite
    void dijkstra(const string& start) {
        int start_idx = get_vertex_index(start);
        vector<int> distances(vertex_count, numeric_limits<int>::max());
        vector<int> previous(vertex_count, -1);
        
        // File de priorite pour le plus court chemin
        priority_queue<pair<int, int>, vector<pair<int, int>>, 
                      greater<pair<int, int>>> pq;
        
        distances[start_idx] = 0;
        pq.push({0, start_idx});
        
        while (!pq.empty()) {
            int current = pq.top().second;
            int current_dist = pq.top().first;
            pq.pop();
            
            if (current_dist > distances[current]) continue;
            
            // Mise a jour des distances des voisins
            for (const auto& neighbor : adj_list[current]) {
                int new_dist = distances[current] + neighbor.second;
                
                if (new_dist < distances[neighbor.first]) {
                    distances[neighbor.first] = new_dist;
                    previous[neighbor.first] = current;
                    pq.push({new_dist, neighbor.first});
                }
            }
        }
        
        // Affichage des resultats
        cout << "Plus courts chemins depuis " << start << ":" << endl;
        for (int i = 0; i < vertex_count; i++) {
            cout << index_to_vertex[i] << ": ";
            if (distances[i] == numeric_limits<int>::max())
                cout << "inf";
            else
                cout << distances[i];
            cout << endl;
        }
    }
};

int main() {
    // Test de l'arbre binaire
    cout << "Test de l'arbre binaire:" << endl;
    binary_tree hierarchical_map_tree("Africa");
    hierarchical_map_tree.insert_string("Morocco");
    hierarchical_map_tree.insert_string("Grand Casablanca");
    hierarchical_map_tree.insert_string("Benslimane");
    hierarchical_map_tree.insert_string("Mohammedia");
    hierarchical_map_tree.insert_string("Algeria");
    hierarchical_map_tree.insert_string("Constantine");
    hierarchical_map_tree.bfs_traversal();
    
    // Test du graphe
    cout << "\nTest du graphe pondere:" << endl;
    weighted_graph g;
    
    // Creation du graphe avec les villes et distances
    g.add_edge("Casablanca", "Rabat", 87);
    g.add_edge("Rabat", "Tangier", 250);
    g.add_edge("Casablanca", "Marrakech", 240);
    g.add_edge("Marrakech", "Agadir", 260);
    g.add_edge("Rabat", "Fes", 210);
    g.add_edge("Fes", "Tangier", 400);
    g.add_edge("Marrakech", "Fes", 530);
    g.add_edge("Agadir", "Casablanca", 460);
    g.add_edge("Tangier", "Casablanca", 340);
    g.add_edge("Fes", "Oujda", 360);
    
    // Test des algorithmes
    g.bfs_traversal("Casablanca");
    g.dijkstra("Casablanca");
    
    return 0;
}
