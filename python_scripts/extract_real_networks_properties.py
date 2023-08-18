import subprocess
import pandas
import glob
import os

alreadyExtracted = []
gpropFilename = "../../directedS1_data/real_networks/network_properties/all_gprop.txt"
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
    alreadyExtracted = list(gpropDF['name'])

for rname in glob.glob("../../directedS1_data/real_networks/edgelists/*_edgelist.txt"):

    nname = rname.split("/")[-1]
    nname = nname.split("_edgelist.txt")[0]

    if not nname in alreadyExtracted:

        print(nname)
        cmd = ["../analyze_networks/extract_network_properties", rname, nname, gpropFilename, str(25000), str(100000)]
        subprocess.Popen(cmd).wait()
