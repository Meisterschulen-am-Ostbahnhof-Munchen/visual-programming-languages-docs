import json
import os
import re

JSON_PATH = os.path.join(os.path.dirname(__file__), 'Abkuerzungen_und_Bedeutungen.json')
DOCS_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'docs'))
BASE_URL = 'https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/visual-programming-languages-docs/de/latest/'

def get_actual_title(rel_path):
    abs_path = os.path.join(DOCS_ROOT, rel_path.replace('/', os.sep))
    if not os.path.exists(abs_path):
        return None
    try:
        with open(abs_path, 'r', encoding='utf-8') as f:
            for line in f:
                if line.startswith('# '):
                    return line[2:].strip()
    except:
        pass
    return None

def cleanup_json():
    print(f"Cleaning up {JSON_PATH}...")
    
    with open(JSON_PATH, 'r', encoding='utf-8') as f:
        data = json.load(f)

    new_categories = []
    
    for category in data.get('categories', []):
        new_data = []
        seen_links = set()
        
        # Sort data to prioritize entries with "nr" or specific meanings over "Auto-added"
        sorted_entries = sorted(category.get('data', []), 
                                key=lambda x: (0 if x.get('nr') else 1, 
                                               0 if "(Auto-added)" not in x.get('mean', '') else 1))
        
        for entry in sorted_entries:
            link_int = entry.get('link_int', '')
            match = re.search(r'href="([^"]+)"', link_int)
            if not match:
                new_data.append(entry)
                continue
                
            url = match.group(1)
            if not url.startswith(BASE_URL):
                new_data.append(entry)
                continue
            
            rel_url = url[len(BASE_URL):].split('#')[0]
            rel_md = rel_url.replace('.html', '.md')
            abs_md = os.path.join(DOCS_ROOT, rel_md.replace('/', os.sep))
            
            # 1. Remove if link is dead and no Index variant exists
            if not os.path.exists(abs_md):
                # Try to find if it was renamed to _Index, _Type, etc.
                # Actually, our previous scripts should have fixed these.
                # If it's still missing, it's junk.
                print(f"[REMOVING] Dead link: {entry['term']} -> {rel_md}")
                continue

            # 2. Fix Term Mismatch
            # If the term is "BOOL" but it links to "AX2_BOOL_TO_X.html"
            filename = os.path.basename(rel_md)
            filename_no_ext = os.path.splitext(filename)[0]
            
            # Skip structural names for term comparison
            clean_filename = filename_no_ext.replace('_Index', '').replace('_Type', '').replace('_Conv', '').replace('_Adapter', '')
            
            if entry['term'] == "BOOL" and clean_filename != "BOOL":
                 # Correct the term to the actual filename
                 print(f"[FIX TERM] '{entry['term']}' -> '{filename_no_ext}' (Path: {rel_md})")
                 entry['term'] = filename_no_ext
                 # Update anchor text in link_int
                 entry['link_int'] = re.sub(r'>.*</a>', f'>{filename_no_ext}</a>', entry['link_int'])

            # 3. Deduplicate
            # If we already have an entry for this exact file in this category, skip
            if rel_md in seen_links:
                # print(f"[DUPE] Skipping redundant entry for {rel_md}")
                continue
            seen_links.add(rel_md)
            
            # 4. Update Title from file if it was "Auto-added"
            if "(Auto-added)" in entry.get('mean', ''):
                actual_title = get_actual_title(rel_md)
                if actual_title:
                    entry['title'] = actual_title
                    # Remove the "Auto-added" flag if we found a real title
                    entry['mean'] = actual_title

            new_data.append(entry)
            
        category['data'] = new_data
        new_categories.append(category)

    data['categories'] = new_categories
    
    with open(JSON_PATH, 'w', encoding='utf-8') as f:
        json.dump(data, f, indent=3, ensure_ascii=False)
    
    print("\nCleanup complete.")

if __name__ == '__main__':
    cleanup_json()
