import os
import re
import sys
import yaml
import hashlib
import urllib.request
from unittest.mock import MagicMock

# Mock weasyprint before importing mkdocs to avoid GObject/GTK loading errors on Windows and CI
sys.modules['weasyprint'] = MagicMock()

import mkdocs.config
import mkdocs.config.config_options
# No-op validation to allow docs_dir: . and site_dir inside docs_dir during merge
mkdocs.config.config_options.DocsDir.post_validation = lambda self, config, key_name: None
mkdocs.config.config_options.SiteDir.post_validation = lambda self, config, key_name: None

from mkdocs.structure.files import get_files
from mkdocs.structure.nav import get_navigation

def clean_id(path):
    # Convert path like "Allgemeines/Zahlen.md" to a clean anchor id "allgemeines-zahlen"
    p = path.replace('\\', '/').lower()
    if p.endswith('.md'):
        p = p[:-3]
    # Replace anything that's not alphanumeric, hyphen or underscore with hyphen
    p = re.sub(r'[^a-z0-9/_-]', '', p)
    p = p.replace('/', '-').replace('_', '-')
    # Collapse multiple hyphens
    p = re.sub(r'-+', '-', p)
    return p.strip('-')

def build_path_to_id_map(pages):
    path_to_id = {}
    for page in pages:
        src = page.file.src_path # relative to docs/ e.g. "4diac/index.md"
        path_to_id[src.replace('\\', '/')] = clean_id(src)
    return path_to_id

def download_remote_image(url, docs_dir):
    # Create downloaded directory under docs/img/downloaded
    downloaded_dir = os.path.join(docs_dir, 'img', 'downloaded')
    os.makedirs(downloaded_dir, exist_ok=True)
    
    # Generate unique local filename based on URL hash
    url_hash = hashlib.md5(url.encode('utf-8')).hexdigest()
    
    content_type_map = {
        'image/jpeg': '.jpg',
        'image/jpg': '.jpg',
        'image/png': '.png',
        'image/gif': '.gif',
        'image/svg+xml': '.svg',
        'image/webp': '.webp',
        'image/bmp': '.bmp',
    }
    
    # Check if a file with this hash and any known extension already exists
    for ext in ['.png', '.jpg', '.jpeg', '.gif', '.svg', '.webp', '.bmp']:
        local_path = os.path.join(downloaded_dir, f"{url_hash}{ext}")
        if os.path.exists(local_path):
            return f"img/downloaded/{url_hash}{ext}"
            
    try:
        req = urllib.request.Request(
            url, 
            headers={'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'}
        )
        print(f"Downloading remote image: {url}")
        with urllib.request.urlopen(req, timeout=15) as response:
            content_type = response.info().get_content_type()
            ext = None
            if content_type:
                ext = content_type_map.get(content_type.lower())
                
            if not ext:
                clean_url = url.split('?')[0]
                url_ext = os.path.splitext(clean_url)[1].lower()
                if url_ext and len(url_ext) <= 5:
                    ext = url_ext
                else:
                    ext = '.png'
                    
            local_name = f"{url_hash}{ext}"
            local_path = os.path.join(downloaded_dir, local_name)
            
            with open(local_path, 'wb') as out_file:
                out_file.write(response.read())
                
            return f"img/downloaded/{local_name}"
    except Exception as e:
        print(f"Error downloading {url}: {e}")
        # Write a placeholder black 1x1 PNG if download fails
        placeholder_path = os.path.join(downloaded_dir, 'placeholder.png')
        if not os.path.exists(placeholder_path):
            minimal_png = bytes([
                0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 
                0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 
                0x08, 0x02, 0x00, 0x00, 0x00, 0x90, 0x77, 0x53, 0xDE, 0x00, 0x00, 0x00, 
                0x0C, 0x49, 0x44, 0x41, 0x54, 0x08, 0xD7, 0x63, 0xF8, 0xFF, 0xFF, 0x3F, 
                0x00, 0x05, 0xFE, 0x02, 0xFE, 0xDC, 0x44, 0x74, 0x8E, 0x00, 0x00, 0x00, 
                0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82
            ])
            try:
                with open(placeholder_path, 'wb') as f:
                    f.write(minimal_png)
            except Exception as write_err:
                print(f"Error writing placeholder image: {write_err}")
        return "img/downloaded/placeholder.png"


def rewrite_content(content, file_src_path, path_to_id, docs_dir):
    # file_src_path is e.g. "4diac/Installation-4diac.md"
    file_dir = os.path.dirname(file_src_path).replace('\\', '/')
    
    # Rewrite images and links
    # 1. Markdown syntax: ![alt](path) or [text](path)
    def replace_url(match):
        prefix = match.group(1) # "![" or "["
        text = match.group(2)
        url_part = match.group(3).strip()
        
        # Split anchor
        if '#' in url_part:
            url_path, anchor = url_part.split('#', 1)
        else:
            url_path, anchor = url_part, ''
            
        # Safeguard: demote image prefix if target does not look like an image
        if prefix == '![':
            is_remote = url_path.startswith(('http://', 'https://'))
            if not is_remote:
                image_extensions = ('.png', '.jpg', '.jpeg', '.gif', '.svg', '.bmp', '.webp', '.pdf')
                if not url_path.lower().endswith(image_extensions):
                    prefix = '['

        if not url_path and not anchor:
            # Empty image reference or link!
            # If it's an image, replace it with empty string to avoid rendering in Typst
            if prefix == '![':
                return ""
            else:
                return f"[{text}]"
                
        if not url_path and anchor:
            # Local anchor link in same file
            return f"{prefix}{text}](#{anchor.lower()})"
            
        # Check for remote URL
        is_remote = url_path.startswith(('http://', 'https://'))
        
        if is_remote:
            if prefix == '![':
                # It is an image! Download it.
                local_rel_path = download_remote_image(url_path, docs_dir)
                anchor_str = f"#{anchor}" if anchor else ""
                dest = f"{local_rel_path}{anchor_str}"
                if ' ' in dest and not (dest.startswith('<') and dest.endswith('>')):
                    dest = f"<{dest}>"
                return f"{prefix}{text}]({dest})"
            else:
                # It is a normal link, keep it remote
                dest = url_part
                if ' ' in dest and not (dest.startswith('<') and dest.endswith('>')):
                    dest = f"<{dest}>"
                return f"{prefix}{text}]({dest})"
                
        if url_path.startswith(('mailto:', 'ftp:', 'www.', '/')):
            dest = url_part
            if ' ' in dest and not (dest.startswith('<') and dest.endswith('>')):
                dest = f"<{dest}>"
            return f"{prefix}{text}]({dest})"
            
        # Target path relative to docs/
        target_src = os.path.normpath(os.path.join(file_dir, url_path)).replace('\\', '/')
        
        # Check if the target is a markdown file
        no_ext = target_src[:-3] if target_src.endswith('.md') else target_src
        target_src_md = no_ext + '.md'
        
        if target_src_md in path_to_id:
            target_id = path_to_id[target_src_md]
            anchor_str = f"-{clean_id(anchor)}" if anchor else ""
            return f"{prefix}{text}](#{target_id}{anchor_str})"
            
        # If it's an image or resource, rewrite the path to be relative to the docs/ directory
        # so that Pandoc running in docs/ can find it.
        anchor_str = f"#{anchor}" if anchor else ""
        dest = f"{target_src}{anchor_str}"
        if ' ' in dest and not (dest.startswith('<') and dest.endswith('>')):
            dest = f"<{dest}>"
        return f"{prefix}{text}]({dest})"
        
    content = re.sub(r'(!?\[)([^]]*)\]\(([^)]*)\)', replace_url, content) # Note: changed ([^)]+) to ([^)]*) to allow empty parentheses ()
    
    # 2. HTML image sources <img src="path" ...> to Markdown image syntax
    def replace_html_img(match):
        attrs = match.group(0)
        src_match = re.search(r'src=["\']([^"\']*)["\']', attrs)
        if not src_match:
            return match.group(0)
        url_part = src_match.group(1).strip()
        
        if not url_part:
            return ""
            
        if url_part.startswith(('http://', 'https://')):
            # Download remote image
            target_src = download_remote_image(url_part, docs_dir)
        elif url_part.startswith(('mailto:', 'ftp:', 'www.', '/')):
            return match.group(0)
        else:
            target_src = os.path.normpath(os.path.join(file_dir, url_part)).replace('\\', '/')
        
        # Check if there is a width attribute
        width_match = re.search(r'width=["\']([^"\']+)["\']', attrs)
        width_attr = ""
        if width_match:
            width_val = width_match.group(1).strip()
            # if it's just a number, append pt
            if width_val.isdigit():
                width_attr = f"{{width={width_val}pt}}"
            elif width_val.endswith('px'):
                val_num = width_val[:-2].strip()
                width_attr = f"{{width={val_num}pt}}"
            else:
                width_attr = f"{{width={width_val}}}"
                
        dest = target_src
        if ' ' in dest and not (dest.startswith('<') and dest.endswith('>')):
            dest = f"<{dest}>"
        return f"![Image]({dest}){width_attr}"
        
    # Match any <img ...> tag
    content = re.sub(r'<img\s+[^>]*>', replace_html_img, content)
    
    return content

def shift_headings(markdown_text, shift, page_id):
    # Also attach the unique ID to the first level-1 heading in the file
    lines = markdown_text.splitlines()
    in_code_block = False
    code_block_char = None
    
    new_lines = []
    attached_id = False
    
    for line in lines:
        stripped = line.strip()
        if not in_code_block:
            if stripped.startswith('```'):
                in_code_block = True
                code_block_char = '```'
            elif stripped.startswith('~~~'):
                in_code_block = True
                code_block_char = '~~~'
        else:
            if stripped.startswith(code_block_char):
                in_code_block = False
                code_block_char = None
                
        if not in_code_block:
            match = re.match(r'^#+[ \t]+(.*)$', line)
            if match:
                # Count leading hashes
                hashes = line[:len(line)-len(line.lstrip('#'))]
                title = match.group(1)
                
                # Check if we should attach the target ID to the first heading we see in the file
                id_suffix = ""
                if not attached_id:
                    # Strip any existing id if present in the header
                    title = re.sub(r'\{#[^}]+\}', '', title).strip()
                    id_suffix = f" {{#{page_id}}}"
                    attached_id = True
                    
                if shift > 0:
                    new_hashes = '#' * (len(hashes) + shift)
                    line = f"{new_hashes} {title}{id_suffix}"
                else:
                    line = f"{hashes} {title}{id_suffix}"
                    
        new_lines.append(line)
        
    # If no heading was found in the file, we prepend a target anchor
    if not attached_id:
        new_lines.insert(0, f"\n# {page_id.replace('-', ' ').title()} {{#{page_id}}}\n")
        
    return '\n'.join(new_lines)

def process_nav(items, path_to_id, docs_dir, output_file, depth=0):
    for item in items:
        if item.is_section:
            # Check if this section has an index page as its first child
            first_child = item.children[0] if item.children else None
            has_index = False
            if first_child and first_child.is_page:
                basename = os.path.basename(first_child.file.src_path).lower()
                has_index = (basename == 'index.md' or 
                             clean_id(first_child.file.src_path) == clean_id(item.title))
            
            if not has_index:
                # If there's no index page, output a heading for the section
                header_level = depth + 1
                hashes = '#' * header_level
                section_id = clean_id(item.title)
                output_file.write(f"\n\n{hashes} {item.title} {{#{section_id}}}\n\n")
                
            # Process children recursively
            process_nav(item.children, path_to_id, docs_dir, output_file, depth + 1)
            
        elif item.is_page:
            # Determine if this page is the index page of its parent section
            parent = item.parent
            is_index = False
            if parent and parent.is_section:
                first_child = parent.children[0]
                if first_child == item:
                    basename = os.path.basename(item.file.src_path).lower()
                    is_index = (basename == 'index.md' or
                                clean_id(item.file.src_path) == clean_id(parent.title))
            
            # Heading shift:
            # Index pages represent the section, so their depth is effectively depth - 1
            # Normal pages are at depth
            shift = (depth - 1) if is_index else depth
            shift = max(0, shift)
            
            abs_path = item.file.abs_src_path
            src_path = item.file.src_path.replace('\\', '/')
            page_id = path_to_id.get(src_path, clean_id(src_path))
            
            try:
                with open(abs_path, 'r', encoding='utf-8') as f:
                    content = f.read()
            except Exception as e:
                print(f"Error reading {abs_path}: {e}")
                continue
                
            # Rewrite paths and links
            content = rewrite_content(content, src_path, path_to_id, docs_dir)
            
            # Shift headings and attach page ID
            content = shift_headings(content, shift, page_id)
            
            # Append to output
            output_file.write(f"\n\n<!-- PAGE_START: {src_path} -->\n")
            output_file.write(content)
            output_file.write(f"\n<!-- PAGE_END: {src_path} -->\n")

def main():
    config_file = sys.argv[1] if len(sys.argv) > 1 else 'mkdocs.yml'
    if not os.path.exists(config_file):
        print(f"Error: Configuration file {config_file} not found.")
        sys.exit(1)
        
    print(f"Loading MkDocs configuration from {config_file}...")
    cfg = mkdocs.config.load_config(config_file=config_file)
    
    files = get_files(cfg)
    nav = get_navigation(files, cfg)
    
    print(f"Building path-to-id map for {len(nav.pages)} pages...")
    path_to_id = build_path_to_id_map(nav.pages)
    
    docs_dir = os.path.abspath(cfg.docs_dir)
    output_path = os.path.join(docs_dir, 'combined.md')
    
    print(f"Generating combined markdown file: {output_path}")
    with open(output_path, 'w', encoding='utf-8') as out_f:
        out_f.write("<!-- Generated by merge_docs.py -->\n")
        process_nav(nav.items, path_to_id, docs_dir, out_f, depth=0)
        
    print("Merge completed successfully!")

if __name__ == '__main__':
    main()
