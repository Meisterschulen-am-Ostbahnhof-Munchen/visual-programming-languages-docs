import os
import re
from generate_glossary_docs import scan_for_all_exercises

# Configuration
DOCS_ROOT = r"visual-programming-languages-docs/docs"

def update_all_docs():
    print("Scanning for all exercises...")
    # Get usage map: {FB_NAME: [EX1, EX2, ...]}}
    usage = scan_for_all_exercises()
    
    print(f"Found {len(usage)} function blocks used in exercises.")

    # Traverse all MD files in docs
    for root, dirs, files in os.walk(DOCS_ROOT):
        for file in files:
            if file.endswith(".md"):
                fb_name = os.path.splitext(file)[0]
                
                # Check if this FB is used in any exercises
                if fb_name in usage:
                    exercises = usage[fb_name]
                    doc_path = os.path.join(root, file)
                    
                    update_single_doc(doc_path, fb_name, exercises)

def update_single_doc(doc_path, fb_name, exercises):
    # Calculate relative path base for links
    # Target structure: ../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/{ex}.md
    # We need to compute the relative path from doc_path to the Uebungen_doc folder.
    
    # Since the "depth" of doc_path varies, we can't hardcode "../../../".
    # Instead, we assume the target is always at a fixed location relative to DOCS_ROOT.
    
    # Absolute path of docs root
    abs_docs_root = os.path.abspath(DOCS_ROOT)
    # Absolute path of current doc file
    abs_doc_path = os.path.abspath(doc_path)
    # Absolute path of doc directory
    abs_doc_dir = os.path.dirname(abs_doc_path)
    
    with open(doc_path, 'r', encoding='utf-8') as f:
        content = f.read()

    new_section = "\n## Zugehörige Übungen\n\n"
    
    for ex in sorted(exercises):
        # Determine subfolder based on exercise name convention
        subfolder = "test_B"
        if "_AX" in ex:
            subfolder = "test_AX"
            
        # Target path relative to DOCS_ROOT
        # docs/training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_XXX.md
        target_abs_path = os.path.join(abs_docs_root, f"training1/Ventilsteuerung/4diacIDE-workspace/{subfolder}/Uebungen_doc/{ex}.md")
        
        # Calculate relative path from current doc to target
        try:
            rel_link = os.path.relpath(target_abs_path, abs_doc_dir)
            # Normalize to forward slashes for markdown
            rel_link = rel_link.replace(os.sep, '/')
            
            new_section += f"* [{ex}]({rel_link})\n"
        except ValueError:
            print(f"Error calculating path for {ex} in {doc_path}")
            continue

    # Update content
    if "## Zugehörige Übungen" in content:
        # Replace existing section
        # Regex to match from header until next header or end of string
        content = re.sub(r'## Zugehörige Übungen.*?(?=\n## |$)', new_section, content, flags=re.DOTALL)
        print(f"Updated: {fb_name}")
    else:
        # Append before "## Fazit" or at the end
        if "## Fazit" in content:
            content = content.replace("## Fazit", f"{new_section}\n## Fazit")
            print(f"Inserted: {fb_name} (before Fazit)")
        else:
            content += f"\n{new_section}"
            print(f"Appended: {fb_name}")

    with open(doc_path, 'w', encoding='utf-8') as f:
        f.write(content)

if __name__ == "__main__":
    update_all_docs()
