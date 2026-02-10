import json
import os
import re

JSON_PATH = os.path.join(os.path.dirname(__file__), 'Abkuerzungen_und_Bedeutungen.json')
DOCS_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'docs'))
BASE_URL = 'https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/visual-programming-languages-docs/de/latest/'

def fix_json():
    print(f"Fixing JSON links in {JSON_PATH}...")
    
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
            # remove anchor
            rel_url_clean = rel_url.split('#')[0]
            
            # Case 1: Link ends in _Detail.html
            if rel_url_clean.endswith('_Detail.html'):
                # Try replacing with .html (Content)
                new_rel_url = rel_url_clean.replace('_Detail.html', '.html')
                
                # Check if file exists
                md_path = new_rel_url.replace('.html', '.md')
                abs_path = os.path.join(DOCS_ROOT, md_path.replace('/', os.sep))
                
                if os.path.exists(abs_path):
                    new_full_url = BASE_URL + new_rel_url
                    entry['link_int'] = link_int.replace(url, new_full_url)
                    print(f"[FIX] '{entry['term']}': _Detail.html -> .html ({new_rel_url})")
                    changes += 1
                    continue
            
            # Case 2: Link points to X.html, but X.md missing, and X_Index.md exists
            # (check_links.py handles this, but maybe missed some?)
            # check_links handled it.
            
            # Case 3: Link points to missing file, try to find *any* matching Index or Content?
            # Let's verify broken links.
            
            md_path_orig = rel_url_clean.replace('.html', '.md')
            abs_path_orig = os.path.join(DOCS_ROOT, md_path_orig.replace('/', os.sep))
            
            if not os.path.exists(abs_path_orig):
                # Try _Index
                index_path = abs_path_orig.replace('.md', '_Index.md')
                if os.path.exists(index_path):
                     new_rel = rel_url_clean.replace('.html', '_Index.html')
                     new_full = BASE_URL + new_rel
                     entry['link_int'] = link_int.replace(url, new_full)
                     print(f"[FIX] '{entry['term']}': Missing -> _Index.html ({new_rel})")
                     changes += 1
    
    if changes > 0:
        with open(JSON_PATH, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=3, ensure_ascii=False)
        print(f"\nSaved {changes} changes.")
    else:
        print("\nNo changes made.")

if __name__ == '__main__':
    fix_json()
