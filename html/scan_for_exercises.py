import os
import re

# Configuration
search_dirs = [
    r"docs/training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen",
    r"docs/training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen"
]

target_fbs = [
    # Timers
    "AX_FB_TOF", "AX_FB_TON", "AX_FB_TP",
    "FB_TON", "FB_TOF", "FB_TP",
    "E_PULSE", "E_TP", "E_TON", "E_TONOF",
    "AX_TON", "AX_TONOF", "AX_TOF", "AX_PULSE",
    
    # Flip-Flops
    "FB_RS", "FB_SR",
    "E_T_FF", "E_T_FF_SR", "E_SR", "E_RS", "E_D_FF",
    "AX_RS", "ASR_AX_SR", "AX_T_FF_SR", "AX_D_FF",
    "AX_T_FF", "AX_SR", # Adding potential variations or aliases if needed
    
    # IO Blocks
    "IB", "ID", "IE", "IL", "IW", "IX",
    "QB", "QD", "QL", "QW", "QX",
    
    # Sequence Control
    "sequence_E_04", "sequence_E_05", "sequence_E_08",
    "sequence_T_04", "sequence_T_05", "sequence_T_08",
    "sequence_ET_04", "sequence_ET_05", "sequence_ET_08",
    "sequence_E_04_loop", "sequence_E_05_loop", "sequence_E_08_loop",
    "sequence_T_04_loop", "sequence_T_05_loop", "sequence_T_08_loop",
    "sequence_ET_04_loop", "sequence_ET_05_loop", "sequence_ET_08_loop",
    "sequence_E_04_AX", "sequence_E_05_AX", "sequence_E_08_AX",
    "sequence_T_04_AX", "sequence_T_05_AX", "sequence_T_08_AX",
    "sequence_ET_04_AX", "sequence_ET_05_AX", "sequence_ET_08_AX",
    "sequence_E_04_loop_AX", "sequence_E_05_loop_AX", "sequence_E_08_loop_AX",
    "sequence_T_04_loop_AX", "sequence_T_05_loop_AX", "sequence_T_08_loop_AX",
    "sequence_ET_04_loop_AX", "sequence_ET_05_loop_AX", "sequence_ET_08_loop_AX",
    
    # Missing items
    "AUDI_TO_AD", "ADI_DI_TO_DINT", "AUDI_CTUD_UDINT"
]

def scan_files():
    fb_usage = {} # Key: FB Type, Value: List of Exercises

    for directory in search_dirs:
        if not os.path.exists(directory):
            print(f"Directory not found: {directory}")
            continue

        for filename in os.listdir(directory):
            if filename.endswith(".SUB"):
                filepath = os.path.join(directory, filename)
                exercise_name = os.path.splitext(filename)[0]
                
                try:
                    with open(filepath, 'r', encoding='utf-8') as f:
                        content = f.read()
                        
                        # Search for FB instantiations: Type="FB_NAME"
                        # We use regex to be robust against spacing
                        for fb in target_fbs:
                            # Look for Type="...fb" where ... can be anything ending with :: or _
                            # We want to match explicit usage.
                            # Example: Type="logiBUS::io::DI::logiBUS_IX" should match IX
                            # Example: Type="E_TON" should match E_TON
                            pattern = fr'Type="[^"]*([:_]){re.escape(fb)}"'
                            
                            # Also handle exact match
                            pattern_exact = fr'Type="{re.escape(fb)}"'
                            
                            if re.search(pattern, content) or re.search(pattern_exact, content):
                                if fb not in fb_usage:
                                    fb_usage[fb] = []
                                if exercise_name not in fb_usage[fb]:
                                    fb_usage[fb].append(exercise_name)
                                    
                except Exception as e:
                    print(f"Error reading {filepath}: {e}")

    # Print results
    print("--- Found Exercises ---")
    for fb, exercises in fb_usage.items():
        print(f"{fb}: {', '.join(exercises)}")

if __name__ == "__main__":
    scan_files()
