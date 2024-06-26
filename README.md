# Geometric description of clustering in directed networks

This repository contains the code associated with [_Geometric description of clustering in directed networks_](https://arxiv.org/abs/2302.09055) by [A. Allard], [M. Á. Serrano] and [M. Boguñá].


## Installation

Installing and running this code requires [`CMake`](https://cmake.org/) and Python 3.

1. Clone this repository with the option `--recurse-submodules`
```
git clone --recurse-submodules https://github.com/networkgeometry/directed-geometric-networks.git
```

2. Copy the `directedS1_data` subdirectory out of the project's root directory.
```
cp -R directed-geometric-networks/directed-geometric-networks_data .
```

3. Compile the executables
```
cd directed-geometric-networks/analyze_networks; cmake .; make; cd ../..
cd directed-geometric-networks/infer_parameters; cmake .; make; cd ../..
```


## Real-world network data

Real-world network data was downloaded from [Netzschleuder](https://networks.skewed.de/). Each dataset was downloaded in the GraphML format (`.xml.zst`) in the directory `directed-geometric-networks_data/real_networks/rough_data/netzschleuder/` and extracted in the proper format by running
```
python extract_edgelists.py
```


## Generating the results and producing the figures

Details on how the results and the figures were generated are provided in the following notebooks
- [plot_figure_real_networks_reciprocity_vs_clustering.ipynb](python_scripts/plot_figure_real_networks_reciprocity_vs_clustering.ipynb)
- [plot_figure_reciprocity_real_vs_synthetic.ipynb](python_scripts/plot_figure_reciprocity_real_vs_synthetic.ipynb)
- [plot_figure_synthetic_networks_global_properties.ipynb](python_scripts/plot_figure_synthetic_networks_global_properties.ipynb)
- [plot_figure_synthetic_networks_reciprocity_vs_clustering.ipynb](python_scripts/plot_figure_synthetic_networks_reciprocity_vs_clustering.ipynb)
- [plot_figure_triangle_spectrum.ipynb](python_scripts/plot_figure_triangle_spectrum.ipynb)
- [plot_figure_validation_degree.ipynb](python_scripts/plot_figure_validation_degree.ipynb)
- [plot_figure_validation_reciprocity.ipynb](python_scripts/plot_figure_validation_reciprocity.ipynb)


## Paper

If you use this code, please consider citing:

_Geometric description of clustering in directed networks_<br/>
[A. Allard], [M. Á. Serrano] and [M. Boguñá]<br/>
[arXiv:2302.09055](https://arxiv.org/abs/2302.09055) (2023)<br/>

[A. Allard]: http://antoineallard.info
[M. Á. Serrano]: http://morfeo.ffn.ub.es/mariangeles/
[M. Boguñá]: http://complex.ffn.ub.es/~mbogunya/
