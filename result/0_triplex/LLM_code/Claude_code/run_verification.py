#!/usr/bin/env python3
import re
import subprocess
import os
from datetime import datetime

class PropertyExtractor:
    def __init__(self):
        self.results_dir = "verification_results"
        self.include_path = "./ /usr/local/MATLAB/R2024b/simulink/include/"
        
    def extract_properties(self, file_path):
        """Extract all VERIFY_PROPERTY definitions from file"""
        properties = set()
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
            # Find all #ifdef VERIFY_PROPERTY_X patterns
            matches = re.findall(r'#ifdef\s+(VERIFY_PROPERTY_\d+)', content)
            for match in matches:
                # Extract the property number
                prop_num = int(match.split('_')[-1])
                properties.add(prop_num)
        return sorted(list(properties))

    def run_verification(self, property_num):
        """Run ESBMC verification for a specific property"""
        # Get all .c files in current directory
        c_files = [f for f in os.listdir('.') if f.endswith('.c')]
        if not c_files:
            print("Error: No .c files found in current directory")
            return "ERROR", "No .c files found"

        # Construct ESBMC command
        cmd = ["esbmc"] + c_files + [
            "-I", self.include_path,
            "--k-induction",
            "--memlimit", "8g",
            "--timeout", "300",
            f"-DVERIFY_PROPERTY_{property_num}"
        ]

        # Run verification
        try:
            result = subprocess.run(cmd, 
                                  capture_output=True, 
                                  text=True,
                                  timeout=300)
            output = result.stdout + result.stderr
            
            if "VERIFICATION SUCCESSFUL" in output:
                status = "SUCCESSFUL"
            elif "VERIFICATION FAILED" in output:
                status = "FAILED"
            else:
                status = "UNKNOWN"
                
            return status, output
        except subprocess.TimeoutExpired:
            return "TIMEOUT", "Verification timed out"
        except Exception as e:
            return "ERROR", str(e)

    def process_verifications(self, source_file):
        """Process all verifications based on extracted properties"""
        # Create results directory
        if not os.path.exists(self.results_dir):
            os.makedirs(self.results_dir)
            
        # Extract properties
        properties = self.extract_properties(source_file)
        print(f"Found properties: {properties}")
        
        # Create log file
        log_path = os.path.join(self.results_dir, "verification_summary.log")
        with open(log_path, 'w') as log:
            log.write(f"Verification Summary - {datetime.now()}\n")
            log.write(f"Source file: {source_file}\n")
            log.write("=" * 50 + "\n\n")
            
            # Process each property
            for prop_num in properties:
                print(f"\nVerifying Property {prop_num}...")
                log.write(f"Property {prop_num}\n")
                log.write("-" * 20 + "\n")
                
                # Run verification
                status, output = self.run_verification(prop_num)
                
                # Save detailed output
                output_file = os.path.join(self.results_dir, f"property_{prop_num}_result.txt")
                with open(output_file, 'w') as f:
                    f.write(output)
                
                # Log result
                result_line = f"Status: {status}"
                print(f"  {result_line}")
                log.write(f"{result_line}\n\n")

def main():
    # Find source files with VERIFY_PROPERTY definitions
    source_files = [f for f in os.listdir('.') if f.endswith('.c') or f.endswith('.h')]
    
    extractor = PropertyExtractor()
    properties_found = False
    
    for source_file in source_files:
        with open(source_file, 'r', encoding='utf-8') as f:
            if 'VERIFY_PROPERTY_' in f.read():
                print(f"\nProcessing file: {source_file}")
                extractor.process_verifications(source_file)
                properties_found = True
                break
    
    if not properties_found:
        print("No files with VERIFY_PROPERTY definitions found.")
    else:
        print("\nVerification complete. Results saved in verification_results/")

if __name__ == "__main__":
    main()
