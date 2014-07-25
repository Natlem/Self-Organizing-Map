#include "Node.hh"

Node::Node(int eLeft, int eRight, int eTop, int eBottom) : eLeft(eLeft), eRight(eRight), eTop(eTop), eBottom(eBottom) {
    std::mt19937 mt_rand(std::time(0));
    auto double_rand = std::bind(std::uniform_real_distribution<double>(0,1), mt_rand);

    for (auto& d : weight) {
        d = double_rand(); 
    }
    
    n_X = this->eLeft + (double)(this->eRight - this->eLeft)/2;
    n_Y = this->eTop + (double)(this->eBottom - this->eTop)/2;
} 
