# pragma once

#include <iostream>
#include <vector>
#include <Eigen/Eigen>

using namespace std;
using namespace Eigen;

namespace PolygonalLibrary {
	
struct PolygonalMesh
{
	// 0D
	unsigned int NumCell0Ds = 0;
	vector<unsigned int> Cell0DsId = {};
	MatrixXd Cell0DsCoordinates = {};
	map<unsigned int, list<unsigned int>> Cell0DsMarkers = {};
	
	// 1D
	unsigned int NumCell1Ds = 0;
	vector<unsigned int> Cell1DsId = {};
	MatrixXi Cell1DsExtrema = {};
	map<unsigned int, list<unsigned int>> Cell1DsMarkers = {};
	
	// 2D
	unsigned int NumCell2Ds = 0;
	vector<unsigned int> Cell2DsId = {};
	map<unsigned int, list<unsigned int>> NumCell2DsVertices = {};
	vector<vector<unsigned int>> Cell2DsVertices = {};  
	map<unsigned int, list<unsigned int>> NumCell2DsEdges = {};
	vector<vector<unsigned int>> Cell2DsEdges = {};     
	
};

}
