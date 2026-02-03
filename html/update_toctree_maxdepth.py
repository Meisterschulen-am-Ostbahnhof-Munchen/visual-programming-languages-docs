import os
import re

DOCS_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'docs'))

def update_maxdepth():
    print(f"Scanning files in {DOCS_ROOT} to update toctree maxdepth to 1...\n")
    
    files_updated = 0
    
    for root, dirs, files in os.walk(DOCS_ROOT):
        for file in files:
            if file.endswith(".md"):
                file_path = os.path.join(root, file)
                
                with open(file_path, 'r', encoding='utf-8') as f:
                    lines = f.readlines()
                
                new_lines = []
                modified = False
                in_toctree = False
                maxdepth_found = False
                
                for i, line in enumerate(lines):
                    stripped = line.strip()
                    
                    if "```{toctree}" in line:
                        in_toctree = True
                        new_lines.append(line)
                        maxdepth_found = False # Reset for new block
                        continue
                        
                    if in_toctree:
                        if "```" in stripped and not stripped.startswith(":"):
                            if not maxdepth_found:
                                pass
                            in_toctree = False
                            new_lines.append(line)
                            continue
                        
                        if stripped.startswith(":maxdepth:"):
                            new_lines.append(":maxdepth: 1\n")
                            modified = True
                            maxdepth_found = True
                            continue
                        
                        pass
                        
                    new_lines.append(line)

                final_lines = []
                skip_next = False
                file_modified = False
                
                i = 0
                while i < len(lines):
                    line = lines[i]
                    final_lines.append(line)
                    
                    if "```{toctree}" in line.strip():
                        if i + 1 < len(lines) and ":maxdepth:" in lines[i+1]:
                            if lines[i+1].strip() != ":maxdepth: 1":
                                final_lines.append(":maxdepth: 1\n")
                                i += 1 
                                file_modified = True
                            else:
                                pass 
                        else:
                            final_lines.append(":maxdepth: 1\n")
                            file_modified = True
                    i += 1
                
                if file_modified:
                    with open(file_path, 'w', encoding='utf-8') as f:
                        f.writelines(final_lines)
                    print(f"Updated: {os.path.basename(file_path)}")
                    files_updated += 1

    print(f"\nTotal files updated: {files_updated}")

if __name__ == "__main__":
    update_maxdepth()
