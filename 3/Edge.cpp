// Copyright 2025 Morgan Nilsson

#include "Edge.h"

Edge::Edge(int source, int dest, double weight) {
    this->source = source;
    this->dest = dest;
    this->weight = weight;
}

Edge::Edge(int source, int dest) {
    this->source = source;
    this->dest = dest;
}

Edge::~Edge() {}

int Edge::get_dest() const {
    return this->dest;
}

int Edge::get_source() const {
    return this->source;
}

double Edge::get_weight() const {
    return this->weight;
}