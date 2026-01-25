import os
import re
from scan_for_exercises import scan_files, target_fbs, search_dirs

# Configuration
DOCS_ROOT = r"visual-programming-languages-docs/docs"
GLOSSARY_FILE = r"visual-programming-languages-docs/docs/Bibliotheken/ExternalLibraries/isobus/UT/Q/Q_ActiveMask.md"

def find_exercises_for_fb(fb_name):
    exercises = []
    for directory in search_dirs:
        if not os.path.exists(directory):
            print(f"Directory not found: {directory}")
            continue

        for filename in os.listdir(directory):
            if filename.endswith(".SUB"):
                filepath = os.path.join(directory, filename)
                exercise_name = os.path.splitext(filename)[0]
                
                try:
                    with open(filepath, 'r', encoding='utf-8') as f:
                        content = f.read()
                        pattern = fr'Type="[^\"]*([:_]){re.escape(fb_name)}"' # Corrected escaping for " inside f-string
                        pattern_exact = fr'Type="{re.escape(fb_name)}"' # Corrected escaping for " inside f-string
                        
                        if re.search(pattern, content) or re.search(pattern_exact, content):
                            if exercise_name not in exercises:
                                exercises.append(exercise_name)
                                    
                except Exception as e:
                    print(f"Error reading {filepath}: {e}")
    return exercises

def update_documentation(fb_name, exercises):
    if not exercises:
        print(f"No exercises found for {fb_name}")
        return

    doc_path = GLOSSARY_FILE
    if not os.path.exists(doc_path):
        print(f"Documentation file not found: {doc_path}")
        return

    print(f"Updating {doc_path} with exercises: {exercises}")
    
    with open(doc_path, 'r', encoding='utf-8') as f:
        content = f.read()

    # Section to add
    new_section = "\n## Zugehörige Übungen\n\n"
    for ex in exercises:
        # Assuming a standard path structure for exercises documentation
        # Adjust link path as needed. 
        # Exercise MD files seem to be in: docs/training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/
        # Relative link from Q_ActiveMask.md (in docs/Bibliotheken/ExternalLibraries/isobus/UT/Q/) 
        # to docs/training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_XXX.md
        
        # Calculate relative path
        target_path = f"../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/{ex}.md"
        new_section += f"* [{ex}]({target_path})\n"

    # Check if section already exists
    if "## Zugehörige Übungen" in content:
        # Replace existing section
        content = re.sub(r'## Zugehörige Übungen.*?(?=\n## |$)', new_section, content, flags=re.DOTALL)
    else:
        # Append before "## Fazit" or at the end
        if "## Fazit" in content:
            content = content.replace("## Fazit", f"{new_section}\n## Fazit")
        else:
            content += f"\n{new_section}"

    with open(doc_path, 'w', encoding='utf-8') as f:
        f.write(content)
    print("Documentation updated successfully.")

if __name__ == "__main__":
    fb_name = "Q_ActiveMask"
    exercises = find_exercises_for_fb(fb_name)
    update_documentation(fb_name, exercises)
