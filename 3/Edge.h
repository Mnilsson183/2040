#ifndef EDGE_H
#define EDGE_H

class Edge
{
private:

    int source;
    int dest;
    double weight;

public:

    Edge(int source, int dest, double weight);
    Edge(int source, int dest);

    ~Edge();

    int get_source() const;
    int get_dest() const;
    double get_weight() const;

    bool operator==(const Edge& other) const {
        return (source == other.source && dest == other.dest);
    }

    bool operator>(const Edge& other) const {
        return (weight > other.weight);
    }

};

#endif