#include <cmath>
#include <limits>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;


int main()
{
	PolygonalMesh mesh;

	if(!Import_mesh(mesh)) {
		cerr << "Errore nell'aprire il file" << endl;
		return false;
	}

	// Esportazione
	Gedim::UCDUtilities utilities;
	utilities.ExportPoints("./Cell0Ds.inp", mesh.coords_cell0d);

	utilities.ExportSegments("./Cell1Ds.inp", mesh.coords_cell0d, mesh.extrema_cell1d);


	// Test marker
	
	cout << "Marker OD: " << endl;
	print_markers(mesh.marker_cell0d);

	cout << "Marker 1D: " << endl;
	print_markers(mesh.marker_cell1d);

	cout << "Marker 2D: " << endl;
	print_markers(mesh.marker_cell2d);


	// Test lunghezza lati

	for(unsigned int i = 0; i < mesh.num_cell1d; i++) {
		unsigned int extreme_1 = mesh.extrema_cell1d(0,i);
		unsigned int extreme_2 = mesh.extrema_cell1d(1,i);

		if(mesh.coords_cell0d.col(extreme_1).isApprox(mesh.coords_cell0d.col(extreme_2))) {
			cerr << "Il lato " << i << " è lungo 0" << endl;
			return false;
		}
	}


	// Test area poligoni

	for(const auto& vec : mesh.edges_cell2d) {

		unsigned int len = vec.size();
		double area = 0;

		for(unsigned int i = 0; i < len; i++) {
			unsigned int ex1 = mesh.extrema_cell1d(0, vec[i]);
			unsigned int ex2 = mesh.extrema_cell1d(1, vec[i]);

			double x1 = mesh.coords_cell0d(0, ex1);
			double y1 = mesh.coords_cell0d(1, ex1);
			double x2 = mesh.coords_cell0d(0, ex2);
			double y2 = mesh.coords_cell0d(1, ex2);

			area += ((x1 * y2) - (x2 * y1));
		}

		area = 0.5 * abs(area);

		if(area < numeric_limits<double>::epsilon())
			cerr << "Poligono con area 0" << endl;
	}

	return 0;
}