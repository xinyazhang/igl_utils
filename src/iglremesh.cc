#include <igl/decimate.h>
#include <igl/upsample.h>
#include <igl/readOBJ.h>
#include <igl/writeOBJ.h>
#include <getopt.h>
#include <fstream>

namespace {

struct Mesh {
	Eigen::MatrixXd V;
	Eigen::MatrixXi F;
};

void usage()
{
	std::cerr << R"xxx(Usage libigl-remesh [OPTIONS] <INPUT OBJ> <OUTPUT OBJ> <Target Face Number>
Options:
	-r <upscale factor> Default: 4 
	-f                  Overwrite the output obj.
)xxx";
}

}

Mesh resample(const Mesh& M, int target_face, int upscale_factor)
{
	Mesh Mcurr = M;
	while (Mcurr.F.rows() < target_face * upscale_factor) {
		Mesh Mtmp = Mcurr;
		igl::upsample(Mtmp.V, Mtmp.F, Mcurr.V, Mcurr.F);
	}
	Mesh ret;
	Eigen::VectorXi J;

	igl::decimate(Mcurr.V, Mcurr.F, target_face, ret.V, ret.F, J);
	return ret;
}

int main(int argc, char *argv[])
{
	int opt;
	bool overwrite = false;
	int upscale_factor = 4;
	while ((opt = getopt(argc, argv, "r:fh")) != -1) {
		switch (opt) {
			case 'r':
				upscale_factor = std::atoi(optarg);
				break;
			case 'f':
				overwrite = true;
				break;
			default:
				std::cerr << "Unrecognized argument -" << char(opt) << std::endl;
				usage();
				return -1;
			case 'h':
				usage();
				return 0;
		}
	}
	if (argc < optind + 3) {
		usage();
		return -1;
	}
	std::string ifn(argv[optind]), ofn(argv[optind + 1]);
	if (!overwrite) {
		std::ifstream infile(ofn);
		if (infile.good()) {
			std::cerr << ofn << " already existed\n";
			return -1;
		}
	}
	int target_face = std::atoi(argv[optind+2]);
	Mesh MI;
	igl::readOBJ(ifn, MI.V, MI.F);
	Mesh M = resample(MI, target_face, upscale_factor);
	igl::writeOBJ(ofn, M.V, M.F);
	return 0;
}
