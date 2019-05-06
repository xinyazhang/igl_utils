#include <igl/readPLY.h>
#include <igl/writePLY.h>
#include <iostream>
#include <cstdlib>
#include <string>

constexpr int kRequiredArguments = 1 + 1; // 1 Input, 1 Output
constexpr int kInputArg = 1;
constexpr int kOutputArg = 2;

void usage()
{
	std::cerr << R"xxx(Missing arguments. Usage:
objtl <Input OBJ file> <Output OBJ file>
)xxx";
}

int main(int argc, char* argv[])
{
	if (argc < kRequiredArguments) {
		usage();
		return -1;
	}
	Eigen::MatrixXd V, N, UV;
	Eigen::MatrixXi F;
	const char* ifn = argv[kInputArg];
	if (!igl::readPLY(ifn, V, F, N, UV)) {
		std::cerr << "Unable to read " << ifn << " as PLY file" << std::endl;
		return -1;
	}
	Eigen::Vector3d means = V.colwise().mean();
	V.col(0).array() -= means(0);
	V.col(1).array() -= means(1);
	V.col(2).array() -= means(2);
	const char* ofn = argv[kOutputArg];
	if (!igl::writePLY(ofn, V, F, N, UV)) {
		std::cerr << "Unable to write " << ofn << " as PLY file" << std::endl;
		return -1;
	}
	return 0;
}
