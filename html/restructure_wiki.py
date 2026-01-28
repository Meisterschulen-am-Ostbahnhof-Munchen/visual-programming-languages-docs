import os
import re
import shutil

DOCS_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'docs'))

def has_toctree(file_path):
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
            return '```{toctree}' in content or '.. toctree::' in content
    except:
        return False

def get_all_md_files():
    files = []
    for root, _, filenames in os.walk(DOCS_ROOT):
        for filename in filenames:
            if filename.endswith('.md'):
                files.append(os.path.join(root, filename))
    return files

def update_references(file_path, replacements):
    """
    replacements: dict of old_rel_path -> new_rel_path (relative to DOCS_ROOT, using forward slashes)
    file_path: absolute path to the file to update
    """
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    original_content = content
    file_dir = os.path.dirname(file_path)
    
    # 1. Update toctree entries
    # Heuristic: lines inside ```{toctree} blocks
    lines = content.split('\n')
    in_toctree = False
    new_lines = []
    
    for line in lines:
        if '```{toctree}' in line or '.. toctree::' in line:
            in_toctree = True
            new_lines.append(line)
            continue
        if '```' in line and in_toctree:
            in_toctree = False
            new_lines.append(line)
            continue
            
        if in_toctree and line.strip() and not line.strip().startswith(':'):
            # This is a toctree entry
            entry = line.strip()
            # Resolve entry to absolute path
            # Entry is relative to current file
            entry_path = os.path.join(file_dir, entry)
            # Add .md if missing for check (Sphinx allows omitting extension)
            if not entry_path.endswith('.md'):
                entry_path_md = entry_path + '.md'
            else:
                entry_path_md = entry_path
            
            # Normalize
            entry_path_md = os.path.normpath(entry_path_md)
            
            # Check if this path corresponds to something we renamed
            # We need to check against our 'renames' logic. 
            # But here we pass 'replacements' which are old_rel -> new_rel.
            
            rel_entry = os.path.relpath(entry_path_md, DOCS_ROOT).replace('\\', '/')
            
            # Check exact match
            if rel_entry in replacements:
                new_rel = replacements[rel_entry]
                # Convert back to relative to current file
                new_abs = os.path.join(DOCS_ROOT, new_rel.replace('/', os.sep))
                new_entry_rel = os.path.relpath(new_abs, file_dir).replace('\\', '/')
                # Remove .md extension if it wasn't there before?
                # Usually best to keep it clean. Sphinx allows omitting. 
                # Let's drop .md if the original didn't have it
                if not entry.endswith('.md'):
                    new_entry_rel = os.path.splitext(new_entry_rel)[0]
                
                # Maintain indentation
                indent = line[:len(line) - len(line.lstrip())]
                new_lines.append(indent + new_entry_rel)
            else:
                # Check for "Detail" replacement logic which might be implicit?
                # If we had "BOOL_Detail" and now it is "BOOL", the dict handles it.
                new_lines.append(line)
        else:
            # 2. Update standard links [Text](path)
            # Regex to find links
            # This is tricky per line because multiple links.
            # We'll use a regex replacement on the whole content later, or handle line by line.
            # Let's do line by line.
            
            # Pattern: [text](link)
            # We want to capture group 2 (link)
            def replace_link(match):
                text = match.group(1)
                link = match.group(2)
                
                # Ignore external links
                if link.startswith('http') or link.startswith('mailto:'):
                    return match.group(0)
                
                # Ignore anchors only
                if link.startswith('#'):
                    return match.group(0)
                
                anchor = ""
                if '#' in link:
                    link, anchor = link.split('#', 1)
                    anchor = '#' + anchor
                
                # Resolve link absolute
                link_abs = os.path.join(file_dir, link)
                if not link_abs.endswith('.md'):
                     # If it links to a folder or html, infer MD?
                     # Let's assume .md for now if missing, mostly works in this repo
                     if not os.path.exists(link_abs) and os.path.exists(link_abs + '.md'):
                         link_abs += '.md'
                
                link_norm = os.path.normpath(link_abs)
                rel_link = os.path.relpath(link_norm, DOCS_ROOT).replace('\\', '/')
                
                if rel_link in replacements:
                    new_rel = replacements[rel_link]
                    new_abs = os.path.join(DOCS_ROOT, new_rel.replace('/', os.sep))
                    new_link_rel = os.path.relpath(new_abs, file_dir).replace('\\', '/')
                    return f"[{text}]({new_link_rel}{anchor})"
                
                return match.group(0)

            new_line = re.sub(r'\[([^\]]+)\]\(([^)]+)\)', replace_link, line)
            new_lines.append(new_line)

    final_content = '\n'.join(new_lines)
    
    if final_content != original_content:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(final_content)
        return True
    return False

def main():
    print("Scanning documentation structure...")
    files = get_all_md_files()
    
    # Identify renames
    # Map: old_rel_path -> new_rel_path
    renames = {}
    
    # Store physical moves to perform: (src, dst)
    moves = []
    
    processed_dirs = set()
    
    # Sort files to ensure deterministic processing?
    files.sort()
    
    for file_path in files:
        if file_path in [
            os.path.join(DOCS_ROOT, 'index.md'),
            os.path.join(DOCS_ROOT, 'Welcome.md')
        ]:
            continue
            
        dir_path = os.path.dirname(file_path)
        filename = os.path.basename(file_path)
        name_no_ext = os.path.splitext(filename)[0]
        
        # Skip if we already processed this directory (optimization)
        # Actually we scan per file.
        
        # Check if this file acts as a ToC
        if has_toctree(file_path):
            # Check for the pattern: Name.md (ToC) + Name_Detail.md (Content)
            detail_filename = f"{name_no_ext}_Detail.md"
            detail_path = os.path.join(dir_path, detail_filename)
            
            rel_path = os.path.relpath(file_path, DOCS_ROOT).replace('\\', '/')
            
            if os.path.exists(detail_path):
                # Pattern A: Pair
                print(f"[PAIR] Found ToC '{filename}' and Content '{detail_filename}' in {os.path.relpath(dir_path, DOCS_ROOT)}")
                
                rel_detail_path = os.path.relpath(detail_path, DOCS_ROOT).replace('\\', '/')
                
                new_index_name = f"{name_no_ext}_Index.md"
                new_index_path = os.path.join(dir_path, new_index_name)
                new_index_rel = os.path.relpath(new_index_path, DOCS_ROOT).replace('\\', '/')
                
                # Logic:
                # 1. ToC File moves to _Index
                moves.append((file_path, new_index_path))
                renames[rel_path] = new_index_rel # Parent ToCs need to point here
                
                # 2. Detail File moves to Original Name
                # Wait, we can't move Detail to Original Name immediately if Original Name still exists.
                # We need a temp step or careful ordering. 
                # Since we are generating a list, we can handle this.
                moves.append((detail_path, file_path))
                
                # Mapping for links:
                # - Links to Detail should now go to Name.md
                renames[rel_detail_path] = rel_path
                
                # - Links to Name.md (Old ToC):
                #   - If it was a ToC reference (parent), it should go to Name_Index.md (handled by renames[rel_path])
                #   - If it was a Content reference? Currently Name.md IS the ToC. 
                #     Usually links to Name.md in text meant the "Concept". 
                #     Now Name.md IS the concept (Content). 
                #     So textual links to Name.md are actually FINE staying as Name.md!
                #     BUT `renames[rel_path] = new_index_rel` will rewrite them to _Index.md.
                #     This is the dilemma. 
                #     We need to distinguish context. 
                #     However, `update_references` uses regex `[...]` for links and `toctree` parsing for structure.
                #     We can provide TWO maps or handle logic inside `update_references`.
                
                # Let's refine the maps.
                # We have `toc_renames` and `link_renames`.
                
            else:
                # Pattern B: Solo ToC
                # Only rename if it seems to be the "Folder Index".
                # User guidance: "wir sollten alle Files die ein Inhaltsverzeichnis Enthalten ... so kennzeichnen"
                print(f"[SOLO] Found ToC '{filename}' in {os.path.relpath(dir_path, DOCS_ROOT)}")
                
                new_index_name = f"{name_no_ext}_Index.md"
                new_index_path = os.path.join(dir_path, new_index_name)
                new_index_rel = os.path.relpath(new_index_path, DOCS_ROOT).replace('\\', '/')
                
                moves.append((file_path, new_index_path))
                renames[rel_path] = new_index_rel

    # We need to differentiate replacements for ToC entries vs hyperlinks.
    # Case Pair:
    #   Old: Name.md (ToC), Name_Detail.md (Content)
    #   New: Name_Index.md (ToC), Name.md (Content)
    #   
    #   Parent ToC: points to Name.md -> Must update to Name_Index.md
    #   Text Link to Name.md: likely wants Concept -> Should stay Name.md (which is now Content).
    #   Text Link to Name_Detail.md: -> Should update to Name.md.
    
    #   Problem: `renames[Name.md] = Name_Index.md` will force Text Links to Name_Index.md.
    #   Solution: We need a `link_replacements` dict and a `toctree_replacements` dict.
    
    toc_replacements = {}
    link_replacements = {}
    
    for old_rel, new_rel in renames.items():
        # Default behavior: Rename applies to both
        toc_replacements[old_rel] = new_rel
        link_replacements[old_rel] = new_rel
    
    # Fix Pair Logic overrides
    # Reread files to find pairs again? Or reuse logic.
    # Let's iterate `moves` to deduce overrides.
    
    # We need to know which move corresponds to a "Detail -> Name" swap.
    # In the loop above:
    #   moves.append((detail_path, file_path)) -> This overwrites file_path (old ToC location).
    
    # Let's reconstruct the specific overrides.
    for root, _, filenames in os.walk(DOCS_ROOT):
        for filename in filenames:
            if not filename.endswith('.md'): continue
            file_path = os.path.join(root, filename)
            
            # Same checks
            if has_toctree(file_path):
                name_no_ext = os.path.splitext(filename)[0]
                detail_filename = f"{name_no_ext}_Detail.md"
                detail_path = os.path.join(root, detail_filename)
                
                rel_path = os.path.relpath(file_path, DOCS_ROOT).replace('\\', '/')
                
                if os.path.exists(detail_path):
                    # It is a PAIR
                    rel_detail = os.path.relpath(detail_path, DOCS_ROOT).replace('\\', '/')
                    
                    new_index_rel = rel_path.replace('.md', '_Index.md')
                    
                    # 1. Parent ToC pointing to Old Name should go to Index
                    toc_replacements[rel_path] = new_index_rel
                    
                    # 2. Text Link pointing to Old Name...
                    # Previously pointed to ToC. Now `rel_path` holds Content.
                    # User wants "BOOL" to point to Content.
                    # So Text Link to `rel_path` should NOT change path!
                    # Remove from link_replacements if present
                    if rel_path in link_replacements:
                        del link_replacements[rel_path]
                        
                    # 3. Text Link pointing to Detail
                    # Now Detail is moved to `rel_path`.
                    link_replacements[rel_detail] = rel_path
                    toc_replacements[rel_detail] = rel_path # Just in case
                    
                    # 4. The Internal ToC in the NEW Index file (old Name.md)
                    # It pointed to `Name_Detail`. Now needs to point to `Name`.
                    # This is handled by `toc_replacements[rel_detail] = rel_path`.
                    
                else:
                    # SOLO
                    # toc_replacements[rel_path] = rel_path_Index (already set)
                    # link_replacements[rel_path] = rel_path_Index (already set)
                    pass

    # Execute Moves
    print(f"Executing {len(moves)} file moves...")
    
    # We must be careful about order. Moving A->B, then C->A.
    # Use temporary files if needed?
    # Simple strategy: Rename all sources to temporary names, then to destinations.
    # Or separate into two lists: 
    # 1. ToC -> Index (Safe, new name)
    # 2. Detail -> Name (Target matches Source of step 1).
    
    # Let's process moves:
    # Filter moves:
    # - Renaming ToC to _Index (always safe, new name usually doesn't exist)
    # - Renaming Detail to Name (Target 'Name' must be free first)
    
    toc_moves = []
    detail_moves = []
    
    for src, dst in moves:
        if src.endswith('_Detail.md'):
            detail_moves.append((src, dst))
        else:
            toc_moves.append((src, dst))
            
    # Step 1: Move ToCs to _Index
    for src, dst in toc_moves:
        print(f"Moving {os.path.basename(src)} -> {os.path.basename(dst)}")
        shutil.move(src, dst)
        
    # Step 2: Move Details to original names
    for src, dst in detail_moves:
        print(f"Moving {os.path.basename(src)} -> {os.path.basename(dst)}")
        shutil.move(src, dst)

    # Step 3: Update References
    print("Updating references in all files...")
    all_files = get_all_md_files() # Re-scan as names changed
    
    for file_path in all_files:
        # We need a custom update function that uses the two dicts
        update_references_split(file_path, toc_replacements, link_replacements)

    print("Restructuring complete.")

def update_references_split(file_path, toc_replacements, link_replacements):
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    file_dir = os.path.dirname(file_path)
    lines = content.split('\n')
    in_toctree = False
    new_lines = []
    
    for line in lines:
        if '```{toctree}' in line or '.. toctree::' in line:
            in_toctree = True
            new_lines.append(line)
            continue
        if '```' in line and in_toctree:
            in_toctree = False
            new_lines.append(line)
            continue
            
        if in_toctree and line.strip() and not line.strip().startswith(':'):
            # ToC Entry
            entry = line.strip()
            
            # Resolve entry
            entry_path = os.path.join(file_dir, entry)
            if not entry_path.endswith('.md'): entry_path += '.md'
            entry_path = os.path.normpath(entry_path)
            
            rel_entry = os.path.relpath(entry_path, DOCS_ROOT).replace('\\', '/')
            
            if rel_entry in toc_replacements:
                new_rel = toc_replacements[rel_entry]
                new_abs = os.path.join(DOCS_ROOT, new_rel.replace('/', os.sep))
                new_entry_rel = os.path.relpath(new_abs, file_dir).replace('\\', '/')
                if not entry.endswith('.md'):
                    new_entry_rel = os.path.splitext(new_entry_rel)[0]
                
                indent = line[:len(line) - len(line.lstrip())]
                new_lines.append(indent + new_entry_rel)
            else:
                new_lines.append(line)
        else:
            # Link Replacement
            def replace_link(match):
                text = match.group(1)
                link = match.group(2)
                
                if link.startswith('http') or link.startswith('mailto:') or link.startswith('#'):
                    return match.group(0)
                
                anchor = ""
                if '#' in link:
                    link, anchor = link.split('#', 1)
                    anchor = '#' + anchor
                
                link_abs = os.path.join(file_dir, link)
                if not link_abs.endswith('.md') and not link_abs.endswith('.html'):
                     if not os.path.exists(link_abs) and os.path.exists(link_abs + '.md'):
                         link_abs += '.md'
                
                # Check for .md links
                if link_abs.endswith('.md'):
                    link_norm = os.path.normpath(link_abs)
                    rel_link = os.path.relpath(link_norm, DOCS_ROOT).replace('\\', '/')
                    
                    if rel_link in link_replacements:
                        new_rel = link_replacements[rel_link]
                        new_abs = os.path.join(DOCS_ROOT, new_rel.replace('/', os.sep))
                        new_link_rel = os.path.relpath(new_abs, file_dir).replace('\\', '/')
                        return f"[{text}]({new_link_rel}{anchor})"
                
                return match.group(0)

            new_line = re.sub(r'\[([^\]]+)\]\(([^)]+)\)', replace_link, line)
            new_lines.append(new_line)

    final_content = '\n'.join(new_lines)
    if final_content != content:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(final_content)

if __name__ == '__main__':
    main()
