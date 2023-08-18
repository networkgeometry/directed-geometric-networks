import subprocess

scriptFile = 'generate_synthetic_directedCM_networks_and_extract_network_properties_for_reciprocity_validation.py'

for graph in ['graphA_00', 'graphB_00']:

    for nu in ['-1.00', '-0.80', '-0.60', '-0.40', '-0.20', '+0.00', '+0.20', '+0.40', '+0.60', '+0.80', '+1.00']:

        cmd = ['python', scriptFile, graph, nu]
        print(cmd)
        subprocess.Popen(cmd).wait()


# for graph in ['graphE_00', 'graphF_00']:

#     for nu in ['-1.00', '-0.80', '-0.60', '-0.40', '-0.20', '+0.00', '+0.20', '+0.40', '+0.60', '+0.80', '+1.00']:

#         cmd = ['python', scriptFile, graph, nu]
#         print(cmd)
#         subprocess.Popen(cmd).wait()