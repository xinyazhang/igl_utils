#include <igl/readOBJ.h>
#include <string>
#include <fstream>

using std::string;
using std::endl;

bool has_suffix(const string &str, const string &suffix)
{
	return str.size() >= suffix.size() &&
		str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

string replace_suffix(const string &str, const string &suffix, const string &newsuffix)
{
	if (!has_suffix(str, suffix))
		return string();
	string ret(str);
	ret.replace(str.size() - suffix.size(), suffix.size(), newsuffix);
	return ret;
}

string wolfnumber(double n)
{
	std::ostringstream out;
	out.precision(std::numeric_limits<double>::max_digits10);
	out << n;
	string ret = out.str();
	size_t pos = ret.find("e");
	if (pos != string::npos) {
		ret.replace(pos, 1, "*^");
	}
	return ret;
}

void write_wolfram(std::ostream& fout,
		const Eigen::MatrixXd& V,
		const Eigen::MatrixXi& F)
{
	fout << "BoundaryMeshRegion[" << endl;
	fout << "{" ;
	for(size_t i = 0; i < V.rows(); i++) {
		if (i > 0)
			fout << ", " << endl;
		fout << "{"
			<< wolfnumber(V(i,0)) << ", "
			<< wolfnumber(V(i,1)) << ", "
			<< wolfnumber(V(i,2)) << "}";
	}
	fout << "}, Polygon[{" << endl;
	for(size_t i = 0; i < F.rows(); i++) {
		if (i > 0)
			fout << ", " << endl;
		fout << "{"
			<< F(i,0) + 1 << ", "
			<< F(i,1) + 1 << ", "
			<< F(i,2) + 1 << "}";
	}
	fout << "}]" << endl;
	fout << "]" << endl;
}

int main(int argc, char* argv[])
{
	for(int i = 1; i < argc; i++) {
		string inf(argv[i]);
		string ouf = replace_suffix(inf, ".obj", ".m");
		if (ouf.empty())
			continue;
		Eigen::MatrixXd V;
		Eigen::MatrixXi F;
		igl::readOBJ(inf, V, F);
		std::ofstream fout(ouf);
		write_wolfram(fout, V, F);
	}
	return 0;
}
