/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  m258zhan @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Fall) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"

using namespace std;

class Weighted_graph {
	private:
		static const double INF;
		double** graph;//adjacency matrix
    //int* degrees;//degree of each node
		int num_nodes;
		int num_edges;

		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );

		// your choice

	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int n ) {
    
    num_nodes = n;
    num_edges = 0;
    if (n <= 0) {
        throw illegal_argument();
    }
    graph = new double*[n];
    //degrees = new int [n];
    for (int i = 0; i < n; i++) {
        graph[i] = new double[n];
    }
    for (int i = 0; i < n; i++) {
        //degrees[i] = 0;
        for (int j = 0; j < n; j++) {
                graph[i][j] = 0.0;
        }
    }
}

Weighted_graph::~Weighted_graph() {
    for (int i = 0; i < num_nodes; i++) {
        delete [] graph[i];
    }
    delete [] graph;
    //delete [] degrees;
}

int Weighted_graph::degree(int u) const {
    if (u < 0 || u > num_nodes - 1) {
        throw illegal_argument();
    }
    int degrees = 0;
    for (int i = 0; i < num_nodes; i++) {
        if (graph[u][i] != 0) {
            degrees++;
        }
    }
    return degrees;

}

int Weighted_graph::edge_count() const {
	return num_edges;
}

bool Weighted_graph::erase_edge(int i, int j) {
    if (i < 0 || i > (num_nodes-1)) {
        throw illegal_argument();
    }
    if (j < 0 || j > (num_nodes-1)) {
        throw illegal_argument();
    }
    if (graph[i][j] == 0.0) {
        if (i == j) {
            return true;
        }
        return false;
    }
    if (graph[i][j] != 0.0) {
        if (i == j) {
            return true;
        }
        graph[i][j] = 0.0;
        graph[j][i] = 0.0;
        
        //degrees[i]--;
        //degrees[j]--;
        num_edges--;
        return true;
    }return true;
}

void Weighted_graph::clear_edges() {
    for (int i = 0; i < num_nodes; i++) {
        //degrees[i] = 0;
        for (int j = 0; j < num_nodes; j++) {
            graph[i][j] = 0.0;
        }
    }
    num_edges = 0;
	return;
}

bool Weighted_graph::insert_edge( int i, int j, double d ) {
    
    if (i < 0 || i > (num_nodes-1)) {
        throw illegal_argument();
    }
    
    if (j < 0 || j > (num_nodes-1)) {
        throw illegal_argument();
    }
    
    if (d <= 0) {
        throw illegal_argument();
    }
    
    if (i == j && i < num_nodes) {
        return false;
    }
    else if (graph[i][j] != 0.0){
        graph[i][j] = d;
        graph[j][i] = d;
        return true;
    }
    else{
        graph[i][j] = d;
        graph[j][i] = d;
        //degrees[i]++;
        //degrees[j]++;
    }
    num_edges++;
	return true;
}

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
    Disjoint_set sets(num_nodes);
    int entries = num_nodes*num_nodes;
    int counter = 0;
    double* weights = new double [entries];
    int* u = new int [entries];
    int* v = new int [entries];
    int edges = 0;
    double totalWeight = 0.0;
    for(int i = 0; i < entries; i++){
        u[i] = 0;
        v[i] = 0;
        weights[i] = 0.0;
    }
    for (int i = 0; i < num_nodes; i++)
    {
        for (int j = 0; j < num_nodes; j++)
        {
            if (graph[i][j] != 0.0)
            {
                u[counter] = i;
                v[counter] = j;
                weights[counter] = graph[i][j];
                counter++;
              
            }
        }
    }
    counter = 0;
    int i, j, first, tmpI;
    double tmpD;
    for (i = 0; i < entries -1; i++)
    {
        first = i;                 // initialize to subscript of first element
        for (j = i + 1; j < entries; j++)   // locate smallest between positions 1 and i.
        {
            if (weights[j] < weights[first])
                first = j;
        }
        tmpD = weights[first];   // Swap smallest found with element in position i.
        weights[first] = weights[i];
        weights[i] = tmpD;
        
        tmpI = u[first];
        u[first] = u[i];
        u[i] = tmpI;
        
        tmpI = v[first];
        v[first] = v[i];
        v[i] = tmpI;

    }
    for (int i = 0; i < entries; i++)
    {
        if (weights[i] != 0.0) {
            if (sets.find_set(u[i]) != sets.find_set(v[i]))
            {
                sets.union_sets(u[i], v[i]);
                totalWeight = totalWeight + weights[i];
                
            }
            edges++;
            if (sets.num_sets() == 1) {
                break;
            }
        }
    }
    edges = (edges + 1) / 2;
    delete[] u;
    delete[] v;
    delete[] weights;
    return std::pair<double, int>(totalWeight, edges);
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
    
    
    return out;
}


#endif
