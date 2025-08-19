# [Autoconfig: SFMRFLP](https://doi.org/10.1016/j.ejor.2024.06.001)

> [!WARNING]
> An up-to-date and mantained version of this project can be found inside the [Mork Github repo](https://github.com/mork-optimization/mork/example-flayouts) as an example of how to use the framework. This copy has been archived for reference purposes only.

## Abstract
Metaheuristic algorithms have become one of the preferred approaches for
solving optimization problems. Finding the best metaheuristic for a given
problem is often difficult due to the large number of available approaches
and possible algorithmic designs. Moreover, high-performing metaheuristics
often combine general-purpose and problem-specific algorithmic components.
We propose here an approach for automatically designing metaheuristics using
a flexible framework of algorithmic components, from which algorithms
are instantiated and evaluated by an automatic configuration method. The
rules for composing algorithmic components are defined implicitly by the
properties of each algorithm component, in contrast to previous proposals,
which require a handwritten algorithmic template or grammar. As a result,
extending our framework with additional components, even problem-specific
or user-defined ones, automatically updates the design space. We provide
an implementation of our proposal and demonstrate its benefits by outperforming
earlier research in three distinct problems from completely different
families: a facility layout problem, a vehicle routing problem and a clustering
problem.

## Links to Github repositories
- https://github.com/rmartinsanta/ac-VRPOD
- https://github.com/rmartinsanta/ac-BMSSC
- https://github.com/rmartinsanta/ac-SFMRFLP


## Authors of the Autoconfig proposal
- Raúl Martín Santamaría
- Manuel López-Ibáñez
- Thomas Stützle
- José Manuel Colmenar

## Authors of the original work
- Alberto Herrán
- José Manuel Colmenar
- Abraham Duarte

## Instance format
First line contains a number (N) representing the number of facilities.
Next non-blank line contains N numbers representing the width of each facility.
Then, a matrix of size NxN is provided, where each cell contains the flow between facilities (i,j), where
0 <= i < N and 0 <= j < N. Matrix is symmetric, so `flow[i][j] == flow[j][i]`.

## Properties used for instance classification and selection
We have considered instance data as a graph (facility flow being weighted edges if not zero), and used the following properties:
- num_facilities
- num_edges
- facility_max_degree
- facility_min_degree
- facility_avg_degree
- facility_std_degree
- is_regular
- facility_max_size
- facility_min_size
- facility_avg_size
- facility_std_size
- edge_max_weight
- edge_min_weight
- edge_avg_weight
- edge_std_weight
- density

## Cite
Consider citing the original SFMRFLP paper if used in your own work, or the Autoconfig proposal.

### DOI SFMRFLP
https://doi.org/10.1016/j.ejor.2021.03.027

### Bibtex SFMRFLP
```bibtex
@article{herran2021efficient,
  title={An efficient variable neighborhood search for the space-free multi-row facility layout problem},
  author={Herr{\'a}n, Alberto and Colmenar, J Manuel and Duarte, Abraham},
  journal={European Journal of Operational Research},
  volume={295},
  number={3},
  pages={893--907},
  year={2021},
  publisher={Elsevier}
}

```

### DOI Autoconfig
[10.1016/j.ejor.2024.06.001](https://doi.org/10.1016/j.ejor.2024.06.001)

### Bibtex Autoconfig
```bibtex
@article{Martin2024AutoconfigMork,
title = {On the automatic generation of metaheuristic algorithms for combinatorial optimization problems},
journal = {European Journal of Operational Research},
volume = {318},
number = {3},
pages = {740-751},
year = {2024},
issn = {0377-2217},
doi = {https://doi.org/10.1016/j.ejor.2024.06.001},
url = {https://www.sciencedirect.com/science/article/pii/S0377221724004296},
author = {Raúl Martín-Santamaría and Manuel López-Ibáñez and Thomas Stützle and J. Manuel Colmenar},
}
```
