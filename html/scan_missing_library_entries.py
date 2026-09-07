import json
import os
import re

# The FB/Adapter reference (Bibliotheken/) lives in a separate repo since the
# split (see README.md). scan_missing_entries.py only ever walked this repo's
# own docs/ tree, so as that sibling repo grows, newly-added FB/adapter pages
# never make it into the glossary unless someone remembers to hand-curate
# them into edit_abkuerzungen.py. This does the same "diff docs tree against
# JSON, auto-add what's missing" pass scan_missing_entries.py does, just
# pointed at the sibling repo checkout (expects `ms-docs` repos to be
# siblings under the same parent directory, matching add_isobus_entries.py's
# convention) instead of this repo's own docs/.
JSON_PATH = os.path.join(os.path.dirname(__file__), 'Abkuerzungen_und_Bedeutungen.json')
LIB_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '4diac-library-reference-docs', 'docs', 'de'))
LIB_BASE_URL = 'https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/4diac-library-reference-docs-de/de/latest/'

IGNORE_FILES = {
    'index.md', 'README.md', 'conf.py', 'requirements.txt', 'make.bat', 'Makefile',
}


def get_linked_files_and_dirs(data):
    """Returns a set of normalized relative paths already linked in the JSON
    (pointing at LIB_BASE_URL), and a map of dir -> category_id histogram."""
    linked_files = set()
    dir_category_map = {}

    for category in data.get('categories', []):
        cat_id = category.get('id')
        for entry in category.get('data', []):
            link_int = entry.get('link_int', '')
            if not link_int:
                continue

            match = re.search(r'href="([^"]+)"', link_int)
            if match:
                url = match.group(1)
                if url.startswith(LIB_BASE_URL):
                    rel_path = url[len(LIB_BASE_URL):].split('#')[0]
                    if rel_path.endswith('/'):
                        rel_path = rel_path[:-1] + '.md'
                    elif '.html' in rel_path:
                        rel_path = rel_path.replace('.html', '.md')
                    linked_files.add(rel_path)

                    dir_path = os.path.dirname(rel_path)
                    if dir_path not in dir_category_map:
                        dir_category_map[dir_path] = {}
                    dir_category_map[dir_path][cat_id] = dir_category_map[dir_path].get(cat_id, 0) + 1

    return linked_files, dir_category_map


def predict_category(file_rel_path, dir_category_map):
    """Guess category based on siblings already linked from the same directory."""
    dir_path = os.path.dirname(file_rel_path.replace(os.sep, '/'))
    if dir_path in dir_category_map:
        cats = dir_category_map[dir_path]
        return max(cats, key=cats.get)
    return "cat_types"


def scan_and_add_missing():
    if not os.path.isdir(LIB_ROOT):
        print(f"Error: sibling repo not found at {LIB_ROOT}")
        return

    print(f"Scanning for markdown files in {LIB_ROOT} not in JSON...")

    with open(JSON_PATH, 'r', encoding='utf-8') as f:
        data = json.load(f)

    linked_files, dir_category_map = get_linked_files_and_dirs(data)

    missing_files = []
    for root, dirs, files in os.walk(LIB_ROOT):
        dirs[:] = [d for d in dirs if not d.startswith('.')]

        for file in files:
            if not file.endswith('.md') or file in IGNORE_FILES:
                continue

            abs_path = os.path.join(root, file)
            rel_path_os = os.path.relpath(abs_path, LIB_ROOT)
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

        if term.lower() in ['index', 'readme', 'intro']:
            continue

        target_cat_id = predict_category(rel_path, dir_category_map)

        new_entry = {
            "nr": "",
            "term": term,
            "mean": f"{term} (Auto-added)",
            "ex": "",
            "exdoc": "",
            "link_int": f'<a href="{LIB_BASE_URL}{rel_path.replace(".md", "/")}" target="_blank">{term}</a>',
            "vid": "",
            "ext_de": "",
            "ext_en": "",
            "title": term,
            "type": ""
        }

        for cat in data['categories']:
            if cat['id'] == target_cat_id:
                cat['data'].append(new_entry)
                added_count += 1
                break

    if added_count > 0:
        with open(JSON_PATH, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=3, ensure_ascii=False)
        print(f"\nAdded {added_count} missing entries to {JSON_PATH}.")


if __name__ == '__main__':
    scan_and_add_missing()
