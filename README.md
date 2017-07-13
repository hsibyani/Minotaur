Install Zeromq 

wget https://github.com/zeromq/libzmq/releases/download/v4.2.1/zeromq-4.2.1.tar.gz

tar -xf zeromq-4.2.1.tar.gz

cd zeromq-4.2.1/

./configure
make
sudo make install
sudo ldconfig


