import subprocess
import random
import sys
import os

networkName = sys.argv[1]

synthNetworkName = networkName

degreeSeqFilename = "../../directedS1_data/synthetic_networks/degrees/" + synthNetworkName + "_degree_seq.txt"
if not os.path.isfile(degreeSeqFilename):
    with open(degreeSeqFilename, "w") as degreeSeqFile:
        degreeSeqFile.write("# {:>6} ".format("vertex"))
        degreeSeqFile.write("{:>4} ".format("iDeg"))
        degreeSeqFile.write("{:>4} ".format("oDeg"))
        degreeSeqFile.write("\n")

degreeDistFilename = "../../directedS1_data/synthetic_networks/degrees/" + synthNetworkName + "_degree_dist.txt"
if not os.path.isfile(degreeDistFilename):
    with open(degreeDistFilename, "w") as degreeDistFile:
        degreeDistFile.write("# {:>6} ".format("k"))
        degreeDistFile.write("{:>12} ".format("iDeg"))
        degreeDistFile.write("{:>12} ".format("oDeg"))
        degreeDistFile.write("\n")

NbRandomEdgelists = 100
inferedParamsFilename = "../../directedS1_data/real_networks/inferred_parameters/" + networkName + "_infparams.txt"
synthEdgelistRootname = synthNetworkName + "_synth"
synthEdgelistFilename = synthNetworkName + "_synth_edgelist.txt"
if os.path.isfile(inferedParamsFilename):
    for j in range(NbRandomEdgelists):
        # time.sleep(1)
        cmd = ["../infer_parameters/generating_directedS1", "-s", str(random.randint(1, 32767)), "-o", synthEdgelistRootname, "-a", inferedParamsFilename]
        # print(cmd)
        subprocess.Popen(cmd).wait()
        cmd = ["../analyze_networks/extract_joint_degree_sequence", synthEdgelistFilename, degreeSeqFilename]
        # print(cmd)
        subprocess.Popen(cmd).wait()
        cmd = ["../analyze_networks/extract_marginal_degree_dist", synthEdgelistFilename, degreeDistFilename]
        # print(cmd)
        subprocess.Popen(cmd).wait()

    os.remove(synthEdgelistFilename)
