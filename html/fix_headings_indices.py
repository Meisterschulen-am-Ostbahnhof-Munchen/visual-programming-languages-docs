import os

DOCS_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'docs'))

# Updates to perform
# Path (relative to docs) -> { 'title': New Title (optional), 'add_index': True/False }
UPDATES = {
    # Adapter Conversions
    'Bibliotheken/ExternalLibraries/adapter/conversion/unidirectional/BOOL/BOOL_Adapter_Conv.md': {
        'title': 'Unidirectional BOOL Adapter Conversion'
    },
    'Bibliotheken/ExternalLibraries/adapter/conversion/unidirectional/BYTE/BYTE_Adapter_Conv.md': {
        'title': 'Unidirectional BYTE Adapter Conversion'
    },
    'Bibliotheken/ExternalLibraries/adapter/conversion/unidirectional/EVENT/EVENT_Adapter_Conv.md': {
        'title': 'Unidirectional EVENT Adapter Conversion'
    },
    
    # LogiBUS Conversions
    'Bibliotheken/ExternalLibraries/logiBUS/utils/conversion/str/converting/BOOL/BOOL_LogiBUS_Conv.md': {
        'title': 'LogiBUS BOOL Conversion'
    },
    'Bibliotheken/ExternalLibraries/logiBUS/utils/conversion/str/converting/BYTE/BYTE_LogiBUS_Conv.md': {
        'title': 'LogiBUS BYTE Conversion'
    },
    'Bibliotheken/ExternalLibraries/logiBUS/utils/conversion/str/types/BOOL/BOOL_LogiBUS_Type.md': {
        'title': 'LogiBUS BOOL Types'
    },
    'Bibliotheken/ExternalLibraries/logiBUS/utils/conversion/str/types/BYTE/BYTE_LogiBUS_Type.md': {
        'title': 'LogiBUS BYTE Types'
    },

    # Missing Indices
    'Bibliotheken/ExternalLibraries/isobus/pgn/pgn_Index.md': {
        'add_index': 'PGN (Parameter Group Number)'
    },
    'Bibliotheken/Vergleich/IEC61131_3/IEC61131_3_Index.md': {
        'add_index': 'IEC 61131-3 Vergleich'
    },
    'Bibliotheken/Vergleich/Vergleich_Index.md': {
        'add_index': 'Normenvergleich'
    }
}

def fix_files():
    print("Fixing titles and indices...")
    
    for rel_path, actions in UPDATES.items():
        abs_path = os.path.join(DOCS_ROOT, rel_path.replace('/', os.sep))
        
        if not os.path.exists(abs_path):
            print(f"File not found: {rel_path}")
            continue
            
        with open(abs_path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
            
        new_lines = []
        title_updated = False
        index_added = False
        
        # Scan current state
        has_index = any('{index}' in l for l in lines)
        
        for i, line in enumerate(lines):
            stripped = line.strip()
            
            # Update Title
            if 'title' in actions and not title_updated and stripped.startswith('# '):
                print(f"Updating title in {rel_path}: '{stripped}' -> '# {actions['title']}'")
                new_lines.append(f"# {actions['title']}\n")
                title_updated = True
                continue
            
            new_lines.append(line)
            
            # Add Index after title if missing
            if 'add_index' in actions and not has_index and not index_added and stripped.startswith('# '):
                # If we just updated title, the 'line' variable is the OLD title, but new_lines has the NEW title.
                # If we didn't update title, 'line' is current title.
                # In both cases, we append the index block now.
                term = actions['add_index']
                print(f"Adding index to {rel_path}: '{term}'")
                new_lines.append(f"\n```{{index}} single: {term}\n```\n")
                index_added = True

        with open(abs_path, 'w', encoding='utf-8') as f:
            f.writelines(new_lines)

if __name__ == '__main__':
    fix_files()
