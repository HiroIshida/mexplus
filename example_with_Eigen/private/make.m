clear all;
addpath('../');
Compilar = 'GCC=/usr/bin/gcc-4.7';
CXXFLAGS = 'CXXFLAGS="$CXXFLAGS -std=c++11"';
path1 = ['-I' '../../include'];
path2 = ['-I' '/usr/include/eigen3'];
mex('-v', Compilar, path1, path2, CXXFLAGS, 'Monster_.cc');
m = Monster('hage');
mat = [1, 2; 3, 4];
vm = [mat;mat];
m.set_vecmat(vm);

