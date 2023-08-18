import numpy as np
import pandas as pd
import scipy.stats as st


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


if __name__ == "__main__":
    # Number of vertices.
    nb_vertices = 25000

    # Generates the names of the vertices (v + number).
    vnames = np.array(['v' + str(i).zfill(5) for i in range(nb_vertices)])

    # Generates the kappas.
    #   distributed according to a pareto prob. density function.
    kappa_min, kappa_max, gamma = 5, 100, 2.5
    kappa = [val for val in kappa_min * st.pareto.rvs(gamma-1, size=nb_vertices) if val < kappa_max]
    while len(kappa) < nb_vertices:
        kappa.extend([val for val in kappa_min * st.pareto.rvs(gamma-1, size=nb_vertices - len(kappa)) if val < kappa_max])

    # # Generates the azimutal angular positions
    # #   uniformly distributes in [0, 2pi)
    # theta = 2 * np.pi * np.random.random_sample(nb_vertices)

    # Creates a dataframe with everything in it.
    df = pd.DataFrame(data={'vertex': vnames, 'kappa_in': kappa, 'kappa_out': kappa})

    # Shuffles the kappa and saves it in a file.
    np.random.shuffle(kappa)
    df['kappa_in'] = kappa
    np.random.shuffle(kappa)
    df['kappa_out'] = kappa
    df.to_fwf('../../directedS1_data/synthetic_networks/hidden_variables/graphC_00_hidden_variables.txt', ['vertex', 'kappa_in', 'kappa_out'])
