
/*
 *
 * Provides the functions related to UNIX operating system.
 *
 * Author:  Antoine Allard
 * WWW:     antoineallard.info
 * Date:    November 2017
 *
 * To compile (from the root repository of the project):
 *   g++ -O3 -std=c++11 src/generatingS1_unix.cpp -o generatingS1_unix.out
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

#include <fstream>
#include <iostream>
#include <numeric>
#include <string>

#include "pgl/directedgraph.h"
#include "pgl/inputoutput/inputoutput.h"
#include "pgl/metrics/directed.h"

int main(int argc , char *argv[])
{
  std::string networkFilename = argv[1];

  std::string networkName = argv[2];

  std::string outFilename = argv[3];

  PGL::DirectedGraph theGraph;
  bool allow_multiedges = false;
  bool allow_selfloops = false;
  auto Name2Num = PGL::loadGraphFromEdgelist(networkFilename, theGraph, allow_multiedges, allow_selfloops);

  int nb_vertices = theGraph.getSize();
  int nb_edges = theGraph.getEdgeNumber();
  double density = ( (double) nb_edges/nb_vertices) / (nb_vertices - 1);

  if(argc == 6) {
    // std::cout << "ignored" << std::endl;
    int nb_vertices_upper_bound = std::stoi(argv[4]);
    if(nb_vertices > nb_vertices_upper_bound)
      return 0;

    int nb_edges_upper_bound = std::stoi(argv[5]);
    if(nb_edges > nb_edges_upper_bound)
        return 0;
  }

  std::fstream outFile(outFilename, std::ios::app);

  outFile << std::setw(30) << networkName << " ";
  outFile << std::setw(20) << nb_vertices << " ";
  outFile << std::setw(20) << nb_edges << " ";
  outFile << std::setw(20) << density << " ";

  auto in_degree = theGraph.getInDegrees();
  auto outdegree = theGraph.getOutDegrees();
  double average_degree = std::accumulate(outdegree.begin(), outdegree.end(), 0.0) / nb_vertices;

  int nb_vertices_undir_degree_gt_zero = 0;
  int nb_vertices_undir_degree_gt_one = 0;
  for(int v(0), kout, k_in; v<nb_vertices; ++v) {
    kout = in_degree[v];
    k_in = outdegree[v];
    if((k_in + kout) > 0)
      ++nb_vertices_undir_degree_gt_zero;
    if((k_in + kout) > 1)
      ++nb_vertices_undir_degree_gt_one;
  }

  outFile << std::setw(20) << average_degree << " ";
  outFile << std::setw(20) << nb_vertices_undir_degree_gt_zero << " ";
  outFile << std::setw(20) << nb_vertices_undir_degree_gt_one << " ";

  auto reciprocalDegrees = PGL::getReciprocalDegrees(theGraph);
  int nb_reciprocal_edges = std::accumulate(reciprocalDegrees.begin(), reciprocalDegrees.end(), 0.0);
  double reciprocity_ratio = (double) nb_reciprocal_edges / nb_edges;
  double reciprocity_stat = 1;
  if(density < 0.99999999999999)
    reciprocity_stat = (reciprocity_ratio - density) / (1 - density);

  outFile << std::setw(20) << nb_reciprocal_edges << " ";
  outFile << std::setw(20) << reciprocity_ratio << " ";
  outFile << std::setw(20) << reciprocity_stat << " ";

  auto inEdges = theGraph.getInEdgesOfVertices();
  auto triangles = PGL::findAllDirectedTriangles(theGraph, inEdges);
  auto triangleSpectrum = PGL::getTriangleSpectrum(theGraph, triangles);
  auto localUndirectedCoefficients = PGL::getUndirectedLocalClusteringCoefficients(theGraph, triangles, inEdges);
  double average_undir_clustering = std::accumulate(localUndirectedCoefficients.begin(), localUndirectedCoefficients.end(), 0.0) / nb_vertices_undir_degree_gt_one;
  double globalUndirectedClustCoeff = PGL::getUndirectedGlobalClusteringCoefficient(theGraph, triangles, inEdges);

  outFile << std::setw(20) << average_undir_clustering << " ";
  outFile << std::setw(20) << globalUndirectedClustCoeff << " ";
  outFile << std::setw(20) << triangles.size() << " ";
  outFile << std::setw(20) << triangleSpectrum["3cycle"] << " ";
  outFile << std::setw(20) << triangleSpectrum["3nocycle"] << " ";
  outFile << std::setw(20) << triangleSpectrum["4cycle"] << " ";
  outFile << std::setw(20) << triangleSpectrum["4outward"] << " ";
  outFile << std::setw(20) << triangleSpectrum["4inward"] << " ";
  outFile << std::setw(20) << triangleSpectrum["5cycle"] << " ";
  outFile << std::setw(20) << triangleSpectrum["6cycle"] << " ";

  outFile << std::endl;
  outFile.close();

  return 0;
}
