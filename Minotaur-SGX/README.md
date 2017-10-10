## Setup
IP addresses and port tuples for Spout and Count bolts should be written in files named `spoutIP` and `countIP` respectively. Examples are availabe in the preexisting files. 

## Usage
Run spout using
    ./app spout <spout_id> <spoutIP> <spoutPort>  

Run split bolt using
    ./app splitter <split_id>

Run count bolt using
    ./app count <count_id> <countIP> <countPort>


Example usage can be seen in the `rundistributed.sh` script
