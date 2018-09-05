#define print(a) std::cout<<a<<std::endl;
#define printr(a) for(auto it!=a.begin(); it!=a.end(); ++it){cout<a<endl;};
#include <mexplus.h>
#include <iostream>
#include <Eigen/Core>

using namespace std;
using namespace mexplus;
using namespace Eigen;
template<class T> using matrix = std::vector<std::vector<T>>;


namespace mexplus{
    // A nasty workaround
    /*
    template<>
    MatrixXd InputArguments::get(size_t index) const{
        MxArray raw_data(this->get(index));
        int Nr = raw_data.rows();
        int Nc = raw_data.cols();
        auto data = this->get<std::vector<double>>(index);
        MatrixXd Mdata = Eigen::Map<MatrixXd>(&data[0], Nr, Nc);
        return Mdata;
    }
    */

    /*
    //template<>// std::vector(nz, 1) of eigen::matrix(nx, ny)
    vector<MatrixXd> InputArguments::get_vecmat(size_t index,
            int nx, int ny, int nz) const{
        MxArray raw_data(this->get(index));
        int Nr = raw_data.rows();
        int Nc = raw_data.cols();
        auto tmp = this->get<std::vector<double>>(index);
        auto mat_data = Eigen::Map<MatrixXd>(&tmp[0], Nr, Nc);

        vector<MatrixXd> data(nz);
        for(auto it=data.begin(); it!=data.end(); ++it){
            int idx = it - data.begin();
            *it = mat_data.block<nx, ny>(nx*idx, 0);
        }
        return data;
    }
    */
}



// Hypothetical database class to be MEXed. This example is a proxy to C++ map.
class Monster {
public:
  // Database constructor. This is a stub.
  Monster(const string& filename):life(100), PTM(MatrixXd::Zero(2,2)){};

  // Database destructor.
  virtual ~Monster() {}
  // Query a record.
  void attack(double power){
      life -= power;
      cout<<"your remaining life is "<< life <<endl;
  }
  void get_life(double& life_){
      life_ = life;
  }

  void set_matrix(Eigen::MatrixXd PTM_){
      PTM = PTM_;
  }

  void set_vecmat(vector<MatrixXd> P__inpt){
      P__ = P__inpt;
      for(auto i=P__.begin(); i!=P__.end(); i++){
          print(*i);
      }
  }

  void set_matmat(matrix<MatrixXd> fuck_){
      fuck = fuck_;
      for(auto i=fuck.begin(); i!=fuck.end(); i++){
          for(auto j=i->begin(); j!=i->end(); j++){
              print(*j);
              cout<<endl;
          }
      }
  }

private:
  double life;
  MatrixXd PTM;
  vector<MatrixXd> P__;
  matrix<MatrixXd> fuck;

};

// Instance manager for Database.
template class mexplus::Session<Monster>;
namespace {

// Defines MEX API for new.
MEX_DEFINE(new) (int nlhs, mxArray* plhs[],
                 int nrhs, const mxArray* prhs[]) {
  InputArguments input(nrhs, prhs, 1);
  OutputArguments output(nlhs, plhs, 1);
  output.set(0, Session<Monster>::create(new Monster(input.get<string>(0))));
}

// Defines MEX API for delete.
MEX_DEFINE(delete) (int nlhs, mxArray* plhs[],
                    int nrhs, const mxArray* prhs[]) {
  InputArguments input(nrhs, prhs, 1);
  OutputArguments output(nlhs, plhs, 0);
  Session<Monster>::destroy(input.get(0));
}

// Defines MEX API for query (const method).
MEX_DEFINE(attack) (int nlhs, mxArray* plhs[],
                   int nrhs, const mxArray* prhs[]) {
  InputArguments input(nrhs, prhs, 2);
  OutputArguments output(nlhs, plhs, 0);
  Monster* monster = Session<Monster>::get(input.get(0));
  monster->attack(input.get<double>(1));
}

MEX_DEFINE(get_life) (int nlhs, mxArray* plhs[],
                   int nrhs, const mxArray* prhs[]) {
  InputArguments input(nrhs, prhs, 1);
  OutputArguments output(nlhs, plhs, 1);
  Monster* monster = Session<Monster>::get(input.get(0));
  double life_;
  monster->get_life(life_);
  output.set(0, life_);
}

MEX_DEFINE(set_matrix) (int nlhs, mxArray* plhs[],
                   int nrhs, const mxArray* prhs[]) {
  InputArguments input(nrhs, prhs, 2);
  OutputArguments output(nlhs, plhs, 1);
  Monster* monster = Session<Monster>::get(input.get(0));
  auto inp_ = input.get(1);
  auto inp = input.get<std::vector<double>>(1);
  auto test = input.get<Eigen::MatrixXd>(1);
}

MEX_DEFINE(set_vecmat) (int nlhs, mxArray* plhs[],
                   int nrhs, const mxArray* prhs[]) {
  InputArguments input(nrhs, prhs, 2);
  OutputArguments output(nlhs, plhs, 1);
  Monster* monster = Session<Monster>::get(input.get(0));
  auto a = input.get<vector<MatrixXd>>(1, 2, 1);
  monster->set_vecmat(a);
}

MEX_DEFINE(set_matmat) (int nlhs, mxArray* plhs[],
                   int nrhs, const mxArray* prhs[]) {
  InputArguments input(nrhs, prhs, 2);
  OutputArguments output(nlhs, plhs, 1);
  Monster* monster = Session<Monster>::get(input.get(0));
  auto fuck = input.get<matrix<MatrixXd>>(1, 1, 2);
  monster->set_matmat(fuck);
}

} // namespace

MEX_DISPATCH // Don't forget to add this if MEX_DEFINE() is used.
