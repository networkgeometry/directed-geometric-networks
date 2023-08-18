
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

#include <algorithm>
#include <fstream>
#include <vector>

#include "pgl/directedgraph.h"
#include "pgl/inputoutput/inputoutput.h"
#include "pgl/metrics/directed.h"

int main(int argc , char *argv[])
{
  std::string networkFilename = argv[1];

  std::string degreeDistFilename = argv[2];
  std::fstream degreeDistFile(degreeDistFilename, std::ios::app);

  PGL::DirectedGraph theGraph;
  bool allow_multiedges = false;
  bool allow_selfloops = false;
  auto Name2Num = PGL::loadGraphFromEdgelist(networkFilename, theGraph, allow_multiedges, allow_selfloops);

  double nb_vertices = theGraph.getSize();

  auto in_degree = theGraph.getInDegrees();
  auto outdegree = theGraph.getOutDegrees();

  size_t max_d_in = *max_element(in_degree.begin(), in_degree.end());
  size_t max_dout = *max_element(outdegree.begin(), outdegree.end());
  size_t max_d = std::max(max_d_in, max_dout) + 100;

  auto in_degreehist = PGL::getInDegreeHistogram(theGraph, in_degree);
  auto outdegreehist = PGL::getOutDegreeHistogram(theGraph);

  std::vector<double> inDistDeg(max_d);
  std::vector<double> outDistDeg(max_d);

  size_t idx_start = 0;
  size_t idx_stop;
  double value = 1;

  idx_start = 0;
  value = 1;
  for(auto el : in_degreehist) {
    idx_stop = el.first;
    for(; idx_start <= idx_stop; ++idx_start) {
      inDistDeg[idx_start] = value;
    }
    value -= (double) el.second / nb_vertices;
  }

  idx_start = 0;
  value = 1;
  for(auto el : outdegreehist) {
    idx_stop = el.first;
    for(; idx_start <= idx_stop; ++idx_start) {
      outDistDeg[idx_start] = value;
    }
    value -= (double) el.second / nb_vertices;
  }

  for(size_t i(0); i<max_d; ++i) {
    degreeDistFile  << std::setw(8) << i << " ";
    degreeDistFile  << std::setw(12) << inDistDeg[i]  << " ";
    degreeDistFile  << std::setw(12) << outDistDeg[i] << " ";
    degreeDistFile  << std::endl;
  }

  degreeDistFile.close();

  return 0;
}
