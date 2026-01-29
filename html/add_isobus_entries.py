import json
import os
import re

# Configuration
json_file_path = 'visual-programming-languages-docs/html/Abkürzungen und Bedeutungen.json'
isobus_objects_dir = 'ISOBUS-VT-Objects-docs/docs/isobus-objects'
base_url_int = 'https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/isobus-vt-objects-docs/de/latest/isobus-objects/'

def update_json():
    # Read JSON file
    try:
        with open(json_file_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
    except FileNotFoundError:
        print(f"Error: JSON file not found at {json_file_path}")
        return

    # Find or create category
    category_id = "cat_isobus_objects"
    category_title = "ISOBUS VT Objekte"
    
    target_category = None
    for cat in data.get('categories', []):
        if cat.get('id') == category_id:
            target_category = cat
            break
    
    if not target_category:
        print(f"Creating new category: {category_title}")
        target_category = {
            "id": category_id,
            "title": category_title,
            "data": []
        }
        data['categories'].append(target_category)
    else:
        print(f"Using existing category: {category_title}")

    # Process Markdown files
    if not os.path.exists(isobus_objects_dir):
        print(f"Error: Directory not found at {isobus_objects_dir}")
        return

    files = sorted(os.listdir(isobus_objects_dir))
    
    # Track existing terms to avoid duplicates
    existing_terms = {entry.get('term') for entry in target_category['data']}

    count_added = 0
    
    for filename in files:
        if not filename.endswith('.md') or filename == 'isobus-objects-index.md':
            continue

        file_path = os.path.join(isobus_objects_dir, filename)
        
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
        except Exception as e:
            print(f"Error reading {filename}: {e}")
            continue

        # Extract Title (First line)
        title_match = re.search(r'^#\s+(.+)$', content, re.MULTILINE)
        if not title_match:
            print(f"Skipping {filename}: No title found")
            continue
        
        full_title = title_match.group(1).strip()
        
        # Extract ID number from filename (ID-XX)
        id_match = re.match(r'ID-(\d+)', filename)
        obj_id = id_match.group(1) if id_match else ""

        # Extract External Link (German)
        # Looking for links to isobus-studio.com that are NOT /en/
        # Example: [ISOBUS Wiki - Working Set](https://isobus-studio.com/isobus-wiki/isobus-objectpool-objects/working-set)
        ext_link_de_match = re.search(r'\(https://isobus-studio\.com/isobus-wiki/([^\)]+)\)', content)
        
        ext_link_de_url = ""
        ext_link_en_url = ""
        
        if ext_link_de_match:
            ext_link_de_url = f"https://isobus-studio.com/isobus-wiki/{ext_link_de_match.group(1)}"
            ext_link_en_url = f"https://isobus-studio.com/en/isobus-wiki/{ext_link_de_match.group(1)}"
        else:
            # Try to find EN link if DE not found, though unlikely based on context
            ext_link_en_match = re.search(r'\(https://isobus-studio\.com/en/isobus-wiki/([^\)]+)\)', content)
            if ext_link_en_match:
                ext_link_en_url = f"https://isobus-studio.com/en/isobus-wiki/{ext_link_en_match.group(1)}"
                ext_link_de_url = f"https://isobus-studio.com/isobus-wiki/{ext_link_en_match.group(1)}"

        # Construct Internal Link
        html_filename = filename.replace('.md', '.html')
        link_int_url = f"{base_url_int}{html_filename}"

        # Construct Entry
        # Format links as HTML
        link_int_html = f'<a href="{link_int_url}" target="_blank">{full_title}</a>'
        ext_de_html = f'<a href="{ext_link_de_url}" target="_blank">Wiki (DE)</a>' if ext_link_de_url else ""
        ext_en_html = f'<a href="{ext_link_en_url}" target="_blank">Wiki (EN)</a>' if ext_link_en_url else ""

        entry = {
            "nr": obj_id,
            "term": full_title,
            "mean": full_title, # Using title as meaning for now
            "ex": "",
            "exdoc": "",
            "link_int": link_int_html,
            "vid": "",
            "ext_de": ext_de_html,
            "ext_en": ext_en_html,
            "title": full_title,
            "type": "isobus_object"
        }

        # Check for duplicates
        if full_title not in existing_terms:
            target_category['data'].append(entry)
            existing_terms.add(full_title)
            count_added += 1
            print(f"Added: {full_title}")
        else:
            print(f"Skipped (Duplicate): {full_title}")

    # Write JSON file
    if count_added > 0:
        try:
            with open(json_file_path, 'w', encoding='utf-8') as f:
                json.dump(data, f, indent=3, ensure_ascii=False)
            print(f"Successfully added {count_added} entries to {json_file_path}")
        except Exception as e:
            print(f"Error writing JSON: {e}")
    else:
        print("No new entries added.")

if __name__ == "__main__":
    update_json()
