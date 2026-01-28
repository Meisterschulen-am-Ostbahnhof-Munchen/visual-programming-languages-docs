import json
import os
import re

JSON_PATH = os.path.join(os.path.dirname(__file__), 'Abkürzungen und Bedeutungen.json')
DOCS_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'docs'))
BASE_URL = 'https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/visual-programming-languages-docs/de/latest/'

# We can re-use the RENAME_MAP from refine_structure.py ideally, but let's just use the logic of scanning.
# Or better: Scan for broken links again and try to find the new file.

def fix_json_final_refine():
    print(f"Refining JSON links in {JSON_PATH}...")
    
    with open(JSON_PATH, 'r', encoding='utf-8') as f:
        data = json.load(f)

    changes = 0
    
    for category in data.get('categories', []):
        for entry in category.get('data', []):
            link_int = entry.get('link_int', '')
            if not link_int: continue
            
            match = re.search(r'href="([^"]+)"', link_int)
            if not match: continue
            
            url = match.group(1)
            if not url.startswith(BASE_URL): continue
            
            rel_url = url[len(BASE_URL):]
            rel_url_clean = rel_url.split('#')[0]
            
            md_path = rel_url_clean.replace('.html', '.md')
            abs_path = os.path.join(DOCS_ROOT, md_path.replace('/', os.sep))
            
            if not os.path.exists(abs_path):
                # Try to find a file in the same directory that matches better
                dir_name = os.path.dirname(abs_path)
                if os.path.exists(dir_name):
                    # Look for candidate
                    candidates = []
                    for f in os.listdir(dir_name):
                        if f.endswith('.md'):
                            candidates.append(f)
                    
                    # Heuristic: if we look for BOOL_Index.md, but find BOOL_Type.md
                    base_search = os.path.basename(md_path).replace('_Index.md', '')
                    
                    best_match = None
                    for cand in candidates:
                        if base_search in cand and cand != base_search + '.md': # prefer derived names
                             best_match = cand
                             break
                    
                    if best_match:
                        new_rel = os.path.join(os.path.dirname(rel_url_clean), best_match.replace('.md', '.html')).replace('\\', '/')
                        new_full = BASE_URL + new_rel
                        entry['link_int'] = link_int.replace(url, new_full)
                        print(f"[FIX] '{entry['term']}': {rel_url_clean} -> {new_rel}")
                        changes += 1

    if changes > 0:
        with open(JSON_PATH, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=3, ensure_ascii=False)
        print(f"\nSaved {changes} changes.")
    else:
        print("\nNo changes made.")

if __name__ == '__main__':
    fix_json_final_refine()
