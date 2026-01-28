import os
import re

DOCS_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'docs'))

# List of files we recently renamed (or significant ones to check)
# I'll scan recursively for the specific patterns we changed, mostly "Type.md", "Conv.md", "Adapter_*.md"
# and also check general structure.

def audit_files():
    print("Auditing Markdown files for Titles and Index entries...\n")
    
    files_to_check = []
    for root, _, filenames in os.walk(DOCS_ROOT):
        for filename in filenames:
            if filename.endswith('.md'):
                # Heuristic: Focus on the ones we likely touched or are structural
                if any(x in filename for x in ['_Type', '_Conv', '_Adapter', '_Index', '_Detail']):
                     files_to_check.append(os.path.join(root, filename))
    
    issues_found = []
    
    for file_path in files_to_check:
        rel_path = os.path.relpath(file_path, DOCS_ROOT).replace('\\', '/')
        
        with open(file_path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
            
        title = None
        has_index = False
        
        for line in lines:
            line = line.strip()
            if not title and line.startswith('# '):
                title = line[2:].strip()
            if '{index}' in line:
                has_index = True
        
        # Analyze
        if not title:
            issues_found.append(f"[NO TITLE] {rel_path}")
        elif not has_index:
            # Maybe okay for some, but index pages usually need it
            issues_found.append(f"[NO INDEX] {rel_path} (Title: '{title}')")
        else:
            # Check for ambiguity
            # Example: File is BOOL_Conv.md but title is "BOOL" -> Bad
            filename = os.path.basename(file_path)
            
            # Simple heuristic for potential mismatch
            if "_Conv" in filename and "Konvertierung" not in title and "Conversion" not in title:
                 # Check if title is too simple
                 if len(title.split()) < 2: 
                     issues_found.append(f"[WEAK TITLE] {rel_path} -> Filename '{filename}' vs Title '{title}'")
            
            if "_Type" in filename and "Datentyp" not in title and "Type" not in title:
                 if len(title.split()) < 2:
                     issues_found.append(f"[WEAK TITLE] {rel_path} -> Filename '{filename}' vs Title '{title}'")

    if issues_found:
        print(f"Found {len(issues_found)} potential issues:")
        for issue in sorted(issues_found):
            print(issue)
    else:
        print("No obvious issues found.")

if __name__ == '__main__':
    audit_files()
