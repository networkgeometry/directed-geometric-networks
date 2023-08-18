import subprocess
import sys
import os

networkName = sys.argv[1]
edgelistFilename = "../../directedS1_data/real_networks/edgelists/" + networkName + "_edgelist.txt"

beta = sys.argv[2]
nu = sys.argv[3]

numberInferenceRuns = 1
for i in range(numberInferenceRuns):

    outputFilename = "../../directedS1_data/real_networks/inferred_parameters/" + networkName + "_beta{}_nu{}_{:02d}".format(beta.replace(".","p"), nu.replace(".","p").replace("-","m"), i)
    if not os.path.isfile(outputFilename + "_log.txt"):
        cmd = ["../infer_parameters/fitting_directedS1", "-o", outputFilename, "-b", beta, "-n", nu, edgelistFilename]
        # print(cmd)
        subprocess.Popen(cmd).wait()
