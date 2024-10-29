
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
#include <iomanip>


#include "pgl/directedgraph.h"
#include "pgl/inputoutput/inputoutput.h"
#include "pgl/metrics/directed.h"

int main(int argc , char *argv[])
{
  std::string networkFilename = argv[1];

  std::string degreeFilename = argv[2];
  std::fstream degreeFile(degreeFilename, std::ios::app);

  PGL::DirectedGraph theGraph;
  bool allow_multiedges = false;
  bool allow_selfloops = false;
  auto Name2Num = PGL::loadGraphFromEdgelist(networkFilename, theGraph, allow_multiedges, allow_selfloops);

  auto in_degree = theGraph.getInDegrees();
  auto outdegree = theGraph.getOutDegrees();

  for(auto el : Name2Num) {
    degreeFile  << std::setw(8) << el.first << " ";
    degreeFile  << std::setw(4) << in_degree[el.second] << " ";
    degreeFile  << std::setw(4) << outdegree[el.second] << " ";
    degreeFile  << std::endl;
  }

  degreeFile.close();

  return 0;
}
