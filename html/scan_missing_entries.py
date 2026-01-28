import json
import os
import re

# Configuration
JSON_PATH = os.path.join(os.path.dirname(__file__), 'Abkürzungen und Bedeutungen.json')
DOCS_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'docs'))
BASE_URL = 'https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/visual-programming-languages-docs/de/latest/'

# Files to ignore (not content blocks)
IGNORE_FILES = {
    'index.md', 'README.md', 'conf.py', 'requirements.txt', 'make.bat', 'Makefile', 
    'Welcome.md', 'Literatur.md', 'Übungsaufgaben.md', 'Visuelle-Programmiersprachen.md'
}

def get_linked_files_and_dirs(data):
    """Returns a set of normalized relative paths that are already linked in JSON, and a map of dir -> category_id."""
    linked_files = set()
    dir_category_map = {} # path/to/dir -> Counter of category_ids
    
    for category in data.get('categories', []):
        cat_id = category.get('id')
        for entry in category.get('data', []):
            link_int = entry.get('link_int', '')
            if not link_int: continue
            
            match = re.search(r'href="([^"]+)"', link_int)
            if match:
                url = match.group(1)
                if url.startswith(BASE_URL):
                    # Convert URL to relative path
                    rel_path = url[len(BASE_URL):].split('#')[0] # remove anchor
                    rel_path = rel_path.replace('.html', '.md')
                    linked_files.add(rel_path)
                    
                    # Track which category this directory usually belongs to
                    dir_path = os.path.dirname(rel_path)
                    if dir_path not in dir_category_map:
                        dir_category_map[dir_path] = {}
                    
                    dir_category_map[dir_path][cat_id] = dir_category_map[dir_path].get(cat_id, 0) + 1

    return linked_files, dir_category_map

def predict_category(file_rel_path, dir_category_map):
    """Guess category based on siblings."""
    dir_path = os.path.dirname(file_rel_path.replace(os.sep, '/'))
    if dir_path in dir_category_map:
        # Return category with most hits
        cats = dir_category_map[dir_path]
        return max(cats, key=cats.get)
    return "cat_types" # Default fallback

def scan_and_add_missing():
    print(f"Scanning for markdown files in {DOCS_ROOT} not in JSON...")
    
    with open(JSON_PATH, 'r', encoding='utf-8') as f:
        data = json.load(f)
    
    linked_files, dir_category_map = get_linked_files_and_dirs(data)
    
    missing_files = []
    
    # Walk docs directory
    for root, dirs, files in os.walk(DOCS_ROOT):
        # Skip hidden folders
        dirs[:] = [d for d in dirs if not d.startswith('.')]
        
        for file in files:
            if not file.endswith('.md'):
                continue
            
            if file in IGNORE_FILES:
                continue
                
            abs_path = os.path.join(root, file)
            rel_path_os = os.path.relpath(abs_path, DOCS_ROOT)
            rel_path_web = rel_path_os.replace(os.sep, '/')
            
            if rel_path_web not in linked_files:
                missing_files.append((rel_path_web, file))

    if not missing_files:
        print("No missing files found.")
        return

    print(f"Found {len(missing_files)} missing files.")
    
    added_count = 0
    for rel_path, filename in missing_files:
        term = os.path.splitext(filename)[0]
        
        # Heuristic: Skip if it looks like a directory index or helper
        if term.lower() in ['index', 'readme', 'intro']:
            continue

        print(f"[MISSING] {rel_path}")
        
        # Predict category
        target_cat_id = predict_category(rel_path, dir_category_map)
        
        # Create new entry
        new_entry = {
            "nr": "",
            "term": term,
            "mean": f"{term} (Auto-added)", # Placeholder description
            "ex": "",
            "exdoc": "",
            "link_int": f'<a href="{BASE_URL}{rel_path.replace(".md", ".html")}" target="_blank">{term}</a>',
            "vid": "",
            "ext_de": "",
            "ext_en": "",
            "title": term,
            "type": ""
        }
        
        # Add to data
        for cat in data['categories']:
            if cat['id'] == target_cat_id:
                cat['data'].append(new_entry)
                # Sort roughly by term to keep it tidy? optional.
                # cat['data'].sort(key=lambda x: x['term'])
                added_count += 1
                print(f"   -> Added to category '{cat.get('title', target_cat_id)}'")
                break
    
    if added_count > 0:
        with open(JSON_PATH, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=3, ensure_ascii=False)
        print(f"\nAdded {added_count} missing entries to {JSON_PATH}.")

if __name__ == '__main__':
    scan_and_add_missing()
