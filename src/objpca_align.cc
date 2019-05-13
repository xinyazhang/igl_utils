#include <igl/readOBJ.h>
#include <igl/writeOBJ.h>
#include <iostream>
#include <string>

constexpr int kRequiredArguments = 1 + 1; // 1 Input, 1 Output
constexpr int kInputArg = 1;
constexpr int kOutputArg = 2;

void usage()
{
	std::cerr << R"xxx(Missing arguments. Usage:
objpca_align <Input OBJ file> <Output OBJ file>
)xxx";
}

int main(int argc, char* argv[])
{
	if (argv[1] == "-h") {
		usage();
		return 0;
	}
	if (argc < kRequiredArguments) {
		usage();
		return -1;
	}
	std::cout.precision(17);
	Eigen::MatrixXd V, TC, N;
	Eigen::MatrixXi F, FTC, FN;
	const char* ifn = argv[kInputArg];
	if (!igl::readOBJ(ifn, V, TC, N, F, FTC, FN)) {
		std::cerr << "Unable to read " << ifn << " as OBJ file" << std::endl;
		return -1;
	}
	Eigen::MatrixXd centered = V.rowwise() - V.colwise().mean();
	Eigen::MatrixXd cov = centered.adjoint() * centered;
	Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
	Eigen::Vector3d X = eig.eigenvectors().col(0).normalized();
	Eigen::Vector3d Y = eig.eigenvectors().col(1).normalized();
	Eigen::Vector3d Z = X.cross(Y);
	Eigen::MatrixXd new_basis(3, 3);
	new_basis.col(0) = X;
	new_basis.col(1) = Y;
	new_basis.col(2) = Z;
	Eigen::MatrixXd Vprime = V * new_basis;
	const char* ofn = argv[kOutputArg];
	if (!igl::writeOBJ(ofn, Vprime, F, N, FN, TC, FTC)) {
		std::cerr << "Unable to write " << ofn << " as OBJ file" << std::endl;
		return -1;
	}
	return 0;
}
