#ifndef INCLUDE_WORKAROUND_H_
#define INCLUDE_WORKAROUND_H_

#include "arguments.h"
#include "dispatch.h"
namespace mexplus{



template<>// make raw vetor of col vectors r = [cv, cv, cv,.... ];
mxArray* MxArray::from(const std::vector<Eigen::VectorXd>& data){
    //MxArray numeric_array<double>(2,2);
    int n_std = data.size();
    int n_eigen = data[0].size();
    MxArray numeric_array(MxArray::Numeric<double>(n_eigen, n_std));
    for(int i=0; i<n_eigen; i++){
        for(int j=0; j<n_std; j++){
            numeric_array.set(i, j, data[j](i));
        }
    }
    return numeric_array.release();
}

template<>// make raw vector of matrix r = [mat, mat, mat, ....];
mxArray* MxArray::from(const std::vector<Eigen::MatrixXd>& data){
    int n_std = data.size();
    int n_rows = data[0].rows();
    int n_cols = data[0].cols();
    MxArray numeric_array(MxArray::Numeric<double>(n_rows, n_cols*n_std));
    for(int i=0; i<n_std; i++){
        for(int j=0; j<n_rows; j++){
            for(int k=0; k<n_cols; k++){
                numeric_array.set(j, i*n_rows+k, data[i](j, k));
            }
        }
    }
    return numeric_array.release();
}
// 3rd order tensor [v, v, ,v , v, v]; [v, v, ,v, ..]; ....;
template<>
mxArray* MxArray::from(const std::vector<std::vector<Eigen::VectorXd>>& data){
    //MxArray numeric_array<double>(2,2);
    int N_ptcl = data.size();//ptcl
    int N_model = data[0].size();//model
    int N_dim = data[0][0].rows();
    MxArray numeric_array(MxArray::Numeric<double>(N_model*N_dim, N_ptcl));
    for(int i=0; i<N_ptcl; i++){
        for(int j=0; j<N_model; j++){
            for(int k=0; k<N_dim; k++){
                numeric_array.set(j*N_dim+k, i, data[i][j](k));
            }
        }
    }
    return numeric_array.release();
}

// 4th order tensor
template<>
mxArray* MxArray::from(const std::vector<std::vector<Eigen::MatrixXd>>& data){
    int N_ptcl = data.size();//ptcl
    int N_model = data[0].size();//model
    int N_rows = data[0][0].rows();
    int N_cols = data[0][0].cols();
    MxArray numeric_array(MxArray::Numeric<double>(N_model*N_rows, N_ptcl*N_cols));
    for(int i=0; i<N_ptcl; i++){
        for(int j=0; j<N_model; j++){
            for(int k=0; k<N_rows; k++){
                for(int l=0; l<N_cols; l++){
                    numeric_array.set(j*N_rows+k, i*N_cols+l, data[i][j](k, l));
                }
            }
        }
    }
    return numeric_array.release();
}

}


#endif
