#include <scitbx/array_family/boost_python/flex_fwd.h>
#include <boost/python.hpp>

//#include <scitbx/mat_ref.h>
//#include <scitbx/sym_mat3.h>

#include <tnt.h>
#include <jama_svd.h>

namespace tnt {
  namespace {

    namespace af = scitbx::af;

    // generalized_inverse wrapper for JAMA SVD
    af::versa<double, af::c_grid<2> > 
    generalized_inverse(
      af::const_ref<double, af::c_grid<2> > const& square_matrix
      )
    {
      unsigned nrows = square_matrix.accessor()[0];
      unsigned ncols = square_matrix.accessor()[1];

      SCITBX_ASSERT (nrows == ncols);
 
      af::versa<double, af::c_grid<2> > inverse(square_matrix.accessor());

      // put flex array into TNT Array2D
      TNT::Array2D<double> a(nrows, nrows);
      for(int i=0;i<nrows;i++)
	{
	  for(int j=0;j<nrows;j++)
	    {
	      a[i][j] = square_matrix(i,j);
	    }
	}
      JAMA::SVD<double> tnt_svd(a);
      TNT::Array2D<double> tnt_inverse(nrows, nrows), 
                           svd_u(nrows, nrows),
                           svd_s(nrows, nrows),
	                   svd_v(nrows, nrows);
      tnt_svd.getU(svd_u);
      tnt_svd.getS(svd_s);
      tnt_svd.getV(svd_v);
      for(int i=0;i<nrows;i++)
	{
	  for(int j=0;j<nrows;j++)
	    {
	      printf("u %d %d %f",i,j,svd_u[i][j]);
	      printf("s %d %d %f",i,j,svd_s[i][j]);
	      printf("v %d %d %f",i,j,svd_v[i][j]);
	    }
	}
	  //tnt_inverse = 

      // put tnt inverse into flex array
      for(int i=0;i<nrows;i++)
	{
	  for(int j=0;j<nrows;j++)
	    {
	      inverse(i,j) = tnt_inverse[i][j];
	    }
	}
      return inverse;
    }
    // generalized_inverse

  }
} // namespace tnt::<anon>

BOOST_PYTHON_MODULE(tntbx_eigensystem_ext)
{
  using namespace tnt;
  using namespace boost::python;
  def("generalized_inverse",generalized_inverse,(
    arg_("square_matrix")
    )
      );
}
