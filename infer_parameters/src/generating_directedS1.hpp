/*
 *
 * This class provides the functions to generate a graph in the S1 space.
 *
 * Compilation requires the c++11 standard to use #include <random>.
 *   Example: g++ -O3 -std=c++11 my_code.cpp -o my_program
 *
 * Author:  Antoine Allard
 * WWW:     antoineallard.info
 * Date:    November 2017
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

#ifndef GENERATINGS1_HPP_INCLUDED
#define GENERATINGS1_HPP_INCLUDED

// Standard Template Library
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>



class generating_directedS1_t
{
  // Flags controlling options.
  public:
    bool CUSTOM_OUTPUT_ROOTNAME = false;
    bool NAME_PROVIDED = false;
    bool NATIVE_INPUT_FILE = false;
    bool THETA_PROVIDED = false;
    bool SAVE_COORDINATES = false;
  // Global parameters.
  public:
    // Random number generator seed.
    int SEED;
    // Parameter beta (clustering).
    double BETA = -10;
    // Parameter mu (average degree).
    double MU = -10;
    // Parameter nu (reciprocity).
    double NU = -10;
    // Rootname for the output files;
    std::string OUTPUT_ROOTNAME = "default_output_rootname";
    // Input hidden variables filename.
    std::string HIDDEN_VARIABLES_FILENAME;
  // General internal objects.
  private:
    // pi
    const double PI = 3.141592653589793238462643383279502884197;
    const double NUMERICAL_ZERO = 1e-5;
    // Random number generator
    std::uniform_real_distribution<double> uniform_01;
    // Mapping the numerical ID of vertices to their name.
    std::vector<std::string> Num2Name;
  public:
    std::mt19937 engine;
  // Objects related to the graph ensemble.
  private:
    // Number of vertices.
    int nb_vertices;
    // Hidden variables of the vertices.
    std::vector<double> in_Kappa;
    std::vector<double> outKappa;
    // Positions of the vertices.
    std::vector<double> theta;
  // Public functions to generate the graphs.
  public:
    // Constructor (empty).
    generating_directedS1_t() { SEED = std::time(NULL); engine.seed(SEED); };
    // Loads the values of the hidden variables (i.e., kappa and theta).
    void load_hidden_variables();
    // Generates an edgelist and writes it into a file.
    void generate_edgelist(int width = 15);
  // Private functions linked to the generation of a random edgelist.
  private:
    // Saves the values of the hidden variables (i.e., kappa and theta).
    void saveCoordinates(int width);
    // Gets and format current date/time.
    std::string get_time();
};





// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void generating_directedS1_t::generate_edgelist(int width)
{
  if(BETA == -10) {
    std::cerr << "ERROR: The value of parameter beta must be provided." << std::endl;
    std::terminate();
  }

  if(MU == -10) {
    double average_kappa = 0;
    for(int v(0); v<nb_vertices; ++v)
      average_kappa += (in_Kappa[v] + outKappa[v]) / (2. * nb_vertices);
    MU = BETA * std::sin(PI / BETA) / (2.0 * PI * average_kappa);
  }

  if(NU == -10) {
    std::cerr << "ERROR: The value of parameter nu must be provided." << std::endl;
    std::terminate();
  }

  if(theta.size() != nb_vertices) {
    theta.clear();
    theta.resize(nb_vertices);
    for(int v(0); v<nb_vertices; ++v)
      theta[v] = 2 * PI * uniform_01(engine);
  }

  // Opens the stream and terminates if the operation did not succeed.
  std::string edgelist_filename = OUTPUT_ROOTNAME + "_edgelist.txt";
  std::fstream edgelist_file(edgelist_filename.c_str(), std::fstream::out);
  if( !edgelist_file.is_open() )
  {
    std::cerr << "ERROR: Could not open file: " << edgelist_filename << "." << std::endl;
    std::terminate();
  }
  // Writes the header.
  edgelist_file << "# =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" << std::endl;
  edgelist_file << "# Generated on:           " << get_time()                << std::endl;
  edgelist_file << "# Hidden variables file:  " << HIDDEN_VARIABLES_FILENAME << std::endl;
  edgelist_file << "# Seed:                   " << SEED                      << std::endl;
  edgelist_file << "#"                                                       << std::endl;
  edgelist_file << "# Parameters"                                            << std::endl;
  edgelist_file << "#   - N:                  " << nb_vertices               << std::endl;
  edgelist_file << "#   - beta:               " << BETA                      << std::endl;
  edgelist_file << "#   - mu:                 " << MU                        << std::endl;
  edgelist_file << "#   - nu:                 " << NU                        << std::endl;
  edgelist_file << "#   - R:                  " << nb_vertices / (2 * PI)    << std::endl;
  edgelist_file << "# =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" << std::endl;
  edgelist_file << "#";
  edgelist_file << std::setw(width - 1) << "Vertex1" << " ";
  edgelist_file << std::setw(width)     << "Vertex2" << " ";
  edgelist_file << std::endl;
  // Generates the edgelist.
  double kout1, k_in1, theta1, dtheta, p11, p12, p21, r, koutkin;
  double prefactor = nb_vertices / (2 * PI * MU);
  for(int v1(0); v1<nb_vertices; ++v1)
  {
    kout1 = outKappa[v1];
    k_in1 = in_Kappa[v1];
    theta1 = theta[v1];
    for(int v2(v1 + 1); v2<nb_vertices; ++v2)
    {
      dtheta = PI - std::fabs(PI - std::fabs(theta1 - theta[v2]));
      koutkin = kout1 * in_Kappa[v2];
      if(koutkin > NUMERICAL_ZERO)
        p12 = 1 / (1 + (std::pow((prefactor * dtheta) / (koutkin), BETA)));
      else
        p12 = 0;
      koutkin = outKappa[v2] * k_in1;
      if(koutkin > NUMERICAL_ZERO)
        p21 = 1 / (1 + (std::pow((prefactor * dtheta) / (koutkin), BETA)));
      else
        p21 = 0;

      if(NU > 0) {
        if(p12 < p21)
          p11 = ( (1 - NU) * p21 + NU ) * p12;
        else
          p11 = ( (1 - NU) * p12 + NU ) * p21;
      }
      else {
        if(p12 + p21 < 1)
          p11 = (1 + NU) * p12 * p21;
        else
          p11 = (1 + NU) * p12 * p21 + NU * (1 - p12 - p21);
      }

      r = uniform_01(engine);
      if(r < p11) {
        edgelist_file << std::setw(width) << Num2Name[v1] << " ";
        edgelist_file << std::setw(width) << Num2Name[v2] << " ";
        edgelist_file << std::endl;
        edgelist_file << std::setw(width) << Num2Name[v2] << " ";
        edgelist_file << std::setw(width) << Num2Name[v1] << " ";
        edgelist_file << std::endl;
      }
      else if(r < p21) { // = p11 + p01
        edgelist_file << std::setw(width) << Num2Name[v2] << " ";
        edgelist_file << std::setw(width) << Num2Name[v1] << " ";
        edgelist_file << std::endl;
      }
      else if(r < (p21 + p12 - p11)) { // = p11 + p01 + p10
        edgelist_file << std::setw(width) << Num2Name[v1] << " ";
        edgelist_file << std::setw(width) << Num2Name[v2] << " ";
        edgelist_file << std::endl;
      }
    }
  }

  edgelist_file.close();

  if(SAVE_COORDINATES)
    saveCoordinates(width);
}


// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void generating_directedS1_t::load_hidden_variables()
{
  // Stream object.
  std::stringstream one_line;
  // String objects.
  std::string full_line, name1_str, name2_str, name3_str;
  // Resets the number of vertices.
  nb_vertices = 0;
  // Resets the container.
  in_Kappa.clear();
  outKappa.clear();
  // Opens the stream and terminates if the operation did not succeed.
  std::fstream hidden_variables_file(HIDDEN_VARIABLES_FILENAME.c_str(), std::fstream::in);
  if( !hidden_variables_file.is_open() )
  {
    std::cerr << "Could not open file: " << HIDDEN_VARIABLES_FILENAME << "." << std::endl;
    std::terminate();
  }
  // Extracts the beta and mu parameters if the file is a native.
  if(NATIVE_INPUT_FILE)
  {
    // Ignores the first 9 lines of the file.
    for(int l(0); l<6; ++l)
    {
      std::getline(hidden_variables_file, full_line);
    }
    // Gets the 7th lines containing the value of beta.
    std::getline(hidden_variables_file, full_line);
    hidden_variables_file >> std::ws;
    one_line.str(full_line);
    one_line >> std::ws;
    one_line >> name1_str >> std::ws;
    one_line >> name1_str >> std::ws;
    one_line >> name1_str >> std::ws;
    BETA = std::stod(name1_str);
    one_line.clear();
    // Gets the 8th lines containing the value of mu.
    std::getline(hidden_variables_file, full_line);
    hidden_variables_file >> std::ws;
    one_line.str(full_line);
    one_line >> std::ws >> name1_str >> std::ws >> name1_str >> std::ws >> name1_str >> std::ws;
    MU = std::stod(name1_str);
    one_line.clear();
    // Gets the 9th lines containing the value of nu.
    std::getline(hidden_variables_file, full_line);
    hidden_variables_file >> std::ws;
    one_line.str(full_line);
    one_line >> std::ws;
    one_line >> name1_str >> std::ws;
    one_line >> name1_str >> std::ws;
    one_line >> name1_str >> std::ws;
    NU = std::stod(name1_str);
    one_line.clear();
  }
  // Reads the hidden variables file line by line.
  while( !hidden_variables_file.eof() )
  {
    // Reads a line of the file.
    std::getline(hidden_variables_file, full_line);
    hidden_variables_file >> std::ws;
    one_line.str(full_line);
    one_line >> std::ws;
    one_line >> name1_str >> std::ws;
    // Skips lines of comment.
    if(name1_str == "#")
    {
      one_line.clear();
      continue;
    }
    // Adds the new vertex and its hidden variable(s).
    if(NAME_PROVIDED)
    {
      Num2Name.push_back(name1_str);
      one_line >> name2_str >> std::ws;
      in_Kappa.push_back(std::stod(name2_str));
      one_line >> name2_str >> std::ws;
      outKappa.push_back(std::stod(name2_str));
    }
    else
    {
      Num2Name.push_back("v" + std::to_string(nb_vertices));
      in_Kappa.push_back(std::stod(name1_str));
      one_line >> name2_str >> std::ws;
      outKappa.push_back(std::stod(name2_str));
    }
    if(THETA_PROVIDED)
    {
      one_line >> name3_str >> std::ws;
      theta.push_back(std::stod(name3_str));
    }
    ++nb_vertices;
    one_line.clear();
  }
  // Closes the stream.
  hidden_variables_file.close();
}


// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
void generating_directedS1_t::saveCoordinates(int width)
{
  std::string coord_filename = OUTPUT_ROOTNAME + "_coord.txt";
  std::fstream coord_file(coord_filename.c_str(), std::fstream::out);
  if( !coord_file.is_open() ) {
    std::cerr << "Could not open file: " << coord_filename << "." << std::endl;
    std::terminate();
  }

  coord_file << "# =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" << std::endl;
  coord_file << "# Generated on: " << get_time()             << std::endl;
  coord_file << "#"                                          << std::endl;
  coord_file << "# Parameters"                               << std::endl;
  coord_file << "#   - N:        " << nb_vertices            << std::endl;
  coord_file << "#   - beta:     " << BETA                   << std::endl;
  coord_file << "#   - mu:       " << MU                     << std::endl;
  coord_file << "#   - nu:       " << NU                     << std::endl;
  coord_file << "#   - R:        " << nb_vertices / (2 * PI) << std::endl;
  coord_file << "# =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" << std::endl;

  coord_file << "#";
  coord_file << std::setw(width - 1) << "vertex"    << " ";
  coord_file << std::setw(width)     << "inKappa"   << " ";
  coord_file << std::setw(width)     << "outKappa"  << " ";
  coord_file << std::setw(width)     << "theta"     << " ";
  coord_file << std::endl;

  for(int v(0); v<nb_vertices; ++v)  {
    coord_file << std::setw(width) << Num2Name[v]   << " ";
    coord_file << std::setw(width) << in_Kappa[v]   << " ";
    coord_file << std::setw(width) << outKappa[v]   << " ";
    coord_file << std::setw(width) << theta[v]      << " ";
    coord_file << std::endl;
  }

  coord_file.close();
}


// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
std::string generating_directedS1_t::get_time()
{
  time_t theTime = time(NULL);
  struct tm *aTime = gmtime(&theTime);
  int year    = aTime->tm_year + 1900;
  int month   = aTime->tm_mon + 1;
  int day     = aTime->tm_mday;
  int hours   = aTime->tm_hour;
  int minutes = aTime->tm_min;

  std::string the_time = std::to_string(year) + "/";
  if(month < 10)
    the_time += "0";
  the_time += std::to_string(month) + "/";
  if(day < 10)
    the_time += "0";
  the_time += std::to_string(day) + " " + std::to_string(hours) + ":";
  if(minutes < 10)
    the_time += "0";
  the_time += std::to_string(minutes) + " UTC";

  return the_time;
}



#endif // GENERATINGS1_HPP_INCLUDED
