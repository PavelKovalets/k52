For Visual Studio there might be problems with libs (e.g. "cannot open file 'libboost_date_time-vc120-mt-gd-1_55.lib'").
Not completelly clear, is it a bug or feature, but according to http://www.boost.org/doc/libs/1_54_0/doc/html/thread/build.html it is fixed by compiling ALL dependant libs explicitly (bjam --build-type=complete --with-thread --with-chrono --with-date_time).

#Using Vagrant box
-Install Vagrant http://www.vagrantup.com/
-From project root (containing Vagrantfile) run 'vagrant up' to create a VM
-Run 'vagrant ssh' to connect to VM
-Run 'cd /vagrant' to move to the project directory
-Do what you need

#Build using cmake
git clone ...
cd k52
#edit config
mkdir build
cd build
cmake .. && make (or open generated k52.sln file if using Visual Studio)
