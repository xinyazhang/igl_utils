#include <igl/readOBJ.h>
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
	std::cout.precision(17);
	for (int i = 1; i < argc; i++) {
		Eigen::MatrixXd V, TC, N;
		Eigen::MatrixXi F, FTC, FN;
		const char* ifn = argv[i];
		if (!igl::readOBJ(ifn, V, TC, N, F, FTC, FN)) {
			std::cerr << "Unable to read " << ifn << " as OBJ file" << std::endl;
			return -1;
		}
		Eigen::MatrixXd centered = V.rowwise() - V.colwise().mean();
		Eigen::MatrixXd cov = centered.adjoint() * centered;
		Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);

		std::cout<< argv[i] <<" PCA Eigen Values: " << eig.eigenvalues().transpose() << std::endl;
		std::cout<< argv[i] <<" PCA Eigen Vectors (in column):\n" << eig.eigenvectors() << std::endl;
	}
	return 0;
}
