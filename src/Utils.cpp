#include "Utils.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;


bool Import_mesh(PolygonalMesh& mesh)
{
	if(!Import_cell0d(mesh))
		return false;

	if(!Import_cell1d(mesh))
		return false;

	if(!Import_cell2d(mesh))
		return false;

	return true;
}


bool Import_file(const string& file_name, list<string>& lines_list)
{
	ifstream ifstr(file_name);

	if(ifstr.fail()) {
		cerr << "Errore con " << file_name << endl;
		return false;
	}
	
	string line;

	while(ifstr >> line)
		lines_list.push_back(line);

	ifstr.close();

	lines_list.pop_front();

	return true;
}


bool Import_cell0d(PolygonalMesh& mesh)
{
	string file_name = "Cell0Ds.csv";
	list<string> lines_list;
	Import_file(file_name, lines_list);

	mesh.num_cell0d = lines_list.size();

	if(mesh.num_cell0d == 0) {
		cerr << "cell0D vuoto" << endl;
		return false;
	}

	mesh.id_cell0d.reserve(mesh.num_cell0d);

	mesh.coords_cell0d = MatrixXd::Zero(3, mesh.num_cell0d);

	string line;
	char sep;
	unsigned int id;
	unsigned int marker;

	for(const auto& line : lines_list) {
		stringstream sstr(line);

		sstr >> id >> sep >> marker >> sep >> mesh.coords_cell0d(0, id) >> sep >> mesh.coords_cell0d(1, id);

		mesh.id_cell0d.push_back(id);

		auto it = mesh.marker_cell0d.find(marker);
		if(it == mesh.marker_cell0d.end())
			mesh.marker_cell0d.insert({marker, {id}}); 
		else
			mesh.marker_cell0d[marker].push_back(id); 
	}

	return true;
}


bool Import_cell1d(PolygonalMesh& mesh)
{
	string file_name = "Cell1Ds.csv";
	list<string> lines_list;
	Import_file(file_name, lines_list);

	mesh.num_cell1d = lines_list.size();

	if(mesh.num_cell1d == 0) {
		cerr << "cell1D vuoto" << endl;
		return false;
	}

	mesh.id_cell1d.reserve(mesh.num_cell1d);

	mesh.extrema_cell1d = MatrixXi::Zero(2, mesh.num_cell1d);

	string line;
	char sep;
	unsigned int id;
	unsigned int marker;

	for(const auto& line : lines_list) {
		stringstream sstr(line);
		
		sstr >> id >> sep >> marker >> sep >> mesh.extrema_cell1d(0, id) >> sep >> mesh.extrema_cell1d(1, id);

		mesh.id_cell1d.push_back(id);

		auto it = mesh.marker_cell1d.find(marker);
		if(it == mesh.marker_cell1d.end())
			mesh.marker_cell1d.insert({marker, {id}}); 
		else
			mesh.marker_cell1d[marker].push_back(id); 
	}

	return true;
}


bool Import_cell2d(PolygonalMesh& mesh)
{
	string file_name = "Cell2Ds.csv";
	list<string> lines_list;
	Import_file(file_name, lines_list);

	mesh.num_cell2d = lines_list.size();

	if(mesh.num_cell2d == 0) {
		cerr << "cell2D vuoto" << endl;
		return false;
	}

	mesh.id_cell2d.reserve(mesh.num_cell2d);
	mesh.vertices_cell2d.resize(mesh.num_cell2d);
	mesh.edges_cell2d.resize(mesh.num_cell2d);

	string line;
	char sep;
	unsigned int id;
	unsigned int marker;
	unsigned int num_vertices;
	unsigned int num_edges;

	for(const auto& line : lines_list) {
		stringstream sstr(line);

		sstr >> id >> sep >> marker >> sep >> num_vertices >> sep;

		mesh.id_cell2d.push_back(id);

		mesh.vertices_cell2d[id].resize(num_vertices);

		for(unsigned int i = 0; i < num_vertices; i++)
			sstr >> mesh.vertices_cell2d[id][i] >> sep;

		sstr >> num_edges >> sep;

		if(num_vertices != num_edges) {
			cerr << "Errore nel poligono " << id << endl;
			return false;
		}

		mesh.edges_cell2d[id].resize(num_edges);

		for(unsigned int i = 0; i < num_edges; i++)
			sstr >> mesh.edges_cell2d[id][i] >> sep;

		auto it = mesh.marker_cell2d.find(marker);
		if(it == mesh.marker_cell2d.end())
			mesh.marker_cell2d.insert({marker, {id}});
		else
			mesh.marker_cell2d[marker].push_back(id); 
	}

	return true;
}


void print_markers(const map<unsigned int, list<unsigned int>>& markers)
{
	for(const auto& pair : markers) {
		cout << pair.first << " -> ";

		for(const auto& val : pair.second)
			cout << val << " ";

		cout << endl;
	}
}