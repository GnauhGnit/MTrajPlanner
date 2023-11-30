# MTrajPlanner: A Multiple-Trajectory Planning Algorithm for Autonomous Underwater Vehicles  


## Introduction

Trajectory planning is a crucial task in designing the navigation systems of automatic underwater vehicles (AUVs). Due to the complexity of underwater environments, decision makers may hope to obtain multiple alternative trajectories in order to select the best. This paper focuses on the multiple-trajectory planning (MTP) problem, which is a new topic in this field. First, we establish a comprehensive MTP model for AUVs, by taking into account the complex underwater environments, the efficiency of each trajectory, and the diversity among different trajectories, simultaneously. Then, to solve the MTP, we develop an ant colony-based trajectory optimizer, which is characterized by a niching strategy, a decayed alarm pheromone measure, and a diversified heuristic measure. The niching strategy assists in identifying and maintaining a diverse set of high-quality solutions. The use of decayed alarm pheromone and diversified heuristic further improves the search effectiveness and efficiency of the algorithm. Experimental results on practical datasets show that our proposed algorithm not only provides multiple AUV trajectories for a flexible choice, but it also outperforms the state-of-the-art algorithms in terms of the single trajectory efficiency.  

## Input data
The input data are comprised of seamounts, suspensions and sea currents.

- **Seamount**: Directory of the underwater seamount data, i.e., the height of the underwater seamounts.
- **Suspension**: Directory of the suspended object data. In the file, each line lists the center location (x, y, z) and the size of suspension.
- **Current**: Directory of the sea current Data. For example, the file current_x_25.txt is the superposed force on X-axis.


## Paper 

* For more information please refer to our paper 

  If the code or paper is useful for your work, please cite our [paper](https://ieeexplore.ieee.org/abstract/document/10038633) 

  with plain text

  > Y. -J. Gong, T. Huang, Y. -N. Ma, S. -W. Jeon and J. Zhang, "MTrajPlanner: A Multiple-Trajectory Planning Algorithm for Autonomous Underwater Vehicles," in IEEE Transactions on Intelligent Transportation Systems, vol. 24, no. 4, pp. 3714-3727, April 2023, doi: 10.1109/TITS.2023.3234937.

  or bibtex
  
  > @ARTICLE{MTrajPlanner,
  author={Gong, Yue-Jiao and Huang, Ting and Ma, Yi-Ning and Jeon, Sang-Woon and Zhang, Jun},
  journal={IEEE Transactions on Intelligent Transportation Systems}, 
  title={MTrajPlanner: A Multiple-Trajectory Planning Algorithm for Autonomous Underwater Vehicles}, 
  year={2023},
  volume={24},
  number={4},
  pages={3714-3727},
  doi={10.1109/TITS.2023.3234937}}
