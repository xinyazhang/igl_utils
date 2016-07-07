#include <igl/readOBJ.h>
#include <igl/writePLY.h>
#include <string>

bool has_suffix(const std::string &str, const std::string &suffix)
{
	return str.size() >= suffix.size() &&
		str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

std::string replace_suffix(const std::string &str, const std::string &suffix, const std::string &newsuffix)
{
	if (!has_suffix(str, suffix))
		return std::string();
	std::string ret(str);
	ret.replace(str.size() - suffix.size(), suffix.size(), newsuffix);
	return ret;
}

int main(int argc, char* argv[])
{
	for(int i = 1; i < argc; i++) {
		std::string inf(argv[i]);
		std::string ouf = replace_suffix(inf, ".obj", ".ply");
		if (ouf.empty())
			continue;
		Eigen::MatrixXd V;
		Eigen::MatrixXi F;
		igl::readOBJ(inf, V, F);
		igl::writePLY(ouf, V, F);
	}
	return 0;
}
