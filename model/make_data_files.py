#!/usr/bin/env python

##
#  Retrieves the actual data files from hypocenter. They are
#  very big
#

import getopt
import sys
import subprocess

model = "CVMH"

def usage():
    print("\n./make_data_files.py -d [cvmh1510] -u [uid]\n\n")
    print("-d - dataset to retrieve from hypocenter.\n")
    print("-u - username to use to do the dataset retrieval.\n")
    sys.exit(0)

def main():

    # Set our variable defaults.
    dataset = -1
    username = -1 
    path = "/var/www/html/research/ucvmc/" + model 

    # Get the dataset.
    try:
        opts, args = getopt.getopt(sys.argv[1:], "u:d:", ["user=", "dataset="])
    except getopt.GetoptError as err:
        print(str(err))
        usage()
        sys.exit(1)

    for o, a in opts:
        if o in ("-d", "--dataset"):
            dataset = str(a)
        if o in ("-u", "--user"):
            username = str(a) + "@"

    # If the iteration number was not provided, display the usage.
    if dataset == -1 or username == -1:
        usage()
        sys.exit(1)

    print("\nDownloading model dataset\n")

    subprocess.check_call(["scp", username +
                           "hypocenter.usc.edu:" + path + "/" + dataset +"/*",
                           "."])

    print("\nDone!")

if __name__ == "__main__":
    main()
