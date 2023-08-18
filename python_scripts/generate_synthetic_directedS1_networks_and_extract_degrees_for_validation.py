import subprocess
import random
import os

networkName = "graphC_00"
beta = 2.2
nu = 0.5

synthNetworkName = networkName

degreeFilename = "../../directedS1_data/synthetic_networks/degrees/" + synthNetworkName + "_degree_seq.txt"

if not os.path.isfile(degreeFilename):
    with open(degreeFilename, "w") as degreeFile:
        degreeFile.write("# {:>6} ".format("vertex"))
        degreeFile.write("{:>4} ".format("iDeg"))
        degreeFile.write("{:>4} ".format("oDeg"))
        degreeFile.write("\n")

NbRandomEdgelists = 100
inferedParamsFilename = "../../directedS1_data/synthetic_networks/hidden_variables/" + networkName + "_hidden_variables.txt"
synthEdgelistRootname = synthNetworkName + "_synth"
synthEdgelistFilename = synthNetworkName + "_synth_edgelist.txt"
if os.path.isfile(inferedParamsFilename):
    for j in range(NbRandomEdgelists):
        # time.sleep(1)
        cmd = ["../infer_parameters/generating_directedS1", "-n", "-s", str(random.randint(1, 32767)), "-o", synthEdgelistRootname, "-b", str(beta), "-i", str(nu), inferedParamsFilename]
        # print(cmd)
        subprocess.Popen(cmd).wait()
        cmd = ["../analyze_networks/extract_joint_degree_sequence", synthEdgelistFilename, degreeFilename]
        # print(cmd)
        subprocess.Popen(cmd).wait()

    os.remove(synthEdgelistFilename)
