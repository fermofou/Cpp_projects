#pragma once

template <class T>
struct Edge {
    T source;
    T target;
    int distanceTrain;
    int distanceCar;
    int timeTrain;
    int timeCar;
    Edge();
    Edge(T source, T target);
    Edge(T source, T target, int distanceTrain, int distanceCar, int timeTrain, int timeCar);
};

template<class T>
Edge<T>::Edge() {
    distanceTrain = 0;
    distanceCar = 0;
    timeTrain = 0;
    timeCar = 0;
}

template <class T>
Edge<T>::Edge(T source, T target) {
    this->source = source;
    this->target = target;
    this->distanceTrain = 0;
    this->distanceCar = 0;
    this->timeTrain = 0;
    this->timeCar = 0;
}

template <class T>
Edge<T>::Edge(T source, T target,int distanceTrain, int distanceCar, int timeTrain, int timeCar) {
    this->source = source;
    this->target = target;
    this->distanceTrain = distanceTrain;
    this->distanceCar = distanceCar;
    this->timeTrain = timeTrain;
    this->timeCar = timeCar;
}