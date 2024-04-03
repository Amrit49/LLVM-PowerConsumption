#include "llvm/Pass.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Metadata.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

// Global variable to keep track of the block index
int blockIndex = 0;

namespace {
// Define a pass to print LLVM IR representation of instructions in each basic block
struct InstructionInfoPass : public FunctionPass {
  static char ID;
  InstructionInfoPass() : FunctionPass(ID) {}

  // Entry point for the function pass
  bool runOnFunction(Function &F) override {
    // Iterate through basic blocks in the function
    for (BasicBlock &BB : F) {
      // Print the basic block index
      errs() << "Basic Block: " << blockIndex << "\n";
      blockIndex++;
      
      // Iterate through instructions in the basic block and print their LLVM IR representation
      for (Instruction &I : BB) {
        errs() << "    " << I << "\n";
      }

      errs() << "\n";
    }

    return false; // Indicate that the function did not modify the code
  }
};
}

// Initialize the ID for the instruction info pass
char InstructionInfoPass::ID = 0;

// Register the instruction info pass with LLVM pass manager
static RegisterPass<InstructionInfoPass> X("instruction-info", "Instruction Info Pass", false, false);
