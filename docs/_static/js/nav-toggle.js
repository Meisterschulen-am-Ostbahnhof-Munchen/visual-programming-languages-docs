// nav-toggle.js — Global navigation collapse/expand toggle for MkDocs Material
(function () {
  'use strict';

  const STORAGE_KEY = 'nav-toggle-collapsed';
  const SVG_EXPAND = '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" width="18" height="18" fill="currentColor" style="vertical-align: middle;"><path d="M12 18.17L8.83 15l-1.41 1.41L12 21l4.59-4.59L15.17 15M12 5.83L15.17 9l1.41-1.41L12 3 7.41 7.41 8.83 9 12 5.83z"/></svg>';
  const SVG_COLLAPSE = '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" width="18" height="18" fill="currentColor" style="vertical-align: middle;"><path d="M12 8L16.59 12.59 18 11.17 12 5.17 6 11.17 7.41 12.59 12 8zm0 8l-4.59-4.59L6 12.83l6 6 6-6-1.41-1.42L12 16z"/></svg>';
  const LABEL_EXPAND = 'Alle ausklappen';
  const LABEL_COLLAPSE = 'Alle einklappen';

  function isCollapsed() {
    return document.body.getAttribute('data-nav-collapsed') === 'true';
  }

  function setCollapsed(collapsed) {
    document.body.setAttribute('data-nav-collapsed', String(collapsed));
    try {
      sessionStorage.setItem(STORAGE_KEY, String(collapsed));
    } catch (e) {
      // Ignore storage errors
    }
    updateButton();
  }

  function toggleNav() {
    const collapsed = !isCollapsed();
    const navItems = document.querySelectorAll('.md-nav__item--nested');

    navItems.forEach(function (item) {
      const toggle = item.querySelector('.md-toggle');
      if (toggle) {
        toggle.checked = !collapsed;
      }
    });

    setCollapsed(collapsed);
  }

  function updateButton() {
    const btn = document.getElementById('nav-toggle-btn');
    if (!btn) return;
    const collapsed = isCollapsed();
    const icon = btn.querySelector('.md-icon');
    const label = btn.querySelector('.nav-toggle-label');

    if (icon) {
      icon.innerHTML = collapsed ? SVG_EXPAND : SVG_COLLAPSE;
    }
    if (label) {
      label.textContent = collapsed ? LABEL_EXPAND : LABEL_COLLAPSE;
    }
    btn.setAttribute('aria-pressed', String(!collapsed));
    btn.setAttribute('aria-expanded', String(!collapsed));
  }

  function createButton() {
    const sidebar = document.querySelector('.md-sidebar--primary .md-sidebar__inner');
    if (!sidebar) return;

    const btn = document.createElement('button');
    btn.id = 'nav-toggle-btn';
    btn.className = 'md-button nav-toggle-btn';
    btn.type = 'button';
    btn.innerHTML =
      '<span class="md-icon">' + SVG_COLLAPSE + '</span>' +
      '<span class="nav-toggle-label">' + LABEL_COLLAPSE + '</span>';

    const collapsed = isCollapsed();
    btn.setAttribute('aria-pressed', String(!collapsed));
    btn.setAttribute('aria-expanded', String(!collapsed));
    btn.addEventListener('click', toggleNav);

    sidebar.insertBefore(btn, sidebar.firstChild);
  }

  function init() {
    let collapsed = false;
    try {
      const stored = sessionStorage.getItem(STORAGE_KEY);
      collapsed = stored === 'true';
    } catch (e) {
      // Ignore storage errors
    }
    document.body.setAttribute('data-nav-collapsed', String(collapsed));
    createButton();
    if (collapsed) {
      const navItems = document.querySelectorAll('.md-nav__item--nested');
      navItems.forEach(function (item) {
        const toggle = item.querySelector('.md-toggle');
        if (toggle) toggle.checked = false;
      });
      updateButton();
    }
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', init);
  } else {
    init();
  }
})();
