#include <gudhi/Rips_complex.h>
// to construct Rips_complex from a OFF file of points
#include <gudhi/Points_off_io.h>
// to construct a simplex_tree from rips complex
#include <gudhi/Simplex_tree.h>
#include <gudhi/distance_functions.h>

#include <iostream>
#include <string>
#include <limits>  // for std::numeric_limits

void usage(int nbArgs, char * const progName) {
  std::cerr << "Error: Number of arguments (" << nbArgs << ") is not correct\n";
  std::cerr << "Usage: " << progName << " threshold\n";
  std::cerr << "       i.e.: " << progName << " 12.0\n";
  exit(-1);  // ----- >>
}

int main(int argc, char **argv) {
  if (argc != 2) usage(argc, argv[0]);

  double threshold = atof(argv[1]);

  // Type definitions
  using Point = std::vector<double>;
  using Simplex_tree = Gudhi::Simplex_tree<Gudhi::Simplex_tree_options_fast_persistence>;
  using Filtration_value = Simplex_tree::Filtration_value;
  using Rips_complex = Gudhi::rips_complex::Rips_complex<Filtration_value>;

  std::vector<Point> points;
  points.push_back({1.0, 1.0});
  points.push_back({7.0, 0.0});
  points.push_back({4.0, 6.0});
  points.push_back({9.0, 6.0});
  points.push_back({0.0, 14.0});
  points.push_back({2.0, 19.0});
  points.push_back({9.0, 17.0});
  
  // ----------------------------------------------------------------------------
  // Init of a rips complex from points
  // ----------------------------------------------------------------------------
  Rips_complex rips_complex_from_points(points, threshold, euclidean_distance<Filtration_value, Point>);

  Simplex_tree simplex;
  if (rips_complex_from_points.create_complex(simplex, 1)) {
    // ----------------------------------------------------------------------------
    // Display information about the one skeleton rips complex
    // ----------------------------------------------------------------------------
    std::cout << "Rips complex is of dimension " << simplex.dimension() <<
        " - " << simplex.num_simplices() << " simplices - " <<
        simplex.num_vertices() << " vertices." << std::endl;

    std::cout << "Iterator on rips complex simplices in the filtration order, with [filtration value]:" <<
        std::endl;
    for (auto f_simplex : simplex.filtration_simplex_range()) {
      std::cout << "   ( ";
      for (auto vertex : simplex.simplex_vertex_range(f_simplex)) {
        std::cout << vertex << " ";
      }
      std::cout << ") -> " << "[" << simplex.filtration(f_simplex) << "] ";
      std::cout << std::endl;
    }
  }
  return 0;
}
