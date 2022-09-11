#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;

double sum(vector<double> x) {
    double sum = 0;
    for (int i = 0; i < x.size(); i++) {
        sum += x[i];
    }
    return sum;
}

double mean(vector<double> x) {
    int size = x.size();
    return sum(x) / size;
}

double median(vector<double> x) {
    sort(x.begin(), x.end());
    if (x.size() % 2 == 0) {
        return (x[x.size() / 2 - 1] + x[x.size() / 2]) / 2;
    }
    return x[x.size() / 2];
}

double range(vector<double> x) {
    double min = x[0];
    double max = x[0];
    for (int i = 0; i < x.size(); i++) {
        if (x[i] > max) {
            max = x[i];
        }
        if (x[i] < min) {
            min = x[i];
        }
    }
    return max - min;
}

void print_stats(vector<double> x) {
    cout << "\tSum of numeric vector = " << sum(x) << endl;
    cout << "\tMean of numeric vector = " << mean(x) << endl;
    cout << "\tMedian of numeric vector = " << median(x) << endl;
    cout << "\tRange of numeric vector = " << range(x) << endl;
}

double covar(vector<double> x, vector<double> y) {
    double covar = 0;
    double xMean = mean(x);
    double yMean = mean(y);
    double summation = 0;
    for (int i = 0; i < x.size(); i++) {
        summation += ((x[i] - xMean) * (y[i] - yMean));
    }
    covar = summation / (x.size() - 1);
    return covar;
}

double cor(vector<double> x, vector<double> y) {
    double cor = 0;
    double xMean = mean(x);
    double yMean = mean(y);
    double xSummation = 0;
    double ySummation = 0;
    for (int i = 0; i < x.size(); i++) {
        xSummation += ((x[i] - xMean) * (x[i] - xMean));
        ySummation += ((y[i] - yMean) * (y[i] - yMean));
    }
    double xSD = sqrt(xSummation / (x.size() - 1));
    double ySD = sqrt(ySummation / (y.size() - 1));
    cor = covar(x, y) / (xSD * ySD);
    return cor;
}

int main(int argc, char** argv) {
    
    ifstream inFS;
    string line;
    string rm_in, medv_in;
    const int MAX_LEN = 1000;
    vector<double> rm(MAX_LEN);
    vector<double> medv(MAX_LEN);

    cout << "Opening file Boston.csv." << endl;

    inFS.open("Boston.csv");
    if(!inFS.is_open()) {
        cout << "Could not open file Boston.csv." << endl;
        return 1;
    }

    cout << "Reading line 1" << endl;
    getline(inFS, line);

    cout << "heading: " << line << endl;

    int numObservations = 0;
    while (inFS.good()) {
        getline(inFS, rm_in, ',');
        getline(inFS, medv_in, '\n');

        rm.at(numObservations) = stof(rm_in);
        medv.at(numObservations) = stof(medv_in);

        numObservations++;
    }

    rm.resize(numObservations);
    medv.resize(numObservations);

    cout << "new length " << rm.size() << endl;

    cout << "Closing file Boston.csv." << endl;
    inFS.close();

    cout << "\nStats for rm" << endl;
    print_stats(rm);

    cout << "\nStats for medv" << endl;
    print_stats(medv);

    cout << "\n Covariance = " << covar(rm, medv) << endl;

    cout << "\n Correlation = " << cor(rm, medv) << endl;

    cout << "\nProgram terminated.";
    
    return 0;
}