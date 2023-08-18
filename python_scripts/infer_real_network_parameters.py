import subprocess
import sys
import os

networkName = sys.argv[1]
edgelistFilename = "../../directedS1_data/real_networks/edgelists/" + networkName + "_edgelist.txt"

numberInferenceRuns = 1
for i in range(numberInferenceRuns):

    outputFilename = "../../directedS1_data/real_networks/inferred_parameters/" + networkName + "_{:02d}".format(i)
    if not os.path.isfile(outputFilename + "_log.txt"):
        cmd = ["../infer_parameters/fitting_directedS1", "-o", outputFilename, edgelistFilename]
        # print(cmd)
        subprocess.Popen(cmd).wait()
