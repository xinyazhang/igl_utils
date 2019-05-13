#include <igl/readOBJ.h>
#include <igl/doublearea.h>
#include <iostream>
#include <string>

constexpr int kRequiredArguments = 1 + 1; // 1 Input, 1 Output
constexpr int kInputArg = 1;
constexpr int kOutputArg = 2;

void usage()
{
	std::cerr << R"xxx(Missing arguments. Usage:
objtl <Input OBJ file>
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
	Eigen::VectorXd sa;
	igl::doublearea(V, F, sa);
	std::cout<< "Surface area " << sa.sum() << std::endl;
	return 0;
}
