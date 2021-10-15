#!/usr/bin/env python

##
#  Retrieves the actual data files from hypocenter. They are
#  very big
#

import getopt
import sys
import subprocess

model = "CVMH"

if sys.version_info.major >= (3) :
  from urllib.request import urlopen
else:
  from urllib2 import urlopen

def usage():
    print("\n./make_data_files.py\n\n")
    sys.exit(0)

def download_urlfile(url,fname):
  try:
    response = urlopen(url)
    CHUNK = 16 * 1024
    with open(fname, 'wb') as f:
      while True:
        chunk = response.read(CHUNK)
        if not chunk:
          break
        f.write(chunk)
  except:
    e = sys.exc_info()[0]
    print("Exception retrieving and saving model datafiles:",e)
    raise
  return True

def main():

    # Set our variable defaults.
    path = ""

    try:
        fp = open('./config','r')
    except:
        print("ERROR: failed to open config file")
        sys.exit(1)

    ## look for model_data_path and other varaibles
    lines = fp.readlines()
    for line in lines :
        if line[0] == '#' :
          continue
        parts = line.split('=')
        if len(parts) < 2 :
          continue;
        variable=parts[0].strip()
        val=parts[1].strip()

        if (variable == 'model_data_path') :
            path = val + '/' + model
            continue
        if (variable == 'model_dir') :
            mdir = "./"+val
            continue
        continue
    if path == "" :
        print("ERROR: failed to find variables from config file")
        sys.exit(1)

    fp.close()

    print("\nDownloading model dataset\n")

    subprocess.check_call(["mkdir", "-p", "./"+mdir])

    flist=['base@@', 'BASE.gts', 'BATO.gts', 'CVM_CM_TAG@@', 'CVM_CM.vo', 'CVM_CM_VP@@', 'CVM_CM_VS@@', 'CVM_HR_TAG@@', 'CVM_HR.vo', 'CVM_HR_VP@@', 'CVM_HR_VS@@', 'CVM_LR.vo', 'CVMSM_flags@@', 'CVMSM_tag66@@', 'CVMSM_vp66@@', 'CVMSM_vs66@@', 'cvm_vs30_wills.hdr', 'cvm_vs30_wills.mdl', 'interfaces.vo', 'model_top@@', 'moho@@', 'MOHO.gts', 'topo_dem@@']

    for f in flist :
        fname = mdir + "/" +f
        url = path + "/" + fname
        print(url, fname)
        download_urlfile(url,fname)

    subprocess.check_call(["mkdir", "-p", "./"+mdir+'/tsurf'])

    fflist=['tsurf/CMxVM_Model3D_CalMex_BATO.ts', 'tsurf/CMxVM_Model3D_CM_BASE_Folded.dxf', 'tsurf/CMxVM_Model3D_CM_BASE_Folded.ts', 'tsurf/CVMH_Basement64.ts', 'tsurf/CVMH_CalMex_BATO.ts', 'tsurf/CVMH_Moho64.ts', 'tsurf/CVMH_Moho.ts']
    for ff in fflist :
        fname = mdir + "/" +ff
        url = path + "/" + fname
        download_urlfile(url,fname)

    print("\nDone!")

if __name__ == "__main__":
    main()
