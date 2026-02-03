import os
import re

# Configuration
DOCS_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'docs'))

def get_index_file(directory):
    """
    Tries to find the index file for a directory.
    Convention: {DirName}_Index.md
    """
    dirname = os.path.basename(directory)
    candidate = os.path.join(directory, f"{dirname}_Index.md")
    if os.path.exists(candidate):
        return candidate
    return None

def get_toctree_entries(index_file_path):
    """
    Parses an index file and returns a list of toctree entries.
    """
    entries = []
    with open(index_file_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()
        
    in_toctree = False
    for line in lines:
        stripped = line.strip()
        if "```{toctree}" in line:
            in_toctree = True
            continue
        if "```" in line and in_toctree:
            in_toctree = False
            continue
        
        if in_toctree and stripped and not stripped.startswith(":"):
            entries.append(stripped)
            
    return entries

def add_entry_to_toctree(index_file_path, entry):
    """
    Adds an entry to the toctree in the index file.
    """
    print(f"Adding '{entry}' to {index_file_path}")
    
    with open(index_file_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()
        
    new_lines = []
    in_toctree = False
    added = False
    
    for line in lines:
        if "```{toctree}" in line:
            in_toctree = True
            new_lines.append(line)
            continue
            
        if "```" in line and in_toctree:
            if not added:
                # Add the new entry before the closing block
                # We try to keep it sorted if possible, but appending is safer for now
                # Or we can read all, sort, and write back.
                # Let's simple append for now.
                new_lines.append(f"{entry}\n")
                added = True
            in_toctree = False
            new_lines.append(line)
            continue
            
        new_lines.append(line)
        
    if not added and in_toctree: 
        # EOF reached while in toctree? Unlikely but handle it
        new_lines.append(f"{entry}\n")
        new_lines.append("```\n")

    with open(index_file_path, 'w', encoding='utf-8') as f:
        f.writelines(new_lines)

def check_and_fix_consistency():
    for root, dirs, files in os.walk(DOCS_ROOT):
        # Skip hidden dirs
        if os.path.basename(root).startswith('.'):
            continue
            
        parent_index_file = get_index_file(root)
        if not parent_index_file:
            continue
            
        current_entries = get_toctree_entries(parent_index_file)
        
        # Check subdirectories
        for d in dirs:
            subdir_path = os.path.join(root, d)
            subdir_index = get_index_file(subdir_path)
            
            if subdir_index:
                # Expected entry: d/d_Index
                # or just d_Index if we are inside d? No, toctree entries are relative to the file.
                # If we are in root/Parent_Index.md, and we want to link root/Child/Child_Index.md
                # The entry should be Child/Child_Index
                
                expected_entry = f"{d}/{d}_Index"
                
                if expected_entry not in current_entries:
                    print(f"Missing entry in {parent_index_file}: {expected_entry}")
                    add_entry_to_toctree(parent_index_file, expected_entry)

if __name__ == "__main__":
    check_and_fix_consistency()
