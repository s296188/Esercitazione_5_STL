#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include "PolygonalMesh.hpp"

using namespace std;
using namespace PolygonalLibrary;


bool Import_mesh(PolygonalMesh& mesh);

bool Import_file(const string& file_name, list<string>& lines);

bool Import_cell0d(PolygonalMesh& mesh);

bool Import_cell1d(PolygonalMesh& mesh);

bool Import_cell2d(PolygonalMesh& mesh);


void print_markers(const map<unsigned int, list<unsigned int>>& markers);
