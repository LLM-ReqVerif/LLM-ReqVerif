# LLM-ReqVerif: LLM-Assisted Formal Verification for Requirements

## 📌 Overview
LLM-ReqVerif is a framework for translating **natural language requirements** into **verifiable properties** and integrating them with **formal verification tools**. The project provides:
- **C code-based verification properties** extracted from Simulink models.
- **Automated verification scripts** using SLDV, CoCoSim, Claude+ESBMC, and ChatGPT+ESBMC.
- **A ground truth comparison framework** to evaluate different verification methods.

This repository includes all necessary resources to **run, test, and validate** formal verification using **LLMs and traditional tools**.

---

## 📁 Project Structure
LLM-ReqVerif/ 

│── include/ # Simulink C code dependencies (header files) 

│── raw_code/ # Generated C code used for verification 

│── result/ # Collected results from SLDV, CoCoSim, Claude+ESBMC, ChatGPT+ESBMC 

    └──  run_verification.py # Script for automated verification and ground truth evaluation 
    
    └──  results (9 folder for each tasks)
    
│── README.md # Project documentation 


### 🔹 **Key Components**
- **`include/`**: Contains required Simulink C header files for proper compilation.
- **`raw_code/`**: The main C code extracted from Simulink, forming the basis of all verification.
- **`result/`**: Verification results from various tools, including scripts for evaluating correctness.
- **`run_verification`**: A script that automatically evaluates results based on the ground truth from SLDV and CoCoSim.

---

## 🚀 Getting Started

### 1 **Clone the Repository**
```bash
git clone https://github.com/LukeW1999/LLM-ReqVerif.git
cd LLM-ReqVerif
```

### 2 Run Full Verification
result has been collected at /result/verification_summary.csv
But if you want to collect it again or use your own LLM prompts or models' result. Please modify the scripts, that should be structured that is easy to understand.

If only use to try the script performance. Modify the Scripts:
```
class PropertyVerifier:
    def __init__(self):
        self.include_paths = [
            "./",
            "/usr/local/MATLAB/R2024b/simulink/include",
            "/usr/local/MATLAB/R2024b/rtw/c/src",
            "/usr/local/MATLAB/R2024b/extern/include",
            "/usr/local/MATLAB/R2024b/simulink/include/sf_runtime"
        ]
```
with your own path.

Then 
```
cd result
python run_verification.py
```



### 3 Run a Specific Verification Property
To verify a specific property (e.g., VERIFY_PROPERTY_1), use:
```
cd 1_fsm/LLM_code/Claude_code
esbmc ert_main.c triplex_12B.c -I ./ -I ../../../ --k-induction --memlimit 8g --timeout 300 -DVERIFY_PROPERTY_1
```

⚙️ Dependencies
This framework relies on the following formal verification tools:

ESBMC – C Model Checker https://github.com/esbmc/esbmc

CoCoSim – MATLAB/Simulink Verification Tool (result has been collected, so it could be used without installation)

SLDV (Simulink Design Verifier) – MATLAB built-in verification tool (we expect you installed Matlab and Simulink plugins)

✅ Adapting to Other Formal Verification Tools

This framework can be adapted to other tools like CBMC, Kind2, CPAChecker, etc.

To do so, modify:
```c
__ESBMC_assert(bool, "")
```
to:

```c
assert(bool)
```
for compatibility with other verification tools.

### By the way, the simulink model is aviable from here:https://github.com/hbourbouh/lm_challenges

this repo did not contain Lockheed Martin Model.

### The prompts to reproduce is in the result folder.
