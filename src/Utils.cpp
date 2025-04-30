#include "Utils.hpp"
#include <fstream>
#include <iostream>
#include <Eigen/Eigen>
#include <sstream>
#include <algorithm>

using namespace std;
using namespace Eigen;

namespace PolygonalLibrary {
	
bool ImportMesh(PolygonalMesh& mesh)
{
    if(!ImportCell0Ds(mesh))
        return false;

    if(!ImportCell1Ds(mesh))
        return false;

    if(!ImportCell2Ds(mesh))
        return false;

    return true;

}
// ***************************************************************************


bool ImportCell0Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell0Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;

    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell0Ds = listLines.size();

    if (mesh.NumCell0Ds == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
    mesh.Cell0DsCoordinates = MatrixXd::Zero(3, mesh.NumCell0Ds);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2d coord;

        converter >> id >> marker >> mesh.Cell0DsCoordinates(0, id) >> mesh.Cell0DsCoordinates(1, id);

        mesh.Cell0DsId.push_back(id);

        /// Memorize markers
        if(marker != 0)
        {
            const auto it = mesh.Cell0DsMarkers.find(marker);
            if(it == mesh.Cell0DsMarkers.end())
            {
                mesh.Cell0DsMarkers.insert({marker, {id}});
            }
            else
            {
                (*it).second.push_back(id);
            }
        }

    }

    return true;
}
// ***************************************************************************

bool ImportCell1Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell1Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell1Ds = listLines.size();

    if (mesh.NumCell1Ds == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.Cell1DsId.reserve(mesh.NumCell1Ds);
    mesh.Cell1DsExtrema = MatrixXi(2, mesh.NumCell1Ds);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2i vertices;

        converter >>  id >> marker >>  mesh.Cell1DsExtrema(0, id) >>  mesh.Cell1DsExtrema(1, id);
        mesh.Cell1DsId.push_back(id);

        /// Memorize markers
        if(marker != 0)
        {
            const auto it = mesh.Cell1DsMarkers.find(marker);
            if(it == mesh.Cell1DsMarkers.end())
            {
                mesh.Cell1DsMarkers.insert({marker, {id}});
            }
            else
            {
                (*it).second.push_back(id);
            }
        }
    }

    return true;
}
// ***************************************************************************

bool ImportCell2Ds(PolygonalMesh& mesh)
{
    ifstream file;
    file.open("./Cell2Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell2Ds = listLines.size();

    if (mesh.NumCell2Ds == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }

    mesh.Cell2DsId.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);

    for (const string& line : listLines)
    {
        istringstream convert(line);

        stringstream ss;
        string token;
        unsigned int id;
        unsigned int marker;
        unsigned int numvert;
        vector<unsigned int> vertices;
        unsigned int numed;
        vector<unsigned int> edges;

        getline(convert, token, ';');
        ss << token;
        ss >> id;
        ss.clear();

        getline(convert, token, ';');
        ss << token;
        ss >> marker;
        ss.clear();

        getline(convert, token, ';');
        ss << token;
        ss >> numvert;
        ss.clear();
        vertices.resize(numvert);

        //dato che il numero di vertici e lati è variabile, dobbiamo leggerli con un ciclo
        for (size_t i = 0; i < vertices.size(); ++i)
        {
            getline(convert, token, ';');
            ss << token;
            ss >> vertices[i];
            ss.clear();
        }

        getline(convert, token, ';');
        ss << token;
        ss >> numed;
        ss.clear();
        edges.resize(numed);

        //leggiamo i lati con un ciclo come i vertici
        for (size_t i = 0; i < edges.size(); ++i)
        {
            getline(convert, token, ';');
            ss << token;
            ss >> edges[i];
            ss.clear();
        }

        //aggiungiamo gli elementi ai vettori
        mesh.Cell2DsId.push_back(id);
        mesh.Cell2DsVertices.push_back(vertices);
        mesh.Cell2DsEdges.push_back(edges);

        //aggiorniamo le mappe del numero di lati e vertici
        if (mesh.NumCell2DsVertices.find(numvert) == mesh.NumCell2DsVertices.end())
        {
            mesh.NumCell2DsVertices.insert({numvert, {id}});
        }
        else
        {
            mesh.NumCell2DsVertices[numvert].push_back(id);
        }

        if (mesh.NumCell2DsEdges.find(numed) == mesh.NumCell2DsEdges.end())
        {
            mesh.NumCell2DsEdges.insert({numed, {id}});
        }
        else
        {
            mesh.NumCell2DsEdges[numed].push_back(id);
        }
    }











/*
    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        array<unsigned int, 3> vertices;
        array<unsigned int, 3> edges;

        converter >>  id;
        for(unsigned int i = 0; i < 3; i++)
            converter >> vertices[i];
        for(unsigned int i = 0; i < 3; i++)
            converter >> edges[i];

        mesh.Cell2DsId.push_back(id);
        mesh.Cell2DsVertices.push_back(vertices);
        mesh.Cell2DsEdges.push_back(edges);
    }
*/
    return true;
}


}