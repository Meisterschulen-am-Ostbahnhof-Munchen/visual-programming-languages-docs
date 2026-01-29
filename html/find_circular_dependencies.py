import os

def find_circular_candidates():
    start_dir = "."
    exclude_dirs = {'.git', '.github', '.gemini', '__pycache__', 'env', 'venv', 'node_modules', '_build', 'build', 'dist', '_static', 'images'}

    for root, dirs, files in os.walk(start_dir):
        dirs[:] = [d for d in dirs if d not in exclude_dirs and not d.startswith('.')]
        
        folder_name = os.path.basename(root)
        
        has_index = "index.md" in files
        
        # Check for DirName.md
        dirname_md = None
        for f in files:
            if f.lower() == f"{folder_name}.md".lower() and f != "index.md":
                dirname_md = f
                break
        
        if has_index and dirname_md:
            print(f"Potential circular dependency in {root}: has 'index.md' and '{dirname_md}'")

if __name__ == "__main__":
    find_circular_candidates()
