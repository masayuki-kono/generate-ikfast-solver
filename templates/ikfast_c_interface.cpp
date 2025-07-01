#define IKFAST_HAS_LIBRARY
#include "ikfast.h"
using namespace ikfast;

IKFAST_API bool ComputeIkC(const IkReal* eetrans, const IkReal* eerot, const IkReal* pfree, IkSolutionListC* solutions) {
  if (!eetrans || !eerot || !solutions) {
    return false;
  }

  ikfast::IkSolutionList<IkReal> cppSolutions;
  bool success = ComputeIk(eetrans, eerot, pfree, cppSolutions);
  if (!success) {
    return false;
  }

  int numJoints = GetNumJoints();
  int numSolutions = static_cast<int>(cppSolutions.GetNumSolutions());

  solutions->numJoints = numJoints;
  solutions->numSolutions = numSolutions;
  solutions->solutions = nullptr;

  if (numSolutions > 0) {
    int totalSize = numSolutions * numJoints;
    IkReal* solutionData = new IkReal[totalSize];
    std::vector<IkReal> jointValues(numJoints);
    for (int i = 0; i < numSolutions; ++i) {
      const auto& solution = cppSolutions.GetSolution(i);
      solution.GetSolution(&jointValues[0], pfree);
      for (int j = 0; j < numJoints; ++j) {
        solutionData[i * numJoints + j] = jointValues[j];
      }
    }
    
    solutions->solutions = solutionData;
    solutions->numSolutions = numSolutions;
  }
  
  return true;
}

IKFAST_API void FreeIkSolutionList(IkSolutionListC* solutions) {
  if (solutions && solutions->solutions) {
    delete[] solutions->solutions;
    solutions->solutions = nullptr;
    solutions->numSolutions = 0;
  }
}
