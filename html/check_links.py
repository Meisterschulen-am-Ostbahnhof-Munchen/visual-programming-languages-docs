import json
import os
import re
from pathlib import Path

# Configuration
JSON_PATH = os.path.join(os.path.dirname(__file__), 'Abkürzungen und Bedeutungen.json')
DOCS_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'docs'))
BASE_URL = 'https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/visual-programming-languages-docs/de/latest/'

def normalize_term(term):
    """Normalize term to compare with filename."""
    # Remove common prefixes/suffixes if needed, or take first word
    # E.g. "E_T_FF / Flip-Flop" -> "E_T_FF"
    return term.split(' ')[0].split('/')[0].strip()

def check_and_fix_links():
    print(f"Checking links in {JSON_PATH}...")
    
    with open(JSON_PATH, 'r', encoding='utf-8') as f:
        data = json.load(f)

    found_changes = False
    
    for category in data.get('categories', []):
        for entry in category.get('data', []):
            term = entry.get('term', '')
            link_int = entry.get('link_int', '')
            
            if not link_int:
                continue

            # Extract href from the anchor tag
            match = re.search(r'href="([^"]+)"', link_int)
            if not match:
                continue
            
            url = match.group(1)
            
            # We only check internal links pointing to our docs
            if url.startswith(BASE_URL):
                # Calculate expected local file path
                rel_url_path = url[len(BASE_URL):]
                # Remove anchor # if present
                rel_url_path = rel_url_path.split('#')[0]
                
                # Convert .html to .md
                rel_md_path = rel_url_path.replace('.html', '.md')
                
                abs_file_path = os.path.join(DOCS_ROOT, rel_md_path.replace('/', os.sep))
                
                # Check 1: Does the file exist?
                if not os.path.exists(abs_file_path):
                    print(f"[BROKEN] Term '{term}' points to missing file: {rel_md_path}")
                else:
                    # Check 2: Consistency check (Fixing AX_SR -> ASR_AX_SR issue)
                    filename = os.path.basename(abs_file_path)
                    filename_no_ext = os.path.splitext(filename)[0]
                    clean_term = normalize_term(term)
                    
                    # If the term doesn't match the filename significantly
                    if clean_term.lower() != filename_no_ext.lower():
                        # Check if a file matching the term exists in the same directory
                        expected_filename = clean_term + '.md'
                        expected_file_path = os.path.join(os.path.dirname(abs_file_path), expected_filename)
                        
                        if os.path.exists(expected_file_path):
                            print(f"[MISMATCH] Term '{term}' links to '{filename}' but '{expected_filename}' exists.")
                            
                            # Construct new correct URL
                            new_rel_url_path = os.path.dirname(rel_url_path) + '/' + clean_term + '.html'
                            if new_rel_url_path.startswith('/'):
                                new_rel_url_path = new_rel_url_path[1:]
                            
                            new_url = BASE_URL + new_rel_url_path
                            
                            # Update the entry
                            entry['link_int'] = link_int.replace(url, new_url)
                            print(f"   -> FIXED: Link updated to .../{clean_term}.html")
                            found_changes = True

    if found_changes:
        with open(JSON_PATH, 'w', encoding='utf-8') as f:
            # Using indent=3 to match existing style
            json.dump(data, f, indent=3, ensure_ascii=False)
        print("\nChanges saved to JSON file.")
    else:
        print("\nNo auto-fixable errors found.")

if __name__ == '__main__':
    check_and_fix_links()
