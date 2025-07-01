# Generate IKFast Solver

This repository extracts only the IKSolver cpp file generation scripts from the [MoveIt ikfast_kinematics_plugin](https://github.com/moveit/moveit/tree/master/moveit_kinematics/ikfast_kinematics_plugin) repository.

The following command generates IK solver cpp from a sample URDF. Please replace the arguments and URDF as appropriate for your use.

```
scripts/auto_create_ikfast_moveit_plugin.sh --iktype Transform6D --freejoint e_1 --name m710ic70 m710ic70_7axis.urdf m710ic70 base_link flange
```
