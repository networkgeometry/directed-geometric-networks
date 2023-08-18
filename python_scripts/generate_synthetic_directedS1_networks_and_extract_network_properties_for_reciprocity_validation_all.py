import subprocess

scriptFile = 'generate_synthetic_directedS1_networks_and_extract_network_properties_for_reciprocity_validation.py'

# Results for Figure 1
for graph in ['graphA_00', 'graphB_00']:

    for beta in ['1.20', '1.40', '1.60', '1.80', '2.00', '2.20', '2.40', '2.60', '2.80', '3.00', '3.20']:

        for nu in ['-1.00', '-0.80', '-0.60', '-0.40', '-0.20', '+0.00', '+0.20', '+0.40', '+0.60', '+0.80', '+1.00']:

            cmd = ['python', scriptFile, graph, beta, nu, 'fixed_angular_positions', 'extract_triangles']
            print(cmd)
            subprocess.Popen(cmd).wait()


# # Results for Figure 1 with bigger network
# for graph in ['graphE_00', 'graphF_00']:

#     for beta in ['1.20', '1.80', '3.20']:

#         for nu in ['-1.00', '-0.80', '-0.60', '-0.40', '-0.20', '+0.00', '+0.20', '+0.40', '+0.60', '+0.80', '+1.00']:

#             cmd = ['python', scriptFile, graph, beta, nu, 'fixed_angular_positions', 'extract_triangles']
#             print(cmd)
#             subprocess.Popen(cmd).wait()


# # Results for Supplementary Figure 1
# for graph in ['graphD_00']:

#     for beta in ['1.10', '1.50', '1.90', '2.30', '2.70', '3.10', '3.50', '3.90']:

#         for nu in ['+0.00']:

#             cmd = ['python', scriptFile, graph, beta, nu, 'random_angular_positions', 'extract_triangles']
#             print(cmd)
#             subprocess.Popen(cmd).wait()
