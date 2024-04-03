#include "llvm/IR/Instructions.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Pass.h"

#include <vector>
#include <string>

using namespace llvm;

// Global variables to store loop iteration counts and variables
std::vector<int> loopIterationCounts;
std::vector<std::string> variables;
int variableCount = 0;
int prevLoopDepth = 0;
int blockIndex = 0;

namespace {
class PowerConsumptionPass : public FunctionPass {
public:
  static char ID;
  PowerConsumptionPass() : FunctionPass(ID) {}

  // Function pass entry point
  bool runOnFunction(Function &F) override {
    // Iterate through basic blocks in the function
    for (BasicBlock &BB : F) {
      // Calculate power consumption for each basic block and print the result
      std::string blockPower = calculateFullBlockPower(BB, F);
      errs() << "  Power Consumption for Basic Block " << blockIndex << ": " << blockPower << "\n";
      blockIndex++;
    }

    return false; // Indicate that the function did not modify the code
  }

  void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.addRequired<LoopInfoWrapperPass>();
    AU.setPreservesAll();
  }

private:
    // Add a new variable to the list
    void addElement() {
        variableCount++;
        std::string varName = "n" + std::to_string(variableCount);
        variables.push_back(varName);
    }

    // Remove the last variable from the list
    void removeLastElement() {
        if (!variables.empty()) {
            variables.pop_back();
        }
    }

    // Check if the given element exists in the loop iteration counts
    bool findElement(int targetElement) {
        auto searchResult = std::find(loopIterationCounts.begin(), loopIterationCounts.end(), targetElement);
        return (searchResult != loopIterationCounts.end());
    }

    // Calculate power consumption for a basic block
    double calculateBlockPower(BasicBlock &BB) {
        double power = 0.0;

        // Iterate over instructions in the basic block
        for (Instruction &I : BB) {
            if (isa<BinaryOperator>(&I)) {
                if (I.getOpcode() == Instruction::Mul || I.getOpcode() == Instruction::SDiv ||
                    I.getOpcode() == Instruction::UDiv || I.getOpcode() == Instruction::SRem ||
                    I.getOpcode() == Instruction::URem) {
                    // Add higher power value for multiplication and division operations
                    power += 9;
                } else {
                    // Add lower power value for basic arithmetic operations
                    power += 4;
                }
            } else if (isa<LoadInst>(&I) || isa<StoreInst>(&I)) {
                // Add power value for memory accesses
                power += 8;
            } else if (isa<CallInst>(&I) || isa<BranchInst>(&I) || isa<ReturnInst>(&I) || isa<InvokeInst>(&I)) {
                // Add power value for control flow instructions, function calls
                power += 7;
            } else if (isa<AllocaInst>(&I) || isa<GetElementPtrInst>(&I) || isa<CastInst>(&I)) {
                // Add power value for type conversion operations
                power += 6;
            } else if (isa<PHINode>(&I) || isa<SelectInst>(&I) || isa<ShuffleVectorInst>(&I) || isa<ExtractValueInst>(&I) || isa<InsertValueInst>(&I)) {
                // Add power value for aggregate operations and miscellaneous instructions
                power += 3;
            } else if (isa<CmpInst>(&I) || isa<ExtractElementInst>(&I) || isa<InsertElementInst>(&I)) {
                // Add power value for basic arithmetic and logical operations
                power += 4;
            } else if (I.getType()->isFloatingPointTy()) {
                // Add power value for floating-point arithmetic operations
                power += 5;
            }
            // Add power contribution for other instruction types as needed
        }

        return power;
    }

    // Calculate the loop depth of a basic block
    int calculateLoopDepth(BasicBlock &BB) {
        int loopDepth = 0;
        LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();

        if (Loop *L = LI.getLoopFor(&BB)) {
            loopDepth = L->getLoopDepth();
        }

        return loopDepth;
    }

    // Count the iterations in the basic block
    void iterationCount(BasicBlock &BB, bool li) {
        int count = 0;
        int flag = 0;
        for (Instruction &I : BB) {
            if (ICmpInst *ICmp = dyn_cast<ICmpInst>(&I)) {
                Value *LastOperand = ICmp->getOperand(ICmp->getNumOperands() - 1);
                if (ConstantInt *CI = dyn_cast<ConstantInt>(LastOperand)) {
                    count = CI->getValue().getSExtValue();
                }
                flag = 1;
            } else if (FCmpInst *FCmp = dyn_cast<FCmpInst>(&I)) {
                Value *LastOperand = FCmp->getOperand(FCmp->getNumOperands() - 1);
                if (ConstantFP *CFP = dyn_cast<ConstantFP>(LastOperand)) {
                    count = (int)CFP->getValueAPF().convertToDouble();
                }
                flag = 1;
            }
        }
        if (count && flag && li) {
            loopIterationCounts.push_back(count);
        } else if (flag && li) {
            loopIterationCounts.push_back(-1);
            addElement();
        }
    }

    // Handle recursion in the basic block
    double handleRecursion(BasicBlock &BB, Function &F) {
        double value = 0;
        for (Instruction &I : BB) {
            if (llvm::CallInst *CI = dyn_cast<llvm::CallInst>(&I)) {
                llvm::Function *Callee = CI->getCalledFunction();
                if (Callee && Callee == &F) {
                    value += 50;
                }
            }
        }
        return value;
    }

    // Calculate the full power consumption for a basic block
    std::string calculateFullBlockPower(BasicBlock &BB, Function &F) {
        double value = 0, power = 1;
        int loopDepth = 0;
        bool loopIncrease = false;

        value = calculateBlockPower(BB);

        loopDepth = calculateLoopDepth(BB);

        if (prevLoopDepth > loopDepth) {
            if (!loopIterationCounts.empty()) {
                loopIterationCounts.pop_back();
                removeLastElement();
            }
        } else if (prevLoopDepth < loopDepth) {
            loopIncrease = true;
        }

        iterationCount(BB, loopIncrease);

        for (int count : loopIterationCounts) {
            if (count != -1) {
                power *= count;
            }
        }

        power *= value;

        std::string powerCalculation;

        if (findElement(-1)) {
            for (const std::string &var : variables) {
                powerCalculation += var; // Concatenate the variable name
                powerCalculation += "*";
            }
        }
        std::string powerValue;
        if (!powerCalculation.empty()) {
            powerCalculation.pop_back();
            powerCalculation = "*" + powerCalculation;
            powerValue = std::to_string((int)power);
            powerValue += powerCalculation;
        }
        if (!powerCalculation.empty()) {
            int val = (int)handleRecursion(BB, F);
            if (val) {
                powerValue += "+";
                powerValue += std::to_string(val);
            }
        } else {
            power += handleRecursion(BB, F);
            powerValue = std::to_string((int)power);
        }

        prevLoopDepth = loopDepth;

        return powerValue;
    }
};

char PowerConsumptionPass::ID = 0;
RegisterPass<PowerConsumptionPass> X("power-consumption", "Power Consumption Calculation Pass", false, false);
} // namespace
