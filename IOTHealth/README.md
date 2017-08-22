## Install Zeromq 
Each machine that you plan on using for the application would require following steps to install the pre-req:

```wget https://github.com/zeromq/libzmq/releases/download/v4.2.1/zeromq-4.2.1.tar.gz

tar -xf zeromq-4.2.1.tar.gz

cd zeromq-4.2.1/

./configure
make
sudo make install
sudo ldconfig

```

## Running a sample setup
Right now it can only be used to start up different components of a word count program
- To start up a spout use: ./app spout <spoutID> <spoutIP> <spoutPort>
- To start up a split use: ./app splitter <splitID> <n> <countIP1> <countPort1> ... <countIPn> <countPortn> <m> <spoutIP1> <spoutPort1> ... <spoutIPm> <spoutPortm>
- To start up a count use: ./app count <countID> <countIP> <countPort>

You can run the following commands on a single node or on multiple. 

For starting a spout instance: 
`./app spout 0 192.168.1.1 5000`

Starting a single split instance:
`./app splitter 0 1 192.168.1.3 6000 1 192.168.1.1 5000`

Starting a single count instance: 
`./app count 0 192.168.1.3 6000`