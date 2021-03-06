/*
 * Particle.hh
 *
 *  Created on: Jul 19, 2015
 *      Author: brandon
 */

#ifndef PARTICLE_HH_
#define PARTICLE_HH_

#include "Model.hh"
#include "Swarm.hh"

class Swarm;
class Data;
class FreeParam;
class Model;
class FreeParam;
class Data;
class Pheromones;
class Particle;

class Particle {
public:
	Particle(Swarm * swarm, int id);
	void setModel(Model * model);
	void setParam(std::pair<std::string, double> myParams);
	std::map<std::string,double> getParams() { return simParams_; }
	void setID(int id);
	int getID() { return id_; }

	void doParticle();
	void generateParams();

	std::map<int, double> fitCalcs;
	std::map<std::string, double> simParams_;

private:
	friend class boost::serialization::access;

	void runModel(unsigned int id = 0, bool localSearch = false);
	void checkMessagesGenetic();
	void checkMessagesPSO();
	bool checkMessagesDE();

	void runNelderMead(std::map<double, std::vector<double>> simplex);
	std::vector<double> getCentroid(std::vector<std::vector<double>>);

	void calculateFit(bool local = false);
	double objFunc_chiSquare(double sim, double exp, double stdev);
	double objFunc_sumOfSquares(double sim, double exp, double dummyvar);
	double objFunc_divByMeasured(double sim, double exp, double dummyvar);
	double objFunc_divByMean(double sim, double exp, double mean);

	void smoothRuns();
	void finalizeSim();

	typedef double (Particle::*objFunc)(double exp,double sim ,double stdev);

	objFunc objFuncPtr;

	Model * model_;
	unsigned int id_;
	std::map<std::string, std::map<int, Data*>> dataFiles_;
	Swarm * swarm_;
	unsigned int currentGeneration_;
	unsigned int island_;

	template<typename Archive>
	void serialize(Archive& ar, const unsigned version) {

		ar & model_;
		ar & simParams_;
		ar & id_;
		ar & dataFiles_;
		ar & swarm_;
		ar & currentGeneration_;
	}
};
#endif /* PARTICLE_HH_ */
