#include <igl/readOBJ.h>
#include <igl/writeOBJ.h>
#include <iostream>
#include <cstdlib>
#include <string>

constexpr int kRequiredArguments = 3 + 1 + 1; // 1 Input, 1 Output
constexpr int kXArg = 1;
constexpr int kYArg = 2;
constexpr int kZArg = 3;
constexpr int kInputArg = 4;
constexpr int kOutputArg = 5;

void usage()
{
	std::cerr << R"xxx(Usage:
objscale <x> <y> <z> <Input OBJ file> <Output OBJ file>
)xxx";
}

int main(int argc, char* argv[])
{
	if (argc < kRequiredArguments) {
		usage();
		return -1;
	}
	double x = std::atof(argv[kXArg]);
	double y = std::atof(argv[kYArg]);
	double z = std::atof(argv[kZArg]);
	Eigen::MatrixXd V, TC, N;
	Eigen::MatrixXi F, FTC, FN;
	const char* ifn = argv[kInputArg];
	if (!igl::readOBJ(ifn, V, TC, N, F, FTC, FN)) {
		std::cerr << "Unable to read " << ifn << " as OBJ file" << std::endl;
		return -1;
	}
	V.col(0) *= x;
	V.col(1) *= y;
	V.col(2) *= z;
	const char* ofn = argv[kOutputArg];
	if (!igl::writeOBJ(ofn, V, F, N, FN, TC, FTC)) {
		std::cerr << "Unable to write " << ofn << " as OBJ file" << std::endl;
		return -1;
	}
	return 0;
}
