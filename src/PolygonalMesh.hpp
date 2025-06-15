#pragma once

#include <vector>
#include <map>
#include <list>
#include <Eigen/Eigen>

using namespace std;
using namespace Eigen;


namespace PolygonalLibrary
{

struct PolygonalMesh
{
	// Numero celle
	unsigned int num_cell0d;
	unsigned int num_cell1d;
	unsigned int num_cell2d;

	// ID
	vector<unsigned int> id_cell0d;
	vector<unsigned int> id_cell1d;
	vector<unsigned int> id_cell2d;

	// Marker
	map<unsigned int, list<unsigned int>> marker_cell0d;
	map<unsigned int, list<unsigned int>> marker_cell1d;
	map<unsigned int, list<unsigned int>> marker_cell2d;

	// Coordinate dei punti
	MatrixXd coords_cell0d;

	// Estremi dei lati
	MatrixXi extrema_cell1d;

	// Vertici del poligono
	vector<vector<unsigned int>> vertices_cell2d;
	// Lati del poligono
	vector<vector<unsigned int>> edges_cell2d;

};
}