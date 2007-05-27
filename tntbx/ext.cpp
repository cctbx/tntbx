#include <scitbx/array_family/boost_python/flex_fwd.h>
#include <boost/python.hpp>

#include <tntbx/generalized_inverse.h>

BOOST_PYTHON_MODULE(tntbx_ext)
{
  using namespace boost::python;
  def("generalized_inverse", tntbx::generalized_inverse, (
    arg_("square_matrix")));
}
