import subprocess
import pandas
import random
import sys
import os

networkName = sys.argv[1]
beta = sys.argv[2]
nu = sys.argv[3]
angular_positions = sys.argv[4]
triangles = sys.argv[5]

synthNetworkName = networkName + "_beta{}_nu{}".format(beta.replace(".","p"), nu.replace("-", "m").replace("+", "p").replace(".","p"))

nbSyntheticEdgelists = 0
gpropFilename = "../../directedS1_data/synthetic_networks/network_properties/" + synthNetworkName + "_gprop.txt"
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
        if triangles == "extract_triangles":
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


aimedNbRandomEdgelists = 100
inferedParamsFilename = "../../directedS1_data/synthetic_networks/hidden_variables/" + networkName + "_hidden_variables.txt"
synthEdgelistRootname = synthNetworkName + "_synth"
synthEdgelistFilename = synthNetworkName + "_synth_edgelist.txt"
if os.path.isfile(inferedParamsFilename):
    if aimedNbRandomEdgelists != nbSyntheticEdgelists:
        for j in range(aimedNbRandomEdgelists - nbSyntheticEdgelists):

            if angular_positions == "fixed_angular_positions":
                 cmd = ["../infer_parameters/generating_directedS1", "-n", "-t", "-s", str(random.randint(1, 32767)), "-o", synthEdgelistRootname, "-b", beta, "-i", nu.replace("+", ""), inferedParamsFilename]
            if angular_positions == "random_angular_positions":
                cmd = ["../infer_parameters/generating_directedS1", "-n", "-s", str(random.randint(1, 32767)), "-o", synthEdgelistRootname, "-b", beta, "-i", nu.replace("+", ""), inferedParamsFilename]

            subprocess.Popen(cmd).wait()
            if triangles == "extract_triangles":
                cmd = ["../analyze_networks/extract_network_properties", synthEdgelistFilename, synthNetworkName, gpropFilename]
            if triangles == "ignore_triangles":
                cmd = ["../analyze_networks/extract_network_properties_no_triangles", synthEdgelistFilename, synthNetworkName, gpropFilename]

            subprocess.Popen(cmd).wait()

            os.remove(synthEdgelistFilename)
