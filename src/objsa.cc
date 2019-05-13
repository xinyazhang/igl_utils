#include <igl/readOBJ.h>
#include <igl/doublearea.h>
#include <iostream>
#include <string>

constexpr int kRequiredArguments = 1;
constexpr int kInputArg = 1;
constexpr int kOutputArg = 2;

void usage()
{
	std::cerr << R"xxx(Missing arguments. Usage:
objsa <Input OBJ file>
)xxx";
}

int main(int argc, char* argv[])
{
	if (argv[1] == "-h") {
		usage();
		return 0;
	}
	for (int i = 1; i < argc; i++) {
		Eigen::MatrixXd V, TC, N;
		Eigen::MatrixXi F, FTC, FN;
		const char* ifn = argv[i];
		if (!igl::readOBJ(ifn, V, TC, N, F, FTC, FN)) {
			std::cerr << "Unable to read " << ifn << " as OBJ file" << std::endl;
			return -1;
		}
		Eigen::VectorXd sa;
		igl::doublearea(V, F, sa);
		std::cout<< argv[i] <<" surface area " << sa.sum() << std::endl;
	}
	return 0;
}
