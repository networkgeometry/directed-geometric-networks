# -​*- coding: utf-8 -*​-
# @author: Antoine Allard <antoineallard.info>
from graph_tool.all import *
import numpy
import glob
import os

networks = glob.glob("*.xml.zst")

for rname in networks:
    # Rootname
    rname = rname.split(".")[0]

    if not os.path.isfile("../../edgelists/" + rname + "_edgelist.txt"):

        print("extracting " + rname)

        # Loads the network.
        g = graph_tool.load_graph(rname + ".xml.zst")

        with open("../../edgelists/" + rname + "_edgelist.txt", "ab") as f:
            header = "Downloaded from Netzschleuder (https://networks.skewed.de/)\n"

            # Writes the name of the graph.
            header = header + "    name: {}\n".format(rname)

            # Writes the tags
            text = g.graph_properties['tags']
            text = " ".join(text)
            text = "    tags: {}\n".format(text)
            header = header + text

            # # Writes the citation
            # text = g.graph_properties['citation']
            # text = "  citation: {}\n".format(text)
            # header = header + text

            # Writes the original url
            text = g.graph_properties['url']
            text = "    url:  {}\n".format(text)
            header = header + text

            # Writes the column names
            header = header + " SourceVertex    TargetVertex"

            # Writes the edgelist.
            numpy.savetxt(f, g.get_edges(),
                          fmt="%15s", delimiter=" ",
                          header=header)
