#include <igl/readOBJ.h>
#include <igl/writeOBJ.h>
#include <igl/per_vertex_normals.h>
#include <iostream>
#include <cstdlib>
#include <string>

constexpr int kRequiredArguments = 1 + 1; // at least one input
constexpr int kInputArg = 1;
constexpr int kOutputArg = 2;

void usage()
{
	std::cerr << R"xxx(Usage:
objvn <Input/Output OBJ files> <Output OBJ file>
)xxx";
}

int main(int argc, char* argv[])
{
	if (argc < kRequiredArguments || (argc == 2 and std::string("-h") == argv[1])) {
		usage();
		return 0;
	}
	Eigen::MatrixXd V, TC, N;
	Eigen::MatrixXi F, FTC, FN;
	for (int i = 1; i < argc; i++) {
		const char* fn = argv[i];
		if (!igl::readOBJ(fn, V, TC, N, F, FTC, FN)) {
			std::cerr << "Unable to read " << fn << " as OBJ file" << std::endl;
			continue;
		}
		if (FN.rows() == F.rows()) {
			std::cout << fn << " already has vertex normal, skipping." << std::endl;
			continue;
		}
		igl::per_vertex_normals(V, F, N);
		// It is easier to understand by copying F to FN
		// Otherwise we might miss the second F in igl::writeOBJ and
		// get confused.
		FN = F;
		if (!igl::writeOBJ(fn, V, F, N, FN, TC, FTC)) {
			std::cerr << "Unable to write " << fn << " as OBJ file" << std::endl;
			return -1;
		}
	}
	return 0;
}
