#include "tetobj.h"
#include <pybind11/eigen.h>
#include <igl/copyleft/tetgen/tetrahedralize.h>
#include <igl/readOBJ.h>
#include <tuple>

namespace tet {
    
std::tuple<Eigen::MatrixXd, Eigen::MatrixXi, Eigen::MatrixXi>
tet(Eigen::Ref<Eigen::MatrixX3d> inV,
    Eigen::Ref<Eigen::MatrixX3i> inF,
    double scale)
{
    Eigen::MatrixXd mV = inV * scale;
    Eigen::MatrixXi mF = inF;
    Eigen::MatrixXd V;
    Eigen::MatrixXi T, F;
    igl::copyleft::tetgen::tetrahedralize(mV, mF, "pq1.414a0.01", V, T, F);
    return std::make_tuple(V, T, F);
}

std::tuple<Eigen::MatrixX3d, Eigen::MatrixX3i>
loadOBJ(const std::string& fn)
{
        Eigen::MatrixX3d V;
        Eigen::MatrixX3i F;
        igl::readOBJ(fn, V, F);
        return std::make_tuple(V, F);
}

void define_module(py::module& m)
{
    m.def("loadOBJ", &loadOBJ);
    m.def("tet", &tet);
}

}

