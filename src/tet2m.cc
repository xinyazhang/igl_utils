#include <unistd.h>
#include <sstream>
#include <ctype.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>

using std::string;
using std::endl;
using std::cerr;
using std::fixed;
using std::vector;

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

void usage()
{
	cerr << "Usage: -i <tetgen file prefix> [-o output_file]" << endl;
}

void write_header(std::ostream& fout)
{
	fout << "MeshRegion[" << endl;
}

void skip_spaces_and_comments(std::istream& fin)
{
	char c;
	while (true) {
		do {
			c = fin.get();
		} while (isspace(c));
		if (c == '#')
			fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		else {
			fin.putback(c);
			break;
		}
	}
}

template<typename T>
T read(std::istream& fin)
{
	T ret;
	skip_spaces_and_comments(fin);
	fin >> ret;
	return ret;
}

struct node {
	int idx;
	double x, y, z;
};

std::istream& operator>>(std::istream& fin, node& n)
{
	skip_spaces_and_comments(fin);
	fin >> n.idx >> n.x >> n.y >> n.z;
	return fin;
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

std::ostream& operator<<(std::ostream& fout, const node& n)
{
	fout << "{" << wolfnumber(n.x) << ", " << wolfnumber(n.y) << ", " << wolfnumber(n.z) << "}" ;
	//cerr << n.x << endl;
	return fout;
}

int translate_vertices(std::ostream& fout, std::istream& fin)
{
	int npoint = read<int>(fin);
	int ndim = read<int>(fin);
	int nattr = read<int>(fin);
	int nbm = read<int>(fin);
	cerr << npoint << ' ' << ndim << ' ' << nattr << ' ' << nbm << endl;

	vector<node> nodes(npoint);
	// The spec doesn't guarntee the nodes must be in-order.
	// So we have to read them all and sort.
	for(int i = 0; i < npoint; i++) {
		nodes[i] = read<node>(fin);
		// Drop attributes and boundary markers.
		for(int j = 0; j < nattr + nbm; j++)
			(void)read<string>(fin);
	}
	std::sort(nodes.begin(), nodes.end(), [](const node& lhs, const node& rhs) { return lhs.idx < rhs.idx; });
	if (nodes.empty())
		return -1;
	
	fout << "{";
	fout << nodes[0];
	for(size_t i = 1; i < nodes.size(); i++) {
		fout << "," << endl << nodes[i];
	}
	fout << endl << "}" << endl;
	return nodes.front().idx;
}

void translate_tetrahedron(std::ostream& fout, std::istream& fin, int base)
{
	int ntetra = read<int>(fin);
	int nnode = read<int>(fin);
	int nattr = read<int>(fin);

	fout << "{Tetrahedron[{";
	for(int i = 0; i < ntetra; i++) {
		if (i > 0)
			fout << ", " << endl;
		(void)read<int>(fin);
		fout << "{";
		for(int j = 0; j < 4; j++) {
			if (j > 0)
				fout << ", ";
			int id = read<int>(fin);
			fout << id + (1 - base); // rebase
		}
		fout << "}";
	}
	fout << "}]}";
}

void write_footer(std::ostream& fout)
{
	fout << "]" << endl;
}

int main(int argc, char* argv[])
{
	int opt;
	string iprefix, ofn;
	while ((opt = getopt(argc, argv, "i:o:")) != -1) {
		switch (opt) {
			case 'i': 
				iprefix = optarg;
				break;
			case 'o':
				ofn = optarg;
				break;
			default:
				std::cerr << "Unrecognized option: " << optarg << endl;
				usage();
				return -1;
		}
	}
	if (iprefix.empty()) {
		std::cerr << "Missing input file" << endl;
		usage();
		return -1;
	}
	if (ofn.empty()) {
		ofn = iprefix + ".m";
	}
	std::ifstream nodef(iprefix+".node"), elef(iprefix+".ele");
	if (!nodef.is_open()) {
		std::cerr << "Cannot open " << iprefix+".node" << " for read" << endl;
		return -2;
	}
	if (!elef.is_open()) {
		std::cerr << "Cannot open " << iprefix+".ele" << " for read" << endl;
		return -2;
	}
	std::ofstream mf(ofn);
	if (!mf.is_open()) {
		std::cerr << "Cannot open " << ofn << " for write" << endl;
		return -3;
	}
	// Setup the precision
	mf.precision(std::numeric_limits<double>::max_digits10);

	write_header(mf);
	auto base = translate_vertices(mf, nodef);
	mf << ", " << endl;
	translate_tetrahedron(mf, elef, base);
	write_footer(mf);
	return 0;
}
