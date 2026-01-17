import os
import re

# Configuration
search_dirs = [
    r"docs/training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen",
    r"docs/training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen"
]

target_fbs = [
    "AX_FB_TOF", "AX_FB_TON", "AX_FB_TP",
    "FB_TON", "FB_TOF", "FB_TP",
    "E_PULSE", "E_TP", "E_TON", "E_TONOF",
    "AX_TON", "AX_TONOF", "AX_TOF", "AX_PULSE"
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
                            # Look for Type="fb" or Type="namespace::fb"
                            # The pattern checks for Type="...fb" where ... can be anything ending with :: or nothing
                            pattern = fr'Type="([^"]*::)?{re.escape(fb)}"' 
                            if re.search(pattern, content):
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
