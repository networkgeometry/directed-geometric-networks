import subprocess
import pandas
import random
# import time
import sys
import os

networkName = sys.argv[1]

nbSyntheticEdgelists = 0
gpropFilename = "../../directedS1_data/synthetic_networks/network_properties/" + networkName + "_gprop.txt"
if not os.path.isfile(gpropFilename):
    with open(gpropFilename, "w") as gpropFile:
        gpropFile.write("# {:>28} ".format("name"))
        gpropFile.write("{:>20} ".format("nb_vertices"))
        gpropFile.write("{:>20} ".format("nb_edges"))
        gpropFile.write("{:>20} ".format("density"))
        gpropFile.write("{:>20} ".format("average_degree"))
        gpropFile.write("{:>20} ".format("nb_vert_deg_gt_0"))
        gpropFile.write("{:>20} ".format("nb_vert_deg_gt_1"))
        gpropFile.write("{:>20} ".format("nb_reciprocal_edges"))
        gpropFile.write("{:>20} ".format("reciprocity_ratio"))
        gpropFile.write("{:>20} ".format("reciprocity_stat"))
        gpropFile.write("{:>20} ".format("avg_undir_loc_clust"))
        gpropFile.write("{:>20} ".format("undir_glob_clust"))
        gpropFile.write("{:>20} ".format("nb_triangles"))
        gpropFile.write("{:>20} ".format("TriSpect_3cycle"))
        gpropFile.write("{:>20} ".format("TriSpect_3nocycle"))
        gpropFile.write("{:>20} ".format("TriSpect_4cycle"))
        gpropFile.write("{:>20} ".format("TriSpect_4outward"))
        gpropFile.write("{:>20} ".format("TriSpect_4inward"))
        gpropFile.write("{:>20} ".format("TriSpect_5cycle"))
        gpropFile.write("{:>20} ".format("TriSpect_6cycle"))
        gpropFile.write("\n")
else:
    header = open(gpropFilename, 'r').readline().replace('#', ' ').split()
    gpropDF = pandas.read_table(gpropFilename, names=header, comment="#", delimiter=r"\s+")
    nbSyntheticEdgelists = gpropDF.shape[0]

aimedNbRandomEdgelists = 1000
inferedParamsFilename = "../../directedS1_data/real_networks/inferred_parameters/" + networkName + "_infparams.txt"
synthEdgelistRootname = networkName + "_synth"
synthEdgelistFilename = networkName + "_synth_edgelist.txt"
if os.path.isfile(inferedParamsFilename):
    for j in range(aimedNbRandomEdgelists - nbSyntheticEdgelists):
        # time.sleep(1)
        cmd = ["../infer_parameters/generating_directedS1", "-s", str(random.randint(1, 32767)), "-o", synthEdgelistRootname, "-a", inferedParamsFilename]
        # print(cmd)
        subprocess.Popen(cmd).wait()
        cmd = ["../analyze_networks/extract_network_properties", synthEdgelistFilename, networkName, gpropFilename]
        # print(cmd)
        subprocess.Popen(cmd).wait()

    os.remove(synthEdgelistFilename)
