#include <igl/readOBJ.h>
#include <igl/writeOBJ.h>
#include <iostream>
#include <cstdlib>
#include <string>

constexpr int kRequiredArguments = 1 + 3 + 1; // 1 Input, 3 XYZ, 1 Output
constexpr int kInputArg = 1;
constexpr int kXYZArg = 2;
constexpr int kOutputArg = 5;

void usage()
{
	std::cerr << R"xxx(Missing arguments. Usage:
objtl <Input OBJ file> <X> <Y> <Z> <Output OBJ file>
)xxx";
}

int main(int argc, char* argv[])
{
	if (argc < kRequiredArguments) {
		usage();
		return -1;
	}
	Eigen::MatrixXd V, TC, N;
	Eigen::MatrixXi F, FTC, FN;
	const char* ifn = argv[kInputArg];
	if (!igl::readOBJ(ifn, V, TC, N, F, FTC, FN)) {
		std::cerr << "Unable to read " << ifn << " as OBJ file" << std::endl;
		return -1;
	}
	double dx = std::atof(argv[kXYZArg]);
	double dy = std::atof(argv[kXYZArg+1]);
	double dz = std::atof(argv[kXYZArg+2]);
	V.col(0).array() += dx;
	V.col(1).array() += dy;
	V.col(2).array() += dz;
	const char* ofn = argv[kOutputArg];
	if (!igl::writeOBJ(ofn, V, F, N, FN, TC, FTC)) {
		std::cerr << "Unable to write " << ofn << " as OBJ file" << std::endl;
		return -1;
	}
	return 0;
}
