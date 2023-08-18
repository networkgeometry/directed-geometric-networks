import sys
import itertools
import numpy as np
import pandas as pd


def to_fwf(df, fname, cols=None, width=15, prec=7, vnames=True):
    """Custom method 'to_fwf' for Pandas

    Parameters
    ----------
    fname : str
        The path to the new file in which the hidden parameters will be written.
    cols : list or array of strings, optional
        A list or an array containing the name of the columns (as strings) to
        be written in the file (if None all columns will be written).
    width : integer, optional
        Width of the columns (default is 15 characters).
    prec : decimal precision of the floats written into the file (default is 7).
    vnames : bool, optional
        Boolean indicating whether the first column contains the names of the
        vertices and should therefore be treated as strings (default is True).
    """

    if cols is None:
        cols = df.columns

    with open(fname, 'w') as ofile:

        fmt_str = '{:>' + '{}'.format(width) + '} '
        string_to_write = ''.join(fmt_str.format(i) for i in cols) + '\n'
        ofile.write(string_to_write.replace(' ', '#', 1))

        fmt_str = []
        nb_cols = len(cols)
        if vnames:
            fmt_str.append('%{}s '.format(width))
            nb_cols = nb_cols - 1

        fmt_str.extend(['%{}.{}f '.format(width, prec) for i in range(nb_cols)])
        fmt_str = ''.join(fmt_str)

        np.savetxt(ofile, df[cols].values, fmt=fmt_str)


# Adds the custom method to Pandas.
pd.DataFrame.to_fwf = to_fwf

hidden_variables_filename = sys.argv[1]
output_filename = sys.argv[2]
nu = float(sys.argv[3])
seed = int(sys.argv[4])

np.random.seed(seed)

header = open(hidden_variables_filename, 'r').readline().replace('#', ' ').split()
df = pd.read_table(hidden_variables_filename, names=header, comment="#", delimiter=r"\s+")

pij = 1 / (1 + np.sum(df['kappa_out']) / np.outer(df['kappa_out'], df['kappa_in']))
np.fill_diagonal(pij, 0)
pji = np.transpose(pij)

r = np.random.uniform(size=pij.shape)

if nu < 0:
    p11 = (1 + nu) * np.multiply(pij, pji) + nu * (1 - pij - pji) * ((pij + pji - 1) > 0)
    np.fill_diagonal(p11, False)
    # edgelist = np.nonzero(p)
else:
    p11 = (1 - nu) * np.multiply(pij, pji) + nu * np.minimum(pij, pji)
    np.fill_diagonal(p11, False)
    # edgelist = np.nonzero(p)

source = []
target = []
for i,j in itertools.combinations(range(len(df['kappa_out'])), 2):
    if r[i, j] < p11[i, j]:
        source.append(i)
        target.append(j)
        source.append(j)
        target.append(i)
    elif r[i, j] < pji[i, j]:
        source.append(j)
        target.append(i)
    elif r[i, j] < pij[i, j] + pji[i, j] - p11[i, j]:
        source.append(i)
        target.append(j)



df = pd.DataFrame(data={'vertex1': source, 'vertex2': target})
df.to_fwf(output_filename, ['vertex1', 'vertex2'], prec=0, vnames=False)
